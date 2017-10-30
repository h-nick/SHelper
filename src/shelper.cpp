#include <QDebug>
#include <QMessageBox>
#include <QTranslator>
#include <QDir>
#include "include/shelper.h"
#include "ui_shelper.h"
#include "include/simplefreqt.h"
#include "include/classintervalfreqt.h"
#include "include/aboutdialog.h"
#include "include/lpgraphicalm.h"

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
	if (!allData.getFlagSet())
		return allData.getStatisticalData();
	else
		return _vct<double>();	// Returns an empty vector if the DataInput window was closed.
}

_vct<_vct<double>> Shelper::obtainLPGData(DataInput::opType type, _vct<_vct<double>> coefficientGroup)
{
	DataInput allData(type, this);
	allData.exec();
	return allData.getLinearProgrammingData();
}

void Shelper::callSimpleFreqT()
{
    _vct<double> temp = obtainStatisticalData(DataInput::opType::TYPE_STATISTIC);
	if (temp.empty())
		return;	// If the DataInput window was closed, it will return an empty vector and won't call ClassIntervalFreqT.

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

void Shelper::lpGraphical()
{
	std::vector<std::vector<double>> coefficientGroup;
	LPGraphicalM *lpGraphical = new LPGraphicalM(obtainLPGData(DataInput::opType::TYPE_LPGRAPHICAL,
															   coefficientGroup));
	lpGraphical->show();
	lpGraphical->setAttribute(Qt::WA_DeleteOnClose);
}

// NOTE: Placeholders!
void Shelper::lpSimplex()
{
	std::vector<std::vector<double>> coefficientGroup;
	obtainLPGData(DataInput::opType::TYPE_LPGENERAL, coefficientGroup);
}

void Shelper::lpDual()
{

}
