#include <algorithm>
#include "include/classintervalfreqt.h"
#include "ui_classintervalfreqt.h"

ClassIntervalFreqT::ClassIntervalFreqT(_vct<double> &numeric_data, QWidget *parent) :
	QWidget(parent), m_rawNumericData(numeric_data),
	ui(new Ui::ClassIntervalFreqT)
{
	ui->setupUi(this);
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
	std::sort(m_rawNumericData.rbegin(), m_rawNumericData.rend());

	/* Gets the TRA */
	// FIXME: This doesn't work if the values are decimals. This must be fixed.
	int TRA = getTotalRealAmplitude();

	/* Gets the class interval */
	int observationK = (1 + (3.222 * log10(m_rawNumericData.size()))) + 1;
	int classInterval = TRA/observationK;

	/* Sets the ranges */
	_vct<double>::const_iterator minValue = m_rawNumericData.begin();
	_vct<double>::const_iterator maxValue = m_rawNumericData.end();

	for(int cnt = 0; cnt < 1; cnt++)
	{
	}

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
