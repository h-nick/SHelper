#include <iostream>
#include <QDebug>
#include <algorithm>
#include "include/simplefreqt.h"
#include "ui_simplefreqt.h"

SimpleFreqT::SimpleFreqT(_vct<double> &numeric_data, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SimpleFreqT)
{
	ui->setupUi(this);

	_vct<double> raw_numeric_data = numeric_data;
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
	_vct<double>::const_iterator dItr;
	_vct<int>::const_iterator nItr;

	/* Builds the variables column */
	int crn = 0;
	for(dItr = variables.begin(); dItr != variables.end(); dItr++)
	{
		QTableWidgetItem *item = new QTableWidgetItem(QString::number(*dItr));

		QFont font;
		font.setWeight(QFont::Bold);
		item->setFont(font);
		item->setTextAlignment(Qt::AlignCenter);

		ui->table->setRowCount(variables.size() + 1);
		ui->table->setItem(crn, 0, item);
		crn++;
	}

	/* Builds the absolute frequencies column */
	crn = 0;
	int absoluteSum = 0;
	for(nItr = absolute_freq.begin(); nItr != absolute_freq.end(); nItr++)
	{
		QTableWidgetItem *item = new QTableWidgetItem(QString::number(*nItr));
		absoluteSum += *nItr;
		item->setTextAlignment(Qt::AlignCenter);

		ui->table->setItem(crn, 1, item);
		crn++;
	}

	/* Builds the index items in the last row */
	// crn shouldn't be reset to 0 in the last build function. Crn will be used to know the last row
	// index.
	// TODO: This is not implemented fully.
	QTableWidgetItem *item = new QTableWidgetItem(QString::number(absoluteSum));

	QFont font;
	font.setWeight(QFont::Bold);
	item->setFont(font);
	QBrush brush;
	brush.setColor(Qt::blue);
	item->setForeground(brush);
	item->setTextAlignment(Qt::AlignCenter);

	ui->table->setItem(crn, 0, new QTableWidgetItem("-"));
	ui->table->setItem(crn, 1, item);

}

void SimpleFreqT::vectorialCalculations(_vct<double> & raw_numeric_data)
{
	/* Sorts the original vector */
	std::sort(raw_numeric_data.begin(), raw_numeric_data.end());

	/* Deletes duplicated entries in the variables vector */
	variables = raw_numeric_data;
	makeVectorUnique(variables);

	/* Creates the frequency table */
	makeFrequencyTable(variables, raw_numeric_data);

	buildTable();
}

void SimpleFreqT::makeVectorUnique(_vct<double> & vector)
{
	vector.erase(unique(vector.begin(), vector.end()), vector.end());
}

void SimpleFreqT::makeFrequencyTable(_vct<double> & variables, _vct<double> & raw_numeric_data)
{
	_vct<double>::iterator dVarItr, dRVarItr;
	_vct<int>::iterator nVarItr;

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
