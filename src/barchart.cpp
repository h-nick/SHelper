#include <QDebug>
#include <QtCharts/qbarcategoryaxis.h>
#include <QtCharts/qbarseries.h>
#include <QtCharts/qchartview.h>
#include <QtCharts/qbarset.h>
#include <QtCharts/qchart.h>
#include "include/barchart.h"
#include "ui_barchart.h"

// TODO: barChart will be the shared class for SimpleFreqT and ClassIntervalFreqT to generate shared barsets.
// As of right now, ClassIntervalFreqG is in charge of that.
using namespace QtCharts;

barChart::barChart(_vct<double> variables, _vct<int> absFreq, QWidget *parent) : QDialog(parent), ui(new Ui::barChart)
{
	ui->setupUi(this);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

barChart::barChart(_vct<_oda> classFreq, _vct<int> absFreq, QWidget *parent) : QDialog(parent), ui(new Ui::barChart)
{
	ui->setupUi(this);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

barChart::~barChart()
{
	delete ui;
}

