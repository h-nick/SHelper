#include <QMessageBox>
#include "include/aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AboutDialog)
{
	ui->setupUi(this);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowCloseButtonHint
						 & ~Qt::WindowContextHelpButtonHint);

	connect(ui->button_return, SIGNAL(pressed()), this, SLOT(close()));
	connect(ui->button_QT, SIGNAL(pressed()), this, SLOT(showAboutQT()));

	ui->labelBuildDate->setText(tr("Build date: ") + __DATE__ + " " + __TIME__);
}

AboutDialog::~AboutDialog()
{
	delete ui;
}

void AboutDialog::showAboutQT()
{
	QMessageBox::aboutQt(this, tr("About QT5"));
}
