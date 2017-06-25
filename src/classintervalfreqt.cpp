#include <QSignalMapper>
#include <QDebug>
#include <QTableWidget>
#include <QLabel>
#include <QMessageBox>
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
	vectorialCalculations();

	connect(ui->buttonFreqPol, SIGNAL(pressed()), this, SLOT(showFreqPolygon()));
	connect(ui->buttonHistogram, SIGNAL(pressed()), this, SLOT(showHistogram()));
	connect(ui->buttonOgive, SIGNAL(pressed()), this, SLOT(showOgive()));

	QSignalMapper *mapper = new QSignalMapper(this);
	connect(mapper, SIGNAL(mapped(int)), this, SLOT(printPosition(int)));

	connect(ui->buttonQuartiles, SIGNAL(pressed()), mapper, SLOT(map()));
	mapper->setMapping(ui->buttonQuartiles, static_cast<int>(posType::QUARTILE));
	connect(ui->buttonSextiles, SIGNAL(pressed()), mapper, SLOT(map()));
	mapper->setMapping(ui->buttonSextiles, (int)posType::SEXTILE);
	connect(ui->buttonDeciles, SIGNAL(pressed()), mapper, SLOT(map()));
	mapper->setMapping(ui->buttonDeciles, (int)posType::DECILE);
	connect(ui->buttonPercentiles, SIGNAL(pressed()), mapper, SLOT(map()));
	mapper->setMapping(ui->buttonPercentiles, (int)posType::PERCENTILE);
}

ClassIntervalFreqT::~ClassIntervalFreqT()
{
	delete ui;
}

// NOTE: This should probably be a template.
int ClassIntervalFreqT::getTotalRealAmplitude()
{
	return m_rawNumericData.at(m_rawNumericData.size() - 1) - m_rawNumericData.at(0) + 1;
	/*	FIXME: Instead of adding 1, it should determine if there's decimals
	 *	in the values and add either 1 or 0.1 accordingly.
	 */
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
	// TODO: This can probably be optimized greatly. Consider this algorithm a placeholder.
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

/*	_vct<_oda>::const_iterator cntCI = m_allClassIntervals.begin();
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
	*/

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
	calculateTrueMedian();
	calculateTrueMedian();

	/* Calculate position trends */
	/*positionFormula(posType::QUARTILE);
	positionFormula(posType::SEXTILE);
	positionFormula(posType::DECILE);
	positionFormula(posType::PERCENTILE);*/

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
	/* Prints all the data below the tableGrid */
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
				"Range: "				+ QString::number(m_range)					+ "<br>"
				"Standard deviation: "	+ QString::number(m_standardDeviation)		+ "<br>"
				"Variance: "			+ QString::number(m_variance)				+ "<br>"
				"Typical deviation: "	+ QString::number(m_typicalDeviation)		+ "<br>"
				"Cft. of variation: "	+ QString::number(m_varianceCoefficient)	+ "% <br>"
				"Interquartile range: "	+ QString::number(m_interquartileRange)		+ "<br>"
				"Interqrt. deviation: "	+ QString::number(m_interquartileDeviation) + "<br>"
				"Pearson Cft.: "		+ QString::number(m_coefficientPearson, 'f')	+ "<br>"
				"Bowley Cft.: "			+ QString::number(m_coefficientBowley, 'f')		+ "<br>"
				"Kurtosis Cft.: "		+ QString::number(m_coefficientKurtosis, 'f')	+
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

void ClassIntervalFreqT::calculateApproximateMedian()
{
	int rawFreqMedian, accFreqMedianM1, lowerLimit;
	_oda medianLimit;
	if(m_absoluteFreq.size() % 2 != 0) // If we have an odd amount of elements.
	{
		rawFreqMedian = m_absoluteFreq.at(std::floor(m_absoluteFreq.size() / 2));
		accFreqMedianM1 = m_accAbsoluteFreq.at(std::floor(m_accAbsoluteFreq.size() / 2) - 1);
		medianLimit = m_allClassIntervals.at(std::floor(m_allClassIntervals.size() / 2));
		lowerLimit = medianLimit.at(0);
	}
	else // If we have an even amount of elements.
	{
		rawFreqMedian = (m_absoluteFreq.at(m_absoluteFreq.size() / 2) +
						 m_absoluteFreq.at((m_absoluteFreq.size() / 2)- 1)) / 2;
		accFreqMedianM1 = (m_accAbsoluteFreq.at(m_accAbsoluteFreq.size() / 2) +
						   m_accAbsoluteFreq.at((m_accAbsoluteFreq.size() / 2) - 1)) / 2;
		medianLimit = m_allClassIntervals.at(m_allClassIntervals.size() / 2);
		_oda medianLimitM1 = m_allClassIntervals.at((m_allClassIntervals.size() / 2) - 1);
		lowerLimit = (medianLimit.at(0) + medianLimitM1.at(0)) / 2;

		/* NOTE: Since the amount of grouped elements is even, I'm calculating everything based
		 * in the arithmetic average values of the grouped data. I don't know if this statistically
		 * correct.
		 */
	}
	m_median = ((((m_totalElements / 2) - accFreqMedianM1) / rawFreqMedian) * m_classInterval) + lowerLimit;
}

void ClassIntervalFreqT::calculateApproximateMode()
{
	// Gets the first biggest element in the absoluteFreq. This should be the most repeated element.
	// FIXME: This will crash if the modal position (FreqItr) is the first or last element of the vector.
	_vct<int>::const_iterator FreqItr = std::max_element(m_absoluteFreq.begin(), m_absoluteFreq.end());
	int modalPos = FreqItr - m_absoluteFreq.begin(); // Gets the index where the iterator is located.
	/* This is done because the index where FreqItr finds the first biggest element in absoluteFreq, is the
	 * same index where the lowerLimit we're looking for is located.
	 */
	_oda lowerLimit = m_allClassIntervals.at(modalPos);
	double tempVal = *FreqItr - *(FreqItr-1);
	m_mode = ((tempVal / (tempVal + (*FreqItr - *(FreqItr+1)))) * m_classInterval) + lowerLimit.at(0);
}

void ClassIntervalFreqT::calculateTrueMedian()
{
	if(m_rawNumericData.size() % 2 != 0)
		m_median = m_rawNumericData.at((m_rawNumericData.size() / 2) - 1);
	else
	{
		double temp1 = m_rawNumericData.at(m_rawNumericData.size() / 2);
		double temp2 = m_rawNumericData.at((m_rawNumericData.size() / 2) - 1);
		m_median = (temp1 + temp2) / 2;
	}
}

void ClassIntervalFreqT::calculateTrueMode()
{
	// TODO: Implement this.
	m_mode = 1;
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
		return "Platykurtic";
	if(shape == 3)
		return "Mesokurtic";
	else
		return "Leptokurtic";
}

void ClassIntervalFreqT::calculateCoefficients()
{
	m_coefficientPearson = (3 * (m_arithmeticAverage - m_median)) / m_typicalDeviation;
	m_coefficientBowley = (m_quartiles.at(2) + m_quartiles.at(0) - (2 * m_median)) /
			(m_quartiles.at(2) - m_quartiles.at(0));
}

double ClassIntervalFreqT::calculatePosition(int position, posType type)
{
	int temp = ++position * m_totalElements;

	switch(type)
	{
	case posType::QUARTILE:
		return (temp / 4);

	case posType::SEXTILE:
		return (temp / 6);

	case posType::DECILE:
		return (temp / 10);

	case posType::PERCENTILE:
		return (temp / 100);

	default:
		return 0;
	}
}

void ClassIntervalFreqT::positionFormula(posType type)
{

	/* This function is used to calculate all the position trends based on the posType parameter passed.
	 * Each one calls calculatePosition() with different arguments.
	 */

	// NOTE: This are the same formulas used in a function above. Try merging them or something.
	// FIXME: Math might be wrong.
	int rawFreqMedian = m_absoluteFreq.at(static_cast<int>(m_absoluteFreq.size() / 2));
	int accFreqMedianM1 = m_accAbsoluteFreq.at(static_cast<int>(m_accAbsoluteFreq.size() / 2) - 1);
	_oda medianLimit = m_allClassIntervals.at(static_cast<int>(m_allClassIntervals.size() / 2));
	int lowerLimit = medianLimit.at(0);

	// FIXME: Reimplement algorithm.
	switch(type)
	{
	/*case posType::QUARTILE:
		_vct<int> positions;
		for(int pos = 0; pos < 4; pos++)
		{
			positions.at(pos)(calculatePosition(position, posType::QUARTILE));
		}
		m_quartiles.at(position - 1) =
				((lowerLimit + calculatePosition(position, posType::QUARTILE) - accFreqMedianM1)
				* m_classInterval) / rawFreqMedian;
		break;
	*/
	case posType::SEXTILE:
		for(int position = 1; position <= 6; position++)
		{
			m_sextiles.at(position - 1) =
					((lowerLimit + calculatePosition(position, posType::SEXTILE) - accFreqMedianM1)
					 * m_classInterval) / rawFreqMedian;
		}
		break;

	case posType::DECILE:
		for(int position = 1; position <= 10; position++)
		{
			m_deciles.at(position - 1) =
					((lowerLimit + calculatePosition(position, posType::DECILE) - accFreqMedianM1)
					 * m_classInterval) / rawFreqMedian;
		}
		break;

	case posType::PERCENTILE:
		for(int position = 1; position <= 100; position++)
		{
			m_percentiles.at(position - 1) =
					((lowerLimit + calculatePosition(position, posType::PERCENTILE) - accFreqMedianM1)
					 * m_classInterval) / rawFreqMedian;
		}
		break;

	default:
		return;
	}

	m_interquartileRange = m_quartiles.at(2) - m_quartiles.at(0);
	m_interquartileDeviation = m_interquartileRange / 2;
}

/* The parameter is int instead of posType due to connect() reasons. I'll try to fix it later. */
void ClassIntervalFreqT::printPosition(int type)
{
	QMessageBox *msgbx = new QMessageBox(this);
	QString message;

	switch(type)
	{
	case posType::QUARTILE:

		for(int crn = 0; crn < 4; crn++)
			message.append("Quartile #" + QString::number(crn + 1) + ": " +
						   QString::number((int)m_quartiles.at(crn)) + "\n");

		msgbx->setWindowTitle("Quartiles");
		msgbx->setText(message);
		msgbx->exec();
		break;

	case posType::SEXTILE:
		for(int crn = 0; crn < 6; crn++)
			message.append("Sextile #" + QString::number(crn + 1) + ": " +
						   QString::number((int)m_sextiles.at(crn)) + "\n");

		msgbx->setWindowTitle("Sextiles");
		msgbx->setText(message);
		msgbx->exec();
		break;

	case posType::DECILE:
		for(int crn = 0; crn < 10; crn++)
			message.append("Decile #" + QString::number(crn + 1) + ": " +
						   QString::number((int)m_deciles.at(crn)) + "\n");

		msgbx->setWindowTitle("Deciles");
		msgbx->setText(message);
		msgbx->exec();
		break;

	case posType::PERCENTILE:
		for(int crn = 0; crn < 20; crn++)
		{
	/*		message.append("Percentile #" + QString::number(crn + 1) + ": " +
/*						   QString::number((int)m_percentiles.at(crn)) + "\n");
		*/
			message.append(
						   "Percentile #" + QString::number(crn + 1) + ": " +
							QString::number((int)m_percentiles.at(crn))		+ "\t" +
							"Percentile #" + QString::number(crn + 21) + ": " +
							QString::number((int)m_percentiles.at(crn + 20)) + "\t" +
							"Percentile #" + QString::number(crn + 41) + ": " +
							QString::number((int)m_percentiles.at(crn + 40)) + "\t" +
							"Percentile #" + QString::number(crn + 61) + ": " +
							QString::number((int)m_percentiles.at(crn + 80)) + "\n");
		}
		msgbx->setWindowTitle("Percentiles");
		msgbx->setText(message);
		msgbx->exec();
		break;

	default:
		return;
	}
}
