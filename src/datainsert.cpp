#include <QDebug>
#include <QString>
#include <vector>
#include "include/datainsert.h"
#include "ui_datainsert.h"

DataInsert::DataInsert(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DataInsert)
{
	ui->setupUi(this);

	connect(ui->button_cancel, SIGNAL(pressed()), this, SLOT(close()));
	connect(ui->button_OK, SIGNAL(pressed()), this, SLOT(StatisticalData()));
}

DataInsert::~DataInsert()
{
	delete ui;
}

const _vct<double> & DataInsert::getVectorData() const
{
	return m_numericData;
}

void DataInsert::closeEvent(QCloseEvent *event)
{
	// FIXME: When this dialog is canceled/closed, the program crashes. Fix it.
}

void DataInsert::StatisticalData()
{
	/*	FIXME: QDoubleValidator kinda works. But returns Not-Acceptable if there's a newline. Perhaps
	 *	QValidator should be used instead or perhaps the way the data values are entered should be changed.
	 */

	// Gets all the written text on the QPlainTextEdit.
	QString data = ui->values->toPlainText();
	// Separates the string into lines.
	QStringList string_lines = data.split("\n", QString::SkipEmptyParts);
	// Adds each value of the stringlist to the vector.
	foreach(QString data, string_lines)
		m_numericData.push_back(data.toDouble());
	this->close();
}
