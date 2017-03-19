#include <iostream>
#include <QDebug>
#include <algorithm>
#include "include/simplefreqt.h"
#include "ui_simplefreqt.h"

SimpleFreqT::SimpleFreqT(_vct<double> &raw_numeric_data, QWidget *parent) :
	QDialog(parent), absoluteSum(raw_numeric_data.size()),
	ui(new Ui::SimpleFreqT)
{
	ui->setupUi(this);

	//_vct<double> raw_numeric_data = numeric_data;
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

	/* Builds the index items in the last row */
	// crn shouldn't be reset to 0 in the last build function. Crn will be used to know the last row
	// index.
	// TODO: This is not implemented fully. It should probably be moved to another function.
	QTableWidgetItem *item = new QTableWidgetItem(QString::number(absoluteSum));

	QFont font;
	font.setWeight(QFont::Bold);
	item->setFont(font);
	item->setBackgroundColor(Qt::green);
	item->setTextAlignment(Qt::AlignCenter);

	ui->table->setItem(crn, 0, new QTableWidgetItem("-"));
	ui->table->setItem(crn, 1, item);

	double sum_relative_frequency = 0;
	for(auto &n : relative_freq)
		sum_relative_frequency += n;

	item = new QTableWidgetItem(QString::number(sum_relative_frequency));
	item->setFont(font);
	item->setTextAlignment(Qt::AlignCenter);
	item->setBackgroundColor(Qt::green);
	ui->table->setItem(crn, 2, item);
}

void SimpleFreqT::vectorialCalculations(_vct<double> & raw_numeric_data)
{
	/* Sorts the original vector */
	std::sort(raw_numeric_data.begin(), raw_numeric_data.end());

	/* Deletes duplicated entries in the variables vector */
	variables = raw_numeric_data;
	makeVectorUnique(variables);

	/* Creates the absolute frequency table */
	makeFrequencyTable(raw_numeric_data);

	/* Creates the relative frequency table */
	relative_freq.resize(absolute_freq.size());
	for(unsigned int crn = 0; crn < absolute_freq.size(); crn++)
		relative_freq.at(crn) = static_cast<double>(absolute_freq.at(crn)) / absoluteSum;

	/* Creates the accumulated frequency table */
	makeACMFreqTable();

	/* Creates the final table */
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

void SimpleFreqT::makeACMFreqTable()
{
	accumulated_freq.resize(variables.size());
	_vct<int>::const_iterator const_nItr = absolute_freq.begin();
	_vct<int>::iterator nItr = accumulated_freq.begin();
	int accumulatedSum = 0;

	for(; const_nItr != absolute_freq.end(); const_nItr++)
	{
		accumulatedSum += *const_nItr;
		*(nItr++) = accumulatedSum;
	}
}
