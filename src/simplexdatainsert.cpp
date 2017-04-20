#include "simplexdatainsert.h"
#include "ui_simplexdatainsert.h"

SimplexDataInsert::SimplexDataInsert(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SimplexDataInsert)
{
	ui->setupUi(this);
}

SimplexDataInsert::~SimplexDataInsert()
{
	delete ui;
}
