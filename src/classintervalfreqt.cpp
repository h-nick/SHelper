#include <QDebug>
#include <algorithm>
#include <cmath>
#include "include/classintervalfreqt.h"
#include "ui_classintervalfreqt.h"

ClassIntervalFreqT::ClassIntervalFreqT(_vct<double> &numeric_data, QWidget *parent) :
	QWidget(parent), m_rawNumericData(numeric_data),
	ui(new Ui::ClassIntervalFreqT)
{
	ui->setupUi(this);
	m_rawNumericData.resize(numeric_data.size());
	vectorialCalculations();
}

ClassIntervalFreqT::~ClassIntervalFreqT()
{
	delete ui;
}

// NOTE: This should probably be a template.
int ClassIntervalFreqT::getTotalRealAmplitude()
{
	return m_rawNumericData.at(m_rawNumericData.size() - 1) - m_rawNumericData.at(0) + 1;
	// Instead of adding 1, it should determine if there's decimals in the values and add either
	// 1 or 0.1 accordingly.
}

void ClassIntervalFreqT::getClassIntervalRanges()
{

}

void ClassIntervalFreqT::getClassMarks()
{

}

void ClassIntervalFreqT::vectorialCalculations()
{
	/* Sorts the data in asc order */
	std::sort(m_rawNumericData.begin(), m_rawNumericData.end());

	/* Gets the TRA */
	// FIXME: This doesn't work if the values are decimals. This must be fixed.
	double TRA = getTotalRealAmplitude();

	/* Gets the class interval */
	// TODO: Check formulas.
	double observationK = round((1 + (3.322 * log10(m_rawNumericData.size()))));
	double classInterval = round(TRA/observationK);

	/* Sets the ranges */
	// TODO: Check if there's a way to reduce the iterator part.
	_vct<double>::iterator cntValueIt = m_rawNumericData.begin();
	_vct<double>::iterator maxValueIt = (m_rawNumericData.end() - 1);
	int cntValue = round(*cntValueIt);

	m_allClassIntervals.reserve(m_rawNumericData.size());
	_vct<int>::iterator cnt = m_allClassIntervals.begin();

	qDebug() << *cnt;	// FIXME: This is not working.

	while(cntValue <= *maxValueIt)
	{
		*cnt = cntValue;
		cnt++;
		cntValue += classInterval;
		*cnt = cntValue - 1;
		cnt++;
	}

	cnt = m_allClassIntervals.begin();
	qDebug() << "ITR: \n";
	for(; cnt != m_allClassIntervals.end(); cnt++)
		qDebug() << *cnt << " ";


	/* NOTE: Plan to calculate this: Get the classInterval, create them based on the minValue and maxValue.
	 * Then iterate the vector and add 1 to the absolute frequency of the class interval.
	 */

}

void ClassIntervalFreqT::buildTable()
{

}

void ClassIntervalFreqT::showFreqPoligon()
{

}

void ClassIntervalFreqT::showHistogram()
{

}

void ClassIntervalFreqT::showOjive()
{

}
