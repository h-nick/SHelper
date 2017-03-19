#include "include/simplefreqg.h"
#include "ui_simplefreqg.h"

SimpleFreqG::SimpleFreqG(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SimpleFreqG)
{
	ui->setupUi(this);

	connect(ui->button_return, SIGNAL(pressed()), this, SLOT(close()));
}

SimpleFreqG::~SimpleFreqG()
{
	delete ui;
}
