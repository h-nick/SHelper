#include <QDebug>
#include <QtCharts/qchart.h>
#include <QtCharts/qlineseries.h>
#include "include/lpgraphicalm.h"
#include "ui_lpgraphicalm.h"

using namespace QtCharts;

// TODO: Check the math.
LPGraphicalM::LPGraphicalM(std::vector<std::vector<double>> coefficientGroup, QWidget *parent) :
	m_coefficientGroup(coefficientGroup), QDialog(parent),
	ui(new Ui::LPGraphicalM)
{
	ui->setupUi(this);

	for(unsigned int crn = 1; crn < m_coefficientGroup.size(); crn++)
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

	QPointF pointY(0, Z/Y);
	m_restrictionPoints.push_back(pointY);
	QPointF pointX(Z/X, 0);
	m_restrictionPoints.push_back(pointX);
	qDebug() << "PointY:" << pointY.rx() << " : " <<
				pointY.ry() << "PointX:" << pointX.rx() << " : " << pointX.ry();;
}

void LPGraphicalM::graphicate()
{
	QChart *chart = new QChart();
	std::vector<QPointF>::const_iterator pointItr;
	int restrictionNumber = 1;
	for(pointItr = m_restrictionPoints.begin(); pointItr != m_restrictionPoints.end(); pointItr++)
	{
		QLineSeries *constraint = new QLineSeries();
		constraint->append(*pointItr);
		constraint->append(*(++pointItr));
		constraint->setName("R" + restrictionNumber);
		chart->addSeries(constraint);
	}
	chart->createDefaultAxes();
	ui->chartView->setChart(chart);
}
