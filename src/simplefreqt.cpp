#include <iostream>
#include <QDebug>
#include <algorithm>
#include <vector>
#include "include/simplefreqt.h"
#include "ui_simplefreqt.h"

SimpleFreqT::SimpleFreqT(_vct<double> &raw_numeric_data, QWidget *parent) :
	QDialog(parent), absoluteSum(raw_numeric_data.size()),
	ui(new Ui::SimpleFreqT)
{
	ui->setupUi(this);

	vectorialCalculations(raw_numeric_data);
	connect(ui->button_return, SIGNAL(pressed()), this, SLOT(close()));
	//connect(ui->button_graph, SIGNAL(pressed()), this, SLOT())
}

SimpleFreqT::~SimpleFreqT()
{
	delete ui;
}

void SimpleFreqT::buildTable()
{
	_vct<double>::const_iterator dItr; // Iterator for double-type vectors.
	_vct<int>::const_iterator nItr;	// Iterator for int-type vectors.
	ui->table->setRowCount(variables.size() + 1);

	// TODO: Compress all of this in one or two functions since they are all the same.
	/* Builds the variables column */
	int crn = 0;
	for(dItr = variables.begin(); dItr != variables.end(); dItr++)
	{
		QTableWidgetItem *item = new QTableWidgetItem(QString::number(*dItr));

		QFont font;
		font.setWeight(QFont::Bold);
		item->setFont(font);
		item->setTextAlignment(Qt::AlignCenter);

		ui->table->setItem(crn, 0, item);
		crn++;
	}

	/* Builds the absolute frequencies column */
	crn = 0;
	for(nItr = absolute_freq.begin(); nItr != absolute_freq.end(); nItr++)
	{
		QTableWidgetItem *item = new QTableWidgetItem(QString::number(*nItr));
		item->setTextAlignment(Qt::AlignCenter);

		ui->table->setItem(crn, 1, item);
		crn++;
	}

	/* Builds the relative frequencies column */
	crn = 0;
	for(dItr = relative_freq.begin(); dItr != relative_freq.end(); dItr++)
	{
		QTableWidgetItem *item = new QTableWidgetItem(QString::number(*dItr));
		item->setTextAlignment(Qt::AlignCenter);

		ui->table->setItem(crn, 2, item);
		crn++;
	}

	/* Builds the accumulated frequencies column */
	crn = 0;
	for(nItr = accumulated_freq.begin(); nItr != accumulated_freq.end(); nItr++)
	{
		QTableWidgetItem *item = new QTableWidgetItem(QString::number(*nItr));
		item->setTextAlignment(Qt::AlignCenter);

		ui->table->setItem(crn, 3, item);
		crn++;
	}

	/* Builds the accumulated relative frequencies column */
	crn = 0;
	for(dItr = accumulated_relative_freq.begin(); dItr != accumulated_relative_freq.end(); dItr++)
	{
		QTableWidgetItem *item = new QTableWidgetItem(QString::number(*dItr));
		item->setTextAlignment(Qt::AlignCenter);

		ui->table->setItem(crn, 4, item);
		crn++;
	}

	/* Builds relative percentage column */
	crn = 0;
	for(dItr = relative_percentage.begin(); dItr != relative_percentage.end(); dItr++)
	{
		QTableWidgetItem *item = new QTableWidgetItem(QString::number(*dItr));
		item->setTextAlignment(Qt::AlignCenter);

		ui->table->setItem(crn, 5, item);
		crn++;
	}

	/* Builds accumulated percentage column */
	crn = 0;
	for(dItr = accumulated_percentage.begin(); dItr != accumulated_percentage.end(); dItr++)
	{
		QTableWidgetItem *item = new QTableWidgetItem(QString::number(*dItr));
		item->setTextAlignment(Qt::AlignCenter);

		ui->table->setItem(crn, 6, item);
		crn++;
	}

	/* Builds the index items in the last row */
	// crn shouldn't be reset to 0 in the last build function. Crn will be used to know the last row
	// index.
	// TODO: This should probably be moved to another function. Consider it a placeholder for now.

	double sum_relative_frequency = 0;
	for(auto &n : relative_freq)
		sum_relative_frequency += n;

	double sum_relative_percentage = 0;
	for(auto &n : relative_percentage)
		sum_relative_percentage += n;

	QTableWidgetItem *iNull = new QTableWidgetItem("-");
	QTableWidgetItem *iAbsoluteF = new QTableWidgetItem(QString::number(absoluteSum));
	QTableWidgetItem *iRelativeF = new QTableWidgetItem(QString::number(sum_relative_frequency));
	QTableWidgetItem *iRelativeP = new QTableWidgetItem(QString::number(sum_relative_percentage));

	QFont font;
	font.setWeight(QFont::Bold);
	QBrush brush;
	brush.setColor(Qt::blue);

	iNull->setFont(font);
	iNull->setForeground(brush);
	iNull->setTextAlignment(Qt::AlignCenter);


	iAbsoluteF->setFont(font);
	iAbsoluteF->setForeground(brush);
	iAbsoluteF->setTextAlignment(Qt::AlignCenter);


	iRelativeF->setFont(font);
	iRelativeF->setForeground(brush);
	iRelativeF->setTextAlignment(Qt::AlignCenter);


	iRelativeP->setFont(font);
	iRelativeP->setForeground(brush);
	iRelativeP->setTextAlignment(Qt::AlignCenter);



	ui->table->setItem(crn, 0, iNull);
	ui->table->setItem(crn, 1, iAbsoluteF);
	ui->table->setItem(crn, 2, iRelativeF);
	//ui->table->setItem(crn, 3, iNull);
	//ui->table->setItem(crn, 4, iNull);
	ui->table->setItem(crn, 5, iRelativeP);
	//ui->table->setItem(crn, 6, iNull);

	// FIXME: The same item can't be assigned to several columns.
}

void SimpleFreqT::vectorialCalculations(_vct<double> & raw_numeric_data)
{
	/* Sorts the original vector */
	std::sort(raw_numeric_data.rbegin(), raw_numeric_data.rend());

	/* Deletes duplicated entries in the variables vector */
	variables = raw_numeric_data;
	makeVectorUnique(variables);

	/* Creates the absolute frequency table */
	makeFrequencyTable(raw_numeric_data);

	/* Creates the relative frequency table */
	relative_freq.resize(absolute_freq.size());
	for(unsigned int crn = 0; crn < absolute_freq.size(); crn++)
		relative_freq.at(crn) = static_cast<double>(absolute_freq.at(crn)) / absoluteSum;

	/* Creates the accumulated absolute and relative frequency table */
	makeACMFreqTable(absolute_freq, accumulated_freq);
	makeACMFreqTable(relative_freq, accumulated_relative_freq);

	/* Creates the relative percentage table */
	relative_percentage.resize(variables.size());
	for(unsigned int crn = 0; crn < relative_percentage.size(); crn++)
		relative_percentage.at(crn) = relative_freq.at(crn) * 100;

	/* Creates the accumulated percentage table */
	makeACMFreqTable(relative_percentage, accumulated_percentage);

	/* Builds the simple frequency table */
	buildTable();
}

void SimpleFreqT::makeVectorUnique(_vct<double> & vector)
{
	vector.erase(unique(vector.begin(), vector.end()), vector.end());
}

void SimpleFreqT::makeFrequencyTable(_vct<double> & raw_numeric_data)
{
	_vct<double>::iterator dVarItr, dRVarItr;

	// NOTE: This can be done more optimally with a hash map.
	int current = 0;
	for(dVarItr = variables.begin(); dVarItr != variables.end(); dVarItr++)
	{
		int count = 0;
		for(dRVarItr = raw_numeric_data.begin(); dRVarItr != raw_numeric_data.end(); dRVarItr++)
		{
			if((*dVarItr) == (*dRVarItr))
				count++;
		}

		absolute_freq.resize(current + 1);
		absolute_freq.at(current) = count;
		current++;
	}
}

template<typename T>
void SimpleFreqT::makeACMFreqTable(_vct<T> & mainFreq, _vct<T> & ACMFreq)
{
	ACMFreq.resize(variables.size());
	_vct<T>::const_iterator const_itr = mainFreq.begin();
	_vct<T>::iterator itr = ACMFreq.begin();
	T accumulatedSum = 0;

	for(; const_itr != mainFreq.end(); const_itr++)
	{
		accumulatedSum += *const_itr;
		*(itr++) = accumulatedSum;
	}
}
