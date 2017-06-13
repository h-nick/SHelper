#include "include/lpgraphicalm.h"
#include "ui_lpgraphicalm.h"

LPGraphicalM::LPGraphicalM(std::vector<double> X, std::vector<double> Y, std::vector<double> Z, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::LPGraphicalM)
{
	ui->setupUi(this);
}

LPGraphicalM::~LPGraphicalM()
{
	delete ui;
}
