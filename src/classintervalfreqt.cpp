#include <QSignalMapper>
#include <QDebug>
#include <QTableWidget>
#include <QLabel>
#include <QMessageBox>
#include <qdialog.h>
#include <algorithm>
#include <cmath>
#include <functional>
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
	ui->retranslateUi(this);

	vectorialCalculations();

	connect(ui->buttonFreqPol, SIGNAL(pressed()), this, SLOT(showFreqPolygon()));
	connect(ui->buttonHistogram, SIGNAL(pressed()), this, SLOT(showHistogram()));
	connect(ui->buttonOgive, SIGNAL(pressed()), this, SLOT(showOgive()));

	QSignalMapper *mapper = new QSignalMapper(this);
	connect(mapper, SIGNAL(mapped(int)), this, SLOT(printPosition(int)));

	connect(ui->buttonQuartiles, SIGNAL(pressed()), mapper, SLOT(map()));
	mapper->setMapping(ui->buttonQuartiles, (int)posType::QUARTILE);
	connect(ui->buttonSextiles, SIGNAL(pressed()), mapper, SLOT(map()));
	mapper->setMapping(ui->buttonSextiles, (int)posType::SEXTILE);
	connect(ui->buttonDeciles, SIGNAL(pressed()), mapper, SLOT(map()));
	mapper->setMapping(ui->buttonDeciles, (int)posType::DECILE);
}

ClassIntervalFreqT::~ClassIntervalFreqT()
{
	delete ui;
}

// NOTE: This should probably be a template.
double ClassIntervalFreqT::getTotalRealAmplitude()
{
	double TRA = m_rawNumericData.at(m_rawNumericData.size() - 1) - m_rawNumericData.at(0);

	if (areThereIntegers())
		return TRA + 1;
	else
		return TRA + 0.1;
}

bool ClassIntervalFreqT::areThereIntegers()
{
	_vct<double>::const_iterator allItr = m_rawNumericData.begin();

	for (; allItr != m_rawNumericData.end(); allItr++)
	{
		if (std::floor(std::abs(*allItr)) == std::abs(*allItr))
			return true;
	}
	return false;
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
	// NOTE: This can probably be optimized greatly. Consider this algorithm a placeholder.
	_vct<_oda>::const_iterator cntCI = m_allClassIntervals.begin();
	for(; cntCI != m_allClassIntervals.end(); cntCI++)
	{
		int tempCounter = 0;
		_oda ciTemp = *cntCI;
		_vct<double>::const_iterator cntVal = m_rawNumericData.begin();

		for(; cntVal != m_rawNumericData.end(); cntVal++)
			if(*cntVal <= ciTemp.at(1) && *cntVal >= ciTemp.at(0))
				tempCounter++;
		m_absoluteFreq.push_back(tempCounter);
	}
}

void ClassIntervalFreqT::vectorialCalculations()
{
	/* Sorts the data in asc order */
	std::sort(m_rawNumericData.begin(), m_rawNumericData.end());

	/* Gets the TRA */
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
	calculateTrueMedian();
	calculateTrueMode();

	/* Calculate position trends */
	positionTrends(posType::QUARTILE);
	positionTrends(posType::SEXTILE);
	positionTrends(posType::DECILE);
	calculateQRanges();

	/* Calculate measures of dispersion */
	_vct<double> allDeviations = calculateAllDeviations();
	calculateDispersion(allDeviations, opType::TYPE_DEVIATION);
	calculateDispersion(allDeviations, opType::TYPE_VARIANCE);
	calculateDispersion(allDeviations, opType::TYPE_KURTOSIS);
	calculateCoefficients();

	/* Builds the table */
	buildTable();

	/* Prints the data */
	printData();
}

void ClassIntervalFreqT::calculateQRanges()
{
	m_interquartileRange = m_quartiles[2] - m_quartiles[0];
	m_interquartileDeviation = m_interquartileRange / 2;
}

void ClassIntervalFreqT::buildTable()
{
	// NOTE: This is showing lines with absolute frequency 0.
	_vct<double>::const_iterator dItr; // Iterator for double-type vectors.
	_vct<int>::const_iterator nItr;	// Iterator for int-type vectors.
	_vct<_oda>::const_iterator ciItr = m_allClassIntervals.begin();
	ui->table->setRowCount(m_allClassIntervals.size());

	// NOTE: Maybe compress all of this in one or two functions since they are all the same.
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
	/* Prints all the data below the tableGrid */
	QLabel *CentralTendencyLabel = new QLabel(this);
	CentralTendencyLabel->setTextFormat(Qt::RichText);
	CentralTendencyLabel->setText(
				tr("<b>Central tendencies:</b><br>"
				"Arithmetic average: ")		+ QString::number(m_arithmeticAverage) + "<br>" +
				tr("Geometric average: ")	+ QString::number(m_geometricAverage) + "<br>" +
				tr("Median: ")				+ QString::number(m_median) + "<br>" +
				tr("Mode: ")				+ QString::number(m_mode)
				);
	ui->gridLayout->addWidget(CentralTendencyLabel, 2, 0, Qt::AlignLeft | Qt::AlignVCenter);

	QLabel *DispersionMeasurementLabel = new QLabel(this);
	DispersionMeasurementLabel->setTextFormat(Qt::RichText);
	DispersionMeasurementLabel->setText(
				tr("<b>Measures of disperion:</b><br>"
				"Range: ")					+ QString::number(m_range)					+ "<br>" +
				tr("Standard deviation: ")	+ QString::number(m_standardDeviation)		+ "<br>" +
				tr("Variance: ")			+ QString::number(m_variance)				+ "<br>" +
				tr("Typical deviation: ")	+ QString::number(m_typicalDeviation)		+ "<br>" +
				tr("Cft. of variation: ")	+ QString::number(m_varianceCoefficient)	+ "% <br>" +
				tr("Interquartile range: ")	+ QString::number(m_interquartileRange)		+ "<br>" +
				tr("Interqrt. deviation: ")	+ QString::number(m_interquartileDeviation) + "<br>" +
				tr("Pearson Cft.: ")		+ QString::number(m_coefficientPearson, 'f')	+ "<br>" +
				tr("Bowley Cft.: ")			+ QString::number(m_coefficientBowley, 'f')		+ "<br>" +
				tr("Kurtosis Cft.: ")		+ QString::number(m_coefficientKurtosis, 'f')	+
				" (" + getShape() + ")"
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
		m_totalElements += *(ItrFreq);	// Gets the total number of elements in the table.
	}
	m_arithmeticAverage = sumForAAvg / m_totalElements;
	m_geometricAverage = pow(10, (sumForGAvg / m_totalElements));
}

void ClassIntervalFreqT::calculateTrueMedian()
{
	if(m_rawNumericData.size() % 2 != 0)
		m_median = m_rawNumericData.at((int)m_rawNumericData.size() / 2);
	else
	{
		double temp1 = m_rawNumericData.at(m_rawNumericData.size() / 2);
		double temp2 = m_rawNumericData.at((m_rawNumericData.size() / 2) - 1);
		m_median = (temp1 + temp2) / 2;
	}
}

void ClassIntervalFreqT::calculateTrueMode()
{
	std::vector<double>::const_iterator exItr(m_rawNumericData.begin());
	int exOcurrence(0);
	for(; exItr != m_rawNumericData.end(); exItr++)
	{
		std::vector<double>::const_iterator inItr(exItr);
		double tempVal(*exItr);
		int inOcurrence(0);

		for(; inItr != m_rawNumericData.end(); inItr++)
		{
			if(*inItr == tempVal)
				inOcurrence++;
			else
				break;
		}

		if(inOcurrence > exOcurrence)
		{
			m_mode = tempVal;
			exOcurrence = inOcurrence;
		}
	}
}

_vct<double> ClassIntervalFreqT::calculateAllDeviations()
{
	/* The deviation is the result of absolutely subtracting the arithmetic average to each class mark. */
	_vct<int>::const_iterator itrMark = m_classMarks.begin();
	_vct<double> deviationTemp;

	for(; itrMark != m_classMarks.end(); itrMark++)
		deviationTemp.push_back(std::abs(*itrMark - m_arithmeticAverage));

	return deviationTemp;
}

void ClassIntervalFreqT::calculateDispersion(_vct<double> deviation, opType type)
{
	/* Gets the dispersion using the deviation vector. It elevates each value of the
	 * deviation to the respective value and multiplies it by the respective absolute
	 * frequency.
	 */

	m_range = m_rawNumericData.at(m_rawNumericData.size() - 1) - m_rawNumericData.at(0);

	double dvSum(0);
	_vct<double>::const_iterator itrDev = deviation.begin();
	_vct<int>::const_iterator itrFreq = m_absoluteFreq.begin();

	switch(type)
	{
	case opType::TYPE_DEVIATION:	// Calculate standard deviation.
		for(; itrDev != deviation.end(); itrDev++)
			dvSum += *itrDev * *(itrFreq++);
		m_standardDeviation = dvSum / m_totalElements;
		break;

	case opType::TYPE_VARIANCE:		// Calculate variance.
		for(; itrDev != deviation.end(); itrDev++)
			dvSum += pow(*itrDev, 2) * *(itrFreq++);
		m_variance = dvSum / m_totalElements;
		m_typicalDeviation = sqrt(m_variance);
		m_varianceCoefficient = (m_typicalDeviation / m_arithmeticAverage) * 100;
		break;

	case opType::TYPE_KURTOSIS:		// Calculate Kurtosis.
		for(; itrDev != deviation.end(); itrDev++)
			dvSum += pow(*itrDev, 4) * *(itrFreq++);
		m_coefficientKurtosis = dvSum / m_totalElements;
		break;

	default:
		return;
	}
}

QString ClassIntervalFreqT::getShape()
{
	/* Gets the shape of the Kurtosis. */
	double shape;
	shape = m_coefficientKurtosis / pow(m_variance, 2);
	if(shape < 3)
		return tr("Platykurtic");
	if(shape == 3)
		return tr("Mesokurtic");
	else
		return tr("Leptokurtic");
}

void ClassIntervalFreqT::calculateCoefficients()
{
	m_coefficientPearson = (3 * (m_arithmeticAverage - m_median)) / m_typicalDeviation;
	m_coefficientBowley = (m_quartiles.at(2) + m_quartiles.at(0) - (2 * m_median)) /
			(m_quartiles.at(2) - m_quartiles.at(0));
}

double ClassIntervalFreqT::positionConstant(int position, posType type)
{
	float temp = ++position * m_totalElements;
	// Since arrays start at 0, we add 1 to position for math reasons.

	switch(type)
	{
	case posType::QUARTILE:
		return std::round((temp / 4));

	case posType::SEXTILE:
		return std::round((temp / 6));

	case posType::DECILE:
		return std::round((temp / 10));

	case posType::PERCENTILE:
		return std::round((temp / 100));

	default:
		return 0;
	}
}

int ClassIntervalFreqT::positionCalculations(const int positionConst)
{
	// NOTE: Placeholder algorithm.
	_vct<int>::const_iterator frItr = m_accAbsoluteFreq.begin();
	int lowerValue = 0, higherValue = 0;
	bool usingRange = true;

	for(; frItr != m_accAbsoluteFreq.end(); frItr++)
	{
		// This will set a range in the m_accAbsoluteFreq vector where selectedACMFreq fits.
		// Then it determines the closer limit and chooses that one.
		if(*frItr == positionConst)
		{
			// Since the value is found, there's no need to set a range.
			usingRange = false;
			break;
		}
		if(*frItr < positionConst)
		{
			lowerValue = *frItr;
			continue;
		}

		higherValue = *frItr;
		break;
	}

	int selectedACMFreq = positionConst;
	if(usingRange)
	{
		int lowerDif = std::abs(positionConst - lowerValue);
		int higherDif = std::abs(positionConst - higherValue);

		higherDif > lowerDif ? selectedACMFreq = lowerValue : selectedACMFreq = higherValue;
		// The selected Accumulated Frequency will be the range limit that is closer to positionConst;
	}

	frItr = m_accAbsoluteFreq.begin();
	int freqPosition = 0;
	for(; frItr != m_accAbsoluteFreq.end(); frItr++)
	{
		if(*frItr == selectedACMFreq)
		{
			freqPosition = std::distance(m_accAbsoluteFreq.cbegin(), frItr);
			// This gets the index of the selectedACMFreq.
			break;
		}
	}
	
	return freqPosition;
}

void ClassIntervalFreqT::positionTrends(posType type)
{
	// Excuse to use a Lambda <3.
	auto getIndexes = [this](int position, int freqPosition) -> double
	{
		_oda medianLimit = m_allClassIntervals.at(freqPosition);
		int lowerLimit = medianLimit.at(0);
		int rawFreqMedian = m_absoluteFreq.at(freqPosition);
		int accFreqMedianM1 = 0;

		/* NOTE: Check the math. If the selected Accumulated Frequency Median is the first one, then the one
		* before is 0.
		*/
		if(freqPosition > 0)
			accFreqMedianM1 = m_accAbsoluteFreq.at(freqPosition - 1);

		return (static_cast<double>(position) - accFreqMedianM1) / rawFreqMedian * m_classInterval + lowerLimit;
	};

	switch(type)
	{
	case posType::QUARTILE:
		for(int crn = 0; crn < 4; crn++)
		{
			const int position = positionConstant(crn, posType::QUARTILE);
			int freqPosition = positionCalculations(position);
			double quartile = getIndexes(position, freqPosition);
			m_quartiles.at(crn) = quartile;
		}
		break;

	case posType::SEXTILE:
		for(int crn = 0; crn < 6; crn++)
		{
			const int position = positionConstant(crn, posType::SEXTILE);
			int freqPosition = positionCalculations(position);
			double sextile = getIndexes(position, freqPosition);
			m_sextiles.at(crn) = sextile;
		}
		break;

	case posType::DECILE:
		for(int crn = 0; crn < 10; crn++)
		{
			const int position = positionConstant(crn, posType::DECILE);
			int freqPosition = positionCalculations(position);
			double decile = getIndexes(position, freqPosition);
			m_deciles.at(crn) = decile;
		}
		break;
	}
}

/* The parameter is int instead of posType due to connect() reasons. */
void ClassIntervalFreqT::printPosition(int type)
{
	QMessageBox *msgbx = new QMessageBox(this);
	QString message;

	switch(type)
	{
	case static_cast<int>(posType::QUARTILE):

		for(int crn = 0; crn < 4; crn++)
			message.append("Quartile #" + QString::number(crn + 1) + ": " +
						   QString::number(std::round(m_quartiles.at(crn))) + "\n");

		msgbx->setWindowTitle("Quartiles");
		msgbx->setText(message);
		msgbx->exec();
		break;

	case static_cast<int>(posType::SEXTILE):
		for(int crn = 0; crn < 6; crn++)
			message.append("Sextile #" + QString::number(crn + 1) + ": " +
						   QString::number(std::round(m_sextiles.at(crn))) + "\n");

		msgbx->setWindowTitle("Sextiles");
		msgbx->setText(message);
		msgbx->exec();
		break;

	case static_cast<int>(posType::DECILE):
		for(int crn = 0; crn < 10; crn++)
			message.append("Decile #" + QString::number(crn + 1) + ": " +
						   QString::number(std::round(m_deciles.at(crn))) + "\n");

		msgbx->setWindowTitle("Deciles");
		msgbx->setText(message);
		msgbx->exec();
		break;

	default:
		return;
	}
}
