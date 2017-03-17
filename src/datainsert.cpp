#include "datainsert.h"
#include "ui_datainsert.h"

DataInsert::DataInsert(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DataInsert)
{
	ui->setupUi(this);
}

DataInsert::~DataInsert()
{
	delete ui;
}
