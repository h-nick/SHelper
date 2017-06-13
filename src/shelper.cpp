#include <QDebug>
#include <QMessageBox>
#include <QTranslator>
#include <QDir>
#include "include/shelper.h"
#include "ui_shelper.h"
#include "include/simplefreqt.h"
#include "include/classintervalfreqt.h"
#include "include/aboutdialog.h"

Shelper::Shelper(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Shelper)
{
	ui->setupUi(this);

	connect(ui->button_simplefreq, SIGNAL(pressed()), this, SLOT(callSimpleFreqT()));
	connect(ui->button_classintervalfreq, SIGNAL(pressed()), this, SLOT(callClassIntervalFreqT()));
	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
	connect(ui->actionLanguage, SIGNAL(triggered()), this, SLOT(changeLang()));
	connect(ui->button_LPgraphical, SIGNAL(pressed()), this, SLOT(lpGraphical()));
	connect(ui->button_LPSimplex, SIGNAL(pressed()), this, SLOT(lpSimplex()));
}

Shelper::~Shelper()
{
	delete ui;
}

void Shelper::changeLang()
{
	// TODO: Implement this fully. I think this must be moved to main() before QMainWindow constructor.
	QDir masterPath(QApplication::applicationDirPath());
	masterPath.cdUp();
	masterPath.cd(masterPath.absolutePath() + "/locale");

	QTranslator locale;

	if(locale.load("locale_es", masterPath.absolutePath()))
		qDebug() << "successful";
	else
		qDebug() << "error";

	qApp->installTranslator(&locale);

	ui->retranslateUi(this);
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

void Shelper::obtainLPGData(DataInput::opType type,
							std::vector<double> &X, std::vector<double> &Y, std::vector<double> &Obj)
{
	DataInput allData(type, this);
	allData.exec();
}

void Shelper::callSimpleFreqT()
{
	SimpleFreqT simpleTable(obtainStatisticalData(DataInput::opType::TYPE_STATISTIC), this);
	simpleTable.show();
}

void Shelper::callClassIntervalFreqT()
{
	ClassIntervalFreqT intFreqTable(obtainStatisticalData(DataInput::opType::TYPE_STATISTIC), this);
	intFreqTable.show();
}

// NOTE: Placeholders!
void Shelper::lpGraphical()
{
	std::vector<double> X, Y, Obj;
	obtainLPGData(DataInput::opType::TYPE_LPGRAPHICAL, X, Y, Obj);
}

void Shelper::lpSimplex()
{
	std::vector<double> X, Y, Obj;
	obtainLPGData(DataInput::opType::TYPE_LPGENERAL, X, Y, Obj);
}

void Shelper::lpDual()
{

}
