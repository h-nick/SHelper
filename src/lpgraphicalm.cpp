#include <QDebug>
#include <QtCharts/qchart.h>
#include <QtCharts/qlineseries.h>
#include "include/lpgraphicalm.h"
#include "ui_lpgraphicalm.h"

using namespace QtCharts;

LPGraphicalM::LPGraphicalM(std::vector<std::vector<double>> coefficientGroup, QWidget *parent) :
	m_coefficientGroup(coefficientGroup), QDialog(parent),
	ui(new Ui::LPGraphicalM)
{
	ui->setupUi(this);

	for(int crn = 1; crn < m_coefficientGroup.size(); crn++)
	{
		std::vector<double> restriction = m_coefficientGroup.at(crn);
		determinePoints(restriction);
	}
	graphicate();
}

LPGraphicalM::~LPGraphicalM()
{
	delete ui;
}

void LPGraphicalM::determinePoints(std::vector<double> restriction)
{
	double X = restriction.at(0);
	double Y = restriction.at(1);
	double Z = restriction.at(2);

	QPointF point(Z/X, Z/Y);
	m_restrictionPoints.push_back(point);
	qDebug() << "Points:" << point.rx() << " : " << point.ry();
}

void LPGraphicalM::graphicate()
{
	QLineSeries *serie = new QLineSeries();
	serie->append(m_restrictionPoints);

	QChart *chart = new QChart();
	chart->addSeries(serie);
	chart->legend()->hide();
	chart->createDefaultAxes();
	ui->chartView->setChart(chart);
}
