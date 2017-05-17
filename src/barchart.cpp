#include <QDebug>
#include <QtCharts/qbarseries.h>
#include <QtCharts/qchart.h>
#include "include/barchart.h"
#include "ui_barchart.h"

BarChart::BarChart(_vct<double> variables, _vct<int> absFreq, QWidget *parent)
					: m_absFreq(absFreq), QDialog(parent), ui(new Ui::BarChart)
{
	ui->setupUi(this);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
	this->setWindowTitle("Bar Chart");
	generateSetSimple(variables);
}

BarChart::BarChart(_vct<_oda> classInt, _vct<int> absFreq, QWidget *parent)
					: m_absFreq(absFreq), QDialog(parent), ui(new Ui::BarChart)
{
	ui->setupUi(this);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
	this->setWindowTitle("Histogram");
	generateSetCI(classInt);
}

BarChart::~BarChart()
{
	delete ui;
}

void BarChart::generateBar(_vct<QBarSet *> &barSet)
{
	QBarSeries *barSeries = new QBarSeries(this);
	_vct<QBarSet *>::const_iterator barSetItr = barSet.begin();

	for(; barSetItr != barSet.end(); barSetItr++)
		barSeries->append(*barSetItr);

	QChart *chart = new QChart();
	chart->addSeries(barSeries);
	chart->setAnimationOptions(QChart::SeriesAnimations);
	chart->createDefaultAxes();
	chart->legend()->setAlignment(Qt::AlignBottom);
	chart->setTheme(QChart::ChartThemeQt);
	chart->setAttribute(Qt::WA_DeleteOnClose);

	ui->graphShow->setChart(chart);
}

void BarChart::generateSetSimple(_vct<double> variables)
{
	_vct<double>::const_iterator ItrVa = variables.begin();
	_vct<int>::const_iterator ItrFr = m_absFreq.begin();

	_vct<QBarSet *> barSet;
	int crn = 0;
	for(; ItrVa != variables.end(); ItrVa++)
	{
		barSet.push_back(new QBarSet(QString::number(*ItrVa), this));
		*(barSet.at(crn++)) << *(ItrFr++);
	}

	generateBar(barSet);
}

void BarChart::generateSetCI(_vct<_oda> classInt)
{
	_vct<_oda>::const_iterator ItrCI = classInt.begin();
	_vct<int>::const_iterator ItrFr = m_absFreq.begin();

	_vct<QBarSet *> barSet;
	int crn = 0;
	for(; ItrCI != classInt.end(); ItrCI++)
	{
		_oda temp = *(ItrCI);
		barSet.push_back(new QBarSet(QString::number(temp.at(0)), this));
		*(barSet.at(crn++)) << *(ItrFr++);
	}
	generateBar(barSet);
}
