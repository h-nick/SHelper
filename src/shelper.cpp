#include <QDebug>
#include <algorithm>
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
	DataInsert * alldata = new DataInsert(this);
	alldata->exec();
	_vct<double> numeric_data = alldata->getVectorData();

	delete alldata;
	alldata = nullptr;

	SimpleFreqT * table = new SimpleFreqT(numeric_data, this);
	table->exec();
}
