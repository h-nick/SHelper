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

	/* Sets the class interval ranges */
	// TODO: Check if there's a way to reduce the iterator part.
	_vct<double>::iterator cntValueIt = m_rawNumericData.begin();
	_vct<double>::iterator maxValueIt = (m_rawNumericData.end() - 1);
	int cntValue = round(*cntValueIt);

	m_allClassIntervals.resize(m_rawNumericData.size());
	_vct<_oda>::iterator cnt = m_allClassIntervals.begin();

	while(cntValue <= *maxValueIt)
	{
		_oda ciTemp = *cnt;
		ciTemp.at(0) = cntValue;
		cnt++;
		cntValue += classInterval;
		ciTemp.at(1) = cntValue - 1;

		if(ciTemp.at(1) < *maxValueIt)
			cnt++; // FIXME: The final class interval .at(1) should be cntValue, not cntValue - 1.

		qDebug()
				<< "Class Interval:" << QString::number(ciTemp.at(0))
				<< " " << QString::number(ciTemp.at(1));
	}
	m_allClassIntervals.resize(m_allClassIntervals.size());
	// FIXME: Perhaps .push_back() should be used instead of this constant use of .resize().

	/* Calculates the class marks */
	// FIXME: This doesn't work for some reason. The ciTemp is getting an empty _oda.
	cnt = m_allClassIntervals.begin();
	m_classMarks.resize(m_allClassIntervals.size());
	_vct<int>::iterator cntMark = m_classMarks.begin();

	for(; cnt != m_allClassIntervals.end(); cnt++)
	{
		_oda ciTemp = *cnt;
		*cntMark = (ciTemp.at(0) + ciTemp.at(1)) / 2;
		cntMark++;
		qDebug() << "Class Mark:" << QString::number(*cntMark);
	}
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
