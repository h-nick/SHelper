#include <QDebug>
#include <QMessageBox>
#include <QTranslator>
#include <QDir>
#include "ui_shelper.h"
#include "include/shelper.h"
#include "include/simplefreqt.h"
#include "include/classintervalfreqt.h"
#include "include/aboutdialog.h"
#include "include/settingsconfig.h"

Shelper::Shelper(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Shelper)
{
	ui->setupUi(this);
	ui->retranslateUi(this);

	connect(ui->button_simplefreq, SIGNAL(pressed()), this, SLOT(callSimpleFreqT()));
	connect(ui->button_classintervalfreq, SIGNAL(pressed()), this, SLOT(callClassIntervalFreqT()));
	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
	connect(ui->actionLanguage, SIGNAL(triggered()), this, SLOT(changeLang()));
}

Shelper::~Shelper()
{
	delete ui;
}

void Shelper::changeLang()
{

}

void Shelper::showAbout()
{
	AboutDialog about(this);
	about.exec();
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

_vct<double> Shelper::obtainStatisticalData(DataInput::opType type)
{
	DataInput allData(type, this);
	allData.exec();
	return allData.getStatisticalData();
}

void Shelper::callSimpleFreqT()
{
    _vct<double> temp = obtainStatisticalData(DataInput::opType::TYPE_STATISTIC);
	if (temp.empty())
		return;	// If the DataInput window was closed, it will return an empty vector and won't call SimpleFreqT.

	SimpleFreqT *simpleTable = new SimpleFreqT(temp);
	simpleTable->show();
	simpleTable->setAttribute(Qt::WA_DeleteOnClose);
}

void Shelper::callClassIntervalFreqT()
{
    _vct<double> temp = obtainStatisticalData(DataInput::opType::TYPE_STATISTIC);
	if (temp.empty())
		return;	// If the DataInput window was closed, it will return an empty vector and won't call ClassIntervalFreqT.

	ClassIntervalFreqT *intFreqTable = new ClassIntervalFreqT(temp);
	intFreqTable->show();
	intFreqTable->setAttribute(Qt::WA_DeleteOnClose);
}