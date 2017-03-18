#include "include/simplefreqt.h"
#include "ui_simplefreqt.h"

SimpleFreqT::SimpleFreqT(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SimpleFreqT)
{
	ui->setupUi(this);
}

SimpleFreqT::~SimpleFreqT()
{
	delete ui;
}
