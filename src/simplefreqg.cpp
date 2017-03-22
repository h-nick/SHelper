#include <QDebug>
#include <QtCharts/qchart.h>
#include <QtCharts/qbarset.h>
#include "include/simplefreqg.h"
#include "ui_simplefreqg.h"

using namespace QtCharts;
using _ptr = std::vector<QBarSet *>;

SimpleFreqG::SimpleFreqG(_vct<double> & variables, _vct<int> & absolute_freq, QWidget *parent) :
	QDialog(parent), m_variables(variables), m_absolute_freq(absolute_freq),
	ui(new Ui::SimpleFreqG)
{
	ui->setupUi(this);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
	connect(ui->button_close, SIGNAL(pressed()), this, SLOT(close()));

	generateSet();
}

SimpleFreqG::~SimpleFreqG()
{
	delete ui;
}

void SimpleFreqG::generateSet()
{
	_vct<double>::iterator dItr = m_variables.begin();

	_ptr barsetPtr;
	barsetPtr.resize(m_variables.size());
	_ptr::iterator pItr = barsetPtr.begin();

	for(; dItr != m_variables.end(); dItr++)
	{
		*pItr = new QBarSet(QString::number(*dItr));
		**pItr << *dItr; /* NOTE: Adds the dItr-dereference to the dereference of the pointer accesed by
						  * dereferencing pItr... This is kinda messy. */
		pItr++;
	}
}
