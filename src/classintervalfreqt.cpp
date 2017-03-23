#include "include/classintervalfreqt.h"
#include "ui_classintervalfreqt.h"

ClassIntervalFreqT::ClassIntervalFreqT(_vct<double> &numeric_data, QWidget *parent) :
	QWidget(parent), m_rawNumericData(numeric_data),
	ui(new Ui::ClassIntervalFreqT)
{
	ui->setupUi(this);
}

ClassIntervalFreqT::~ClassIntervalFreqT()
{
	delete ui;
}

int ClassIntervalFreqT::getTotalRealAmplitude()
{
	return 0; // NOTE: Placeholder.
}

void ClassIntervalFreqT::getClassInterval()
{

}

void ClassIntervalFreqT::getClassMarks()
{

}

void ClassIntervalFreqT::vectorialCalculations()
{

}

void ClassIntervalFreqT::buildTable()
{

}

void ClassIntervalFreqT::showFreqPoligon()
{

}

void ClassIntervalFreqT::showHistogram()
{

}

void ClassIntervalFreqT::showOjive()
{

}
