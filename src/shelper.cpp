#include <QDebug>
#include <QMessageBox>
#include <QTranslator>
#include <QDir>
#include "include/shelper.h"
#include "ui_shelper.h"
#include "include/simplefreqt.h"
#include "include/datainsert.h"
#include "include/aboutdialog.h"

Shelper::Shelper(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Shelper)
{
	ui->setupUi(this);

	connect(ui->button_simplefreq, SIGNAL(pressed()), this, SLOT(callSimpleFreqT()));
	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
	connect(ui->actionLanguage, SIGNAL(triggered()), this, SLOT(changeLang()));
}

Shelper::~Shelper()
{
	delete ui;
}

void Shelper::changeLang()
{
	// TODO: Implement this fully.
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
	AboutDialog *about = new AboutDialog(this);
	about->exec();
	about->setAttribute(Qt::WA_DeleteOnClose);
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
