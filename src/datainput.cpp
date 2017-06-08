#include <QDebug>
#include <QSignalMapper>
#include <QString>
#include <QLabel>
#include "include/datainput.h"
#include "ui_datainput.h"

// FIXME: There's a memory leak somewhere around here.
DataInput::DataInput(opType type, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DataInput)
{
	ui->setupUi(this);
	QSignalMapper *map = new QSignalMapper(this);
	connect(map, SIGNAL(mapped(QWidget*)), this, SLOT(statisticalData(QWidget*)));
	connect(ui->buttonCancel, SIGNAL(pressed()), this, SLOT(close()));
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

	switch(type)
	{
	case opType::TYPE_STATISTIC:
		{
			this->setWindowTitle("Inert statistical data");
			QLabel *info = new QLabel(this);
			info->setText("Insert all the numeric values for the table.\n"
						  "Each value must be in a line by itself.\n"
						  "Use a dot (.) as the decimal denominator.\n");
			QTextEdit *textEdit = new QTextEdit(this);

			ui->mainLayout->addWidget(textEdit, 1, 0, Qt::AlignCenter);
			ui->mainLayout->addWidget(info, 0, 0, Qt::AlignCenter);

			connect(ui->buttonProceed, SIGNAL(pressed()), map, SLOT(map()));
			map->setMapping(ui->buttonProceed, textEdit);
		}
		break;
	case opType::TYPE_LINEARPROGRAMMING:
		{
			this->setWindowTitle("Insert linear programming data");

		}
		break;
	}
}

DataInput::~DataInput()
{
	delete ui;
}

std::vector<double> DataInput::getStatisticalData()
{
	return m_statisticalData;
}

void DataInput::linearProgrammingData()
{

}

void DataInput::statisticalData(QWidget *textEdit)
{
	// Gets all the written text on the QPlainTextEdit.
	QString data = static_cast<QTextEdit *>(textEdit)->toPlainText();

	// Separates the string into lines.
	QStringList lines = data.split("\n", QString::SkipEmptyParts);

	// Adds each value of the QStringList to the data vector.
	foreach(QString data, lines)
		m_statisticalData.push_back(data.toDouble());
	this->close();
}
