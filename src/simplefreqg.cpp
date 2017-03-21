#include <QtCharts/qchart.h>
#include "include/simplefreqg.h"
#include "ui_simplefreqg.h"

using namespace QtCharts;

SimpleFreqG::SimpleFreqG(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SimpleFreqG)
{
	ui->setupUi(this);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
	connect(ui->button_close, SIGNAL(pressed()), this, SLOT(close()));
}

SimpleFreqG::~SimpleFreqG()
{
	delete ui;
}
