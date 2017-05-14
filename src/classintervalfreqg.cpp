#include <QDebug>
#include <QtCharts/qbarcategoryaxis.h>
#include <QtCharts/qbarseries.h>
#include <QtCharts/qchartview.h>
#include "include/classintervalfreqg.h"
#include "ui_classintervalfreqg.h"

ClassIntervalFreqG::ClassIntervalFreqG(_vct<_oda> & classIntervals,
									   _vct<int> & absoluteFreqs, QWidget *parent)
	: QDialog(parent), m_allClassIntervals(classIntervals), m_absoluteFreq(absoluteFreqs),
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
