#include <QDebug>
#include <QtCharts/qchart.h>
#include "include/classintervalfreqg.h"
#include "ui_classintervalfreqg.h"

// FIXME: This is showing lines with absolute frequency 0.
ClassIntervalFreqG::ClassIntervalFreqG(_vct<_oda> & classIntervals, _vct<int> & AbsFreq, QWidget *parent)
										: m_allClassIntervals(classIntervals), m_freq(AbsFreq),
										QDialog(parent), ui(new Ui::ClassIntervalFreqG)
{
	ui->setupUi(this);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
	this->setWindowTitle("Ogive");
	generateOgive();
}

ClassIntervalFreqG::ClassIntervalFreqG(_vct<int> &classMarks, _vct<int> &acmAbsFreq, QWidget *parent)
										: m_classMarks(classMarks), m_freq(acmAbsFreq),
										QDialog(parent), ui(new Ui::ClassIntervalFreqG)
{
	ui->setupUi(this);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
	this->setWindowTitle("Frequency Polygon");
	generateFreqPol();
}

ClassIntervalFreqG::~ClassIntervalFreqG()
{
	delete ui;
}

void ClassIntervalFreqG::generateFreqPol()
{
	QSplineSeries *chartSeries = new QSplineSeries();
	_vct<int>::const_iterator marksItr = m_classMarks.begin();
	_vct<int>::const_iterator freqItr = m_freq.begin();

	for(; marksItr != m_classMarks.end(); marksItr++)
		chartSeries->append(*marksItr, *(freqItr++)); //This can be done with a QList.

	chartSeries->setName("Frequency Polygon");
	generateChart(chartSeries);
}

void ClassIntervalFreqG::generateOgive()
{
	QSplineSeries *chartSeries = new QSplineSeries();
	_vct<_oda>::const_iterator ItrCI = m_allClassIntervals.begin();
	_vct<int>::const_iterator freqItr = m_freq.begin();

	for(; ItrCI != m_allClassIntervals.end(); ItrCI++)
	{
		_oda temp = *ItrCI;
		chartSeries->append(temp.at(0), *(freqItr++));
	}

	chartSeries->setName("Ogive");
	generateChart(chartSeries);
}

void ClassIntervalFreqG::generateChart(QSplineSeries *chartSeries)
{
	QChart *chart = new QChart();
	chart->addSeries(chartSeries);
	chart->createDefaultAxes();

	std::sort(m_freq.rbegin(), m_freq.rend());
	// I add 1 at the end to create some slack in the vertical-axis for graphical reasons.
	chart->axisY()->setRange(0, m_freq.at(0) + 1);
	ui->GraphShow->setChart(chart);
}
