#include <QLineEdit>
#include "include/datainput.h"
#include "ui_datainput.h"

DataInput::DataInput(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DataInput)
{
	ui->setupUi(this);

	QLineEdit *lineEdit = new QLineEdit(this);
	ui->mainLayout->addWidget(lineEdit, 0, 0, 0, 0, Qt::AlignCenter);
	lineEdit->deleteLater();
}

DataInput::~DataInput()
{
	delete ui;
}
