#include <QDebug>
#include <memory>
#include "include/shelper.h"
#include "ui_shelper.h"
#include "include/simplefreqt.h"
#include "include/datainsert.h"

Shelper::Shelper(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Shelper)
{
	ui->setupUi(this);

	connect(ui->button_simplefreq, SIGNAL(pressed()), this, SLOT(callSimpleFreqT()));
}

Shelper::~Shelper()
{
	delete ui;
}

void Shelper::callSimpleFreqT()
{
	std::unique_ptr<DataInsert> alldata(new DataInsert());
	alldata->exec();
}
