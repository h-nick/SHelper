#include <QDebug>
#include <QMessageBox>
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

void Shelper::closeEvent(QCloseEvent *event)
{
	if(QMessageBox(QMessageBox::Warning, tr("Close Shelper?"),
				tr("If you close Shelper, all open tables will be closed. Are you sure you "
				   "want to continue?"), QMessageBox::Yes | QMessageBox::No, this).exec()
			== QMessageBox::Yes)
	{
		qApp->exit(0);
	}
	else
		event->ignore();
}

void Shelper::callSimpleFreqT()
{
	DataInsert * alldata = new DataInsert(this);
	alldata->exec();
	alldata->deleteLater();
	_vct<double> numeric_data = alldata->getVectorData();

	SimpleFreqT * table = new SimpleFreqT(numeric_data);
	table->show();
	table->setAttribute(Qt::WA_DeleteOnClose);
}
