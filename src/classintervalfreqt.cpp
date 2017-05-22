#include <QDebug>
#include <QTableWidget>
#include <QLabel>
#include <algorithm>
#include <cmath>
#include "include/classintervalfreqt.h"
#include "include/accumulator.h"
#include "include/classintervalfreqg.h"
#include "include/barchart.h"
#include "ui_classintervalfreqt.h"

ClassIntervalFreqT::ClassIntervalFreqT(_vct<double> &numeric_data, QWidget *parent)
										: QWidget(parent), m_rawNumericData(numeric_data),
	ui(new Ui::ClassIntervalFreqT)
{
	ui->setupUi(this);
	m_rawNumericData.resize(numeric_data.size());
	vectorialCalculations();

	connect(ui->buttonFreqPol, SIGNAL(pressed()), this, SLOT(showFreqPolygon()));
	connect(ui->buttonHistogram, SIGNAL(pressed()), this, SLOT(showHistogram()));
	connect(ui->buttonOgive, SIGNAL(pressed()), this, SLOT(showOgive()));
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
	_vct<double>::iterator cntValueIt = m_rawNumericData.begin();
	_vct<double>::iterator maxValueIt = (m_rawNumericData.end() - 1);
	int cntValue = round(*cntValueIt);

	while(cntValue <= *maxValueIt)
	{
		_oda ciTemp;
		ciTemp.at(0) = cntValue;
		cntValue += m_classInterval;
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
		m_classMarks.push_back(round(((double)ciTemp.at(0) + (double)ciTemp.at(1)) / 2));
	}
}

void ClassIntervalFreqT::getSingleClassIntervalRange()
{
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

}

void ClassIntervalFreqT::vectorialCalculations()
{
	/* Sorts the data in asc order */
	std::sort(m_rawNumericData.begin(), m_rawNumericData.end());

	/* Gets the TRA */
	// FIXME: This doesn't work if the values are decimals.
	double TRA = getTotalRealAmplitude();

	/* Gets the class interval */
	double observationK = round((1 + (3.322 * log10(m_rawNumericData.size()))));
	m_classInterval = round(TRA/observationK);

	/* Sets the class interval ranges */
	getClassIntervalRanges();

	/* Calculates the class marks */
	getClassMarks();

	/* Determines the absolute frequencies per class range*/
	getSingleClassIntervalRange();

	/* Creates the relative frequency table */
	// TODO: Move this (And the ones in SimpleFreqT) to the global scope. These are very similar.
	_vct<int>::const_iterator nItr = m_absoluteFreq.begin();
	for(; nItr != m_absoluteFreq.end(); nItr++)
		m_relativeFreq.push_back(static_cast<double>(*nItr) / m_rawNumericData.size());

	/* Creates the percentage list */
	_vct<double>::const_iterator dItr = m_relativeFreq.begin();
	for(; dItr != m_relativeFreq.end(); dItr++)
		m_relativePrcntgs.push_back(*dItr * 100);

	/* Accumulator */
	createACMFreqVector(m_absoluteFreq, m_accAbsoluteFreq);
	createACMFreqVector(m_relativeFreq, m_accRelativeFreq);
	createACMFreqVector(m_relativePrcntgs, m_accRelativePrcntgs);

	/* Calculate central trends */
	calculateAverages();
	calculateMedian(); // calculateMedian() calls calculateMode().

	/* Builds the table */
	buildTable();

	/* Prints the data */
	printData();
}

void ClassIntervalFreqT::buildTable()
{
	_vct<double>::const_iterator dItr; // Iterator for double-type vectors.
	_vct<int>::const_iterator nItr;	// Iterator for int-type vectors.
	_vct<_oda>::const_iterator ciItr = m_allClassIntervals.begin();
	ui->table->setRowCount(m_allClassIntervals.size());

	// TODO: Compress all of this in one or two functions since they are all the same.
	/* Builds the class-intervals column */
	int crn = 0;
	for(; ciItr != m_allClassIntervals.end(); ciItr++)
	{
		_oda ciTemp = *ciItr;
		QTableWidgetItem *item =
				new QTableWidgetItem(QString::number(ciTemp.at(0)) + " - " + QString::number(ciTemp.at(1)));

		QFont font;
		font.setWeight(QFont::Bold);
		item->setFont(font);
		item->setTextAlignment(Qt::AlignCenter);
		ui->table->setItem(crn++, 0, item);
	}

	/* Builds the classes marks column */
	crn = 0;
	for(nItr = m_classMarks.begin(); nItr != m_classMarks.end(); nItr++)
	{
		QTableWidgetItem *item = new QTableWidgetItem(QString::number(*nItr));
		item->setTextAlignment(Qt::AlignCenter);
		ui->table->setItem(crn++, 1, item);
	}

	/* Builds the absolute frequencies column */
	crn = 0;
	for(nItr = m_absoluteFreq.begin(); nItr != m_absoluteFreq.end(); nItr++)
	{
		QTableWidgetItem *item = new QTableWidgetItem(QString::number(*nItr));
		item->setTextAlignment(Qt::AlignCenter);
		ui->table->setItem(crn++, 2, item);
	}

	/* Builds the accumulated frequencies column */
	crn = 0;
	for(nItr = m_accAbsoluteFreq.begin(); nItr != m_accAbsoluteFreq.end(); nItr++)
	{
		QTableWidgetItem *item = new QTableWidgetItem(QString::number(*nItr));
		item->setTextAlignment(Qt::AlignCenter);
		ui->table->setItem(crn++, 3, item);
	}

	/* Builds the relative frequencies column */
	crn = 0;
	for(dItr = m_relativeFreq.begin(); dItr != m_relativeFreq.end(); dItr++)
	{
		QTableWidgetItem *item = new QTableWidgetItem(QString::number(*dItr));
		item->setTextAlignment(Qt::AlignCenter);
		ui->table->setItem(crn++, 4, item);
	}

	/* Builds the accumulated relative frequencies column */
	crn = 0;
	for(dItr = m_accRelativeFreq.begin(); dItr != m_accRelativeFreq.end(); dItr++)
	{
		QTableWidgetItem *item = new QTableWidgetItem(QString::number(*dItr));
		item->setTextAlignment(Qt::AlignCenter);
		ui->table->setItem(crn++, 5, item);
	}

	/* Builds the percentages column */
	crn = 0;
	for(dItr = m_relativePrcntgs.begin(); dItr != m_relativePrcntgs.end(); dItr++)
	{
		QTableWidgetItem *item = new QTableWidgetItem(QString::number(*dItr));
		item->setTextAlignment(Qt::AlignCenter);
		ui->table->setItem(crn++, 6, item);
	}

	/* Builds the accumulated percentages column */
	crn = 0;
	for(dItr = m_accRelativePrcntgs.begin(); dItr != m_accRelativePrcntgs.end(); dItr++)
	{
		QTableWidgetItem *item = new QTableWidgetItem(QString::number(*dItr));
		item->setTextAlignment(Qt::AlignCenter);
		ui->table->setItem(crn++, 7, item);
	}
}

void ClassIntervalFreqT::showFreqPolygon()
{
	ClassIntervalFreqG *freqPolygon = new ClassIntervalFreqG(m_classMarks, m_absoluteFreq, this);
	freqPolygon->setAttribute(Qt::WA_DeleteOnClose);
	freqPolygon->show();
}

void ClassIntervalFreqT::showHistogram()
{
	BarChart *histogram = new BarChart(m_allClassIntervals, m_absoluteFreq, this);
	histogram->setAttribute(Qt::WA_DeleteOnClose);
	histogram->show();
}

void ClassIntervalFreqT::showOgive()
{
	ClassIntervalFreqG *ogive = new ClassIntervalFreqG(m_allClassIntervals, m_accAbsoluteFreq, this);
	ogive->setAttribute(Qt::WA_DeleteOnClose);
	ogive->show();
}

void ClassIntervalFreqT::printData()
{
	QLabel *CentralTendencyLabel = new QLabel(this);
	CentralTendencyLabel->setTextFormat(Qt::RichText);
	CentralTendencyLabel->setText(
				"<b>Central tendencies:</b><br>"
				"Arithmetic average: "	+ QString::number(m_arithmeticAverage) + "<br>"
				"Geometric average: "	+ QString::number(m_geometricAverage) + "<br>"
				"Median: "				+ QString::number(m_median) + "<br>"
				"Mode: "				+ QString::number(m_mode)
				);
	ui->gridLayout->addWidget(CentralTendencyLabel, 2, 0, Qt::AlignLeft | Qt::AlignVCenter);

	QLabel *DispersionMeasurementLabel = new QLabel(this);
	DispersionMeasurementLabel->setTextFormat(Qt::RichText);
	DispersionMeasurementLabel->setText(
				"<b>Measures of disperion:</b><br>"
				"Range: "				+ QString::number(m_range) + "<br>"
				"Standard deviation: "	+ QString::number(m_standardDeviation) + "<br>"
				"Variance: "			+ QString::number(m_variance) + "<br>"
				"Typical deviation: "	+ QString::number(sqrt(m_variance)) + "<br>"
				"Cft. of variation: "	+ QString::number(m_varianceCoefficient) + "<br>"
				"Interquartile range: "	"PLACEHOLDER <br>"
				"Pearson Cft.:"			+ QString::number(m_coefficientPearson) + "<br>"
				"Bowley Cft.:"			+ QString::number(m_coefficientBowley) + "<br>"
				"Kurtosis Cft.:"		+ QString::number(m_coefficientKurtosis) + "<br>"
				);
	ui->gridLayout->addWidget(DispersionMeasurementLabel, 2, 1, Qt::AlignHCenter | Qt::AlignVCenter);
}

void ClassIntervalFreqT::calculateAverages()
{
	_vct<int>::const_iterator ItrFreq = m_absoluteFreq.begin();
	_vct<int>::const_iterator ItrMark = m_classMarks.begin();
	double sumForAAvg(0), sumForGAvg(0);

	for(; ItrFreq != m_absoluteFreq.end(); ItrFreq++)
	{
		sumForAAvg += ((*ItrFreq) * (*ItrMark));			// Arithmetic average.
		sumForGAvg += ((*ItrFreq) * log10(*(ItrMark++)));	// Geometric average.
		m_totalElements += *(ItrFreq);

	}
	m_arithmeticAverage = sumForAAvg / m_totalElements;
	m_geometricAverage = pow(10, (sumForGAvg / m_totalElements));
}

void ClassIntervalFreqT::calculateMedian()
{
	int rawFreqMedian = m_absoluteFreq.at(static_cast<int>(m_absoluteFreq.size() / 2) - 1);
	int accFreqMedianM1 = m_accAbsoluteFreq.at(static_cast<int>(m_accAbsoluteFreq.size() / 2) - 2);
	_oda medianLimit = m_allClassIntervals.at(static_cast<int>(m_allClassIntervals.size() / 2 - 1));
	int lowerLimit = medianLimit.at(0);

	m_median = ((((m_totalElements / 2) - accFreqMedianM1) * m_classInterval) /
				static_cast<double>(rawFreqMedian)) + lowerLimit;

	calculateMode(lowerLimit);
}

void ClassIntervalFreqT::calculateMode(int lowerLimit)
{
	_vct<int>::iterator FreqItr = std::max_element(m_absoluteFreq.begin(), m_absoluteFreq.end());
	m_mode = ((*FreqItr / ((*FreqItr - 1) + (*FreqItr + 1))) * m_classInterval) + lowerLimit;
}
