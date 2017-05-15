#include <QDebug>
#include <QtCharts/qchart.h>
#include "include/classintervalfreqg.h"
#include "ui_classintervalfreqg.h"

ClassIntervalFreqG::ClassIntervalFreqG(_vct<_oda> & classIntervals, _vct<int> & AbsFreq, QWidget *parent)
	: m_allClassIntervals(classIntervals), m_freq(AbsFreq), QDialog(parent), ui(new Ui::ClassIntervalFreqG)
{
	ui->setupUi(this);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
	generateOjive();
}

ClassIntervalFreqG::ClassIntervalFreqG(_vct<int> &classMarks, _vct<int> &acmAbsFreq, QWidget *parent)
	: m_classMarks(classMarks), m_freq(acmAbsFreq), QDialog(parent), ui(new Ui::ClassIntervalFreqG)
{
	ui->setupUi(this);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
	generateFreqPol();
}

ClassIntervalFreqG::~ClassIntervalFreqG()
{
	delete ui;
}

void ClassIntervalFreqG::generateFreqPol()
{
	QSplineSeries *chartSeries = new QSplineSeries();
	chartSeries->setName("Frequency Polygon");

	_vct<int>::const_iterator marksItr = m_classMarks.begin();
	_vct<int>::const_iterator freqItr = m_freq.begin();

	for(; marksItr != m_classMarks.end(); marksItr++)
		chartSeries->append(*marksItr, *(freqItr++)); //This can be done with a QList.

	generateChart(chartSeries);
}

void ClassIntervalFreqG::generateOjive()
{
	QSplineSeries *chartSeries = new QSplineSeries();
	chartSeries->setName("Ogive");

	_vct<_oda>::const_iterator ItrCI = m_allClassIntervals.begin();
	_vct<int>::const_iterator freqItr = m_freq.begin();

	for(; ItrCI != m_allClassIntervals.end(); ItrCI++)
	{
		_oda temp = *ItrCI;
		chartSeries->append(temp.at(0), *(freqItr++));
	}

	generateChart(chartSeries);
}

void ClassIntervalFreqG::generateChart(QSplineSeries *chartSeries)
{
	QChart *chart = new QChart();
	chart->addSeries(chartSeries);
	chart->setTitle("PLACEHOLDER");
	chart->createDefaultAxes();

	// TODO: Mmmmm... Do something about this... It looks awful.
	std::sort(m_freq.rbegin(), m_freq.rend());
	chart->axisY()->setRange(0, m_freq.at(0) + 1);
	ui->GraphShow->setChart(chart);
}



/*
ClassIntervalFreqG::ClassIntervalFreqG(_vct<_oda> & classIntervals, _vct<int> & freqs, QWidget *parent)
	: QDialog(parent), m_allClassIntervals(classIntervals), m_absoluteFreq(freqs),
	ui(new Ui::ClassIntervalFreqG)
{
	ui->setupUi(this);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

	generateBarSet();
}

ClassIntervalFreqG::~ClassIntervalFreqG()
{
	delete ui;
}

void ClassIntervalFreqG::generateBarSet()
{
	_vct<_oda>::const_iterator ItrCI = m_allClassIntervals.begin();
	_vct<int>::const_iterator ItrFr = m_absoluteFreq.begin();

	_vct<QBarSet *> barSet;
	int crn = 0;
	for(; ItrCI != m_allClassIntervals.end(); ItrCI++)
	{
		_oda temp = *(ItrCI);
		barSet.push_back(new QBarSet(QString::number(temp.at(0)), this));
		*(barSet.at(crn)) << *(ItrFr++);
		crn++;
	}

	generateBar(barSet);
}

void ClassIntervalFreqG::generateBar(_vct<QBarSet *> &barSet)
{
	QBarSeries *barSeries = new QBarSeries(this);
	_vct<QBarSet *>::const_iterator barSetItr = barSet.begin();

	for(; barSetItr != barSet.end(); barSetItr++)
		barSeries->append(*barSetItr);

	QChart *chart = new QChart();
	chart->addSeries(barSeries);
	chart->setTitle("PLACEHOLDER");
	chart->setAnimationOptions(QChart::SeriesAnimations);
	chart->createDefaultAxes();
	chart->legend()->setAlignment(Qt::AlignBottom);
	chart->setTheme(QChart::ChartThemeQt);
	chart->setAttribute(Qt::WA_DeleteOnClose);

	ui->GraphShow->setChart(chart);
}
*/
