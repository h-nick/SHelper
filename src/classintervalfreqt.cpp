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

void ClassIntervalFreqT::getClassIntervalRanges(double classInterval)
{
	_vct<double>::iterator cntValueIt = m_rawNumericData.begin();
	_vct<double>::iterator maxValueIt = (m_rawNumericData.end() - 1);
	int cntValue = round(*cntValueIt);

	while(cntValue <= *maxValueIt)
	{
		_oda ciTemp;
		ciTemp.at(0) = cntValue;
		cntValue += classInterval;
		ciTemp.at(1) = cntValue - 1;
		m_allClassIntervals.push_back(ciTemp);
		// FIXME: The final class interval .at(1) should be cntValue, not cntValue - 1.
	}
}

void ClassIntervalFreqT::getClassMarks()
{
	_vct<_oda>::iterator cnt = m_allClassIntervals.begin();

	for(; cnt != m_allClassIntervals.end(); cnt++)
	{
		_oda ciTemp = *cnt;
		m_classMarks.push_back(round((double)ciTemp.at(0) + (double)ciTemp.at(1) / 2));
	}
}

void ClassIntervalFreqT::vectorialCalculations()
{
	/* Sorts the data in asc order */
	std::sort(m_rawNumericData.begin(), m_rawNumericData.end());

	/* Gets the TRA */
	// FIXME: This doesn't work if the values are decimals. This must be fixed.
	double TRA = getTotalRealAmplitude();

	/* Gets the class interval */
	double observationK = round((1 + (3.322 * log10(m_rawNumericData.size()))));
	double classInterval = round(TRA/observationK);

	/* Sets the class interval ranges */
	getClassIntervalRanges(classInterval);

	/* Calculates the class marks */
	getClassMarks();

	/* Determine the absolute frequencies per class range*/
	// TODO: This can be optimized greatly. Consider this algorithm a placeholder.
	_vct<_oda>::const_iterator cntCI = m_allClassIntervals.begin();
	m_absoluteFreq.resize(m_allClassIntervals.size());
	_vct<int>::iterator cntAF = m_absoluteFreq.begin();

	for(; cntCI != m_allClassIntervals.end(); cntCI++)
	{
		_oda ciTemp = *cntCI;

		_vct<double>::const_iterator cntVal = m_rawNumericData.begin();
		for(; cntVal != m_rawNumericData.end(); cntVal++)
			if(*cntVal <= ciTemp.at(1) && *cntVal >= ciTemp.at(0))
				*cntAF += 1;
		cntAF++;
	}

	cntAF = m_absoluteFreq.begin();
	for(; cntAF != m_absoluteFreq.end(); cntAF++)
		qDebug() << QString::number(*cntAF);


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
