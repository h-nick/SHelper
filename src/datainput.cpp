#include <QDebug>
#include <QSignalMapper>
#include <QString>
#include <QStringList>
#include <QLabel>
#include <QTableWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QComboBox>
#include "include/datainput.h"
#include "ui_datainput.h"

// FIXME: There's a memory leak somewhere around here.
DataInput::DataInput(opType type, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DataInput)
{
	ui->setupUi(this);
	QSignalMapper *map = new QSignalMapper(this);
	connect(ui->buttonCancel, SIGNAL(pressed()), this, SLOT(close()));

	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
	QLabel *info = new QLabel(this);
	info->deleteLater();

	if(type == opType::TYPE_STATISTIC) // If the data's going to be used for statistical calculations.
	{
			connect(map, SIGNAL(mapped(QWidget*)), this, SLOT(statisticalData(QWidget*)));
			this->setWindowTitle("Inert statistical data");
			info->setText("Insert all the numeric values for the table.\n"
						  "Each value must be in a line by itself.\n"
						  "Use a dot (.) as the decimal denominator.\n");
			QTextEdit *textEdit = new QTextEdit(this);

			ui->mainLayout->addWidget(info, 0, 0, Qt::AlignCenter);
			ui->mainLayout->addWidget(textEdit, 1, 0, Qt::AlignCenter);

			connect(ui->buttonProceed, SIGNAL(pressed()), map, SLOT(map()));
			map->setMapping(ui->buttonProceed, textEdit);
	}
	else // If the data's going to be used for linear programming calculations.
	{
		/* Generates the formLayout elements to determine the size of the problem */
		QSpinBox *numOfVars = new QSpinBox(this);
		QSpinBox *numOfRest = new QSpinBox(this);
		QComboBox *objective = new QComboBox(this);
		ui->formLayout->addRow("Number of variables: ", numOfVars);
		ui->formLayout->addRow("Number of restrictions: ", numOfRest);
		ui->formLayout->addRow("Type of operation: ", objective);

		this->setWindowTitle("Insert linear programming data");
		info->setText("Please fill the table with the linear programming decision problem.");
		numOfVars->setRange(1, 99);
		numOfRest->setRange(1, 99);
		QStringList itemsList;
		itemsList.append("Minimize");
		itemsList.append("Maximize");
		objective->addItems(itemsList);

		// If it's going to be used for LP Graphical Method.
		if(type == opType::TYPE_LPGRAPHICAL)
		{
			info->setText(info->text() + "\nGraphical methods can only have two variables.");
			numOfVars->setRange(1, 2);
		}
		ui->mainLayout->addWidget(info, 0, 0, Qt::AlignTop);


		/* Lambda to generate the table and calls prepareTable(QWidget *).
		 * A QMetaObject::Connection pointer is used so it can be disconnected later inside the
		 * Lambda (Gets the pointer via copy).
		 */
		QMetaObject::Connection * buttonConn = new QMetaObject::Connection;
		*buttonConn = connect(ui->buttonProceed, &QPushButton::pressed, this,
				[=, this]()
				{
					 // Disconnects buttonProceed from calling the Lambda again.
					QObject::disconnect(*buttonConn);

					// 2 is added to numOfVars to make extra columns for the result and inequation.
					// 1 is added to numOfRest to make an extra row for the objective function.
					QTableWidget *table = new QTableWidget(numOfRest->text().toInt()+1,
														   numOfVars->text().toInt()+2,
														   this);
					ui->mainLayout->addWidget(table, 0, 0, Qt::AlignTop);
					delete numOfVars;
					delete numOfRest;
					delete buttonConn;

					// Reassigns buttonProceed to call linearProgrammingData(QWidget *table).
					connect(map, SIGNAL(mapped(QWidget*)), this, SLOT(linearProgrammingData(QWidget*)));
					connect(ui->buttonProceed, SIGNAL(pressed()), map, SLOT(map()));
					map->setMapping(ui->buttonProceed, table);

					// Prepares the table to accept the data.
					prepareTable(table);
				});
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

void DataInput::linearProgrammingData(QWidget *table)
{

}

void DataInput::prepareTable(QWidget *table)
{
	QTableWidget *tableptr = static_cast<QTableWidget *>(table);
	QStringList tempList;

	// Renames all the columns to have "variable" labels. X1, X2, etc.
	// Also renames the last 2 columns accordingly.
	for(int crn = 0; crn < tableptr->columnCount()-2;)
	{
		tempList.append("X" + QString::number(++crn));
	}
	tempList.append("Rel");
	tempList.append("Result");
	tableptr->setHorizontalHeaderLabels(tempList);

	// Adds a QComboBox to the Rel column.
	for(int crn = 0; crn < tableptr->rowCount(); crn++)
	{
		QComboBox * relations = new QComboBox(this);
		tempList.clear();
		tempList << "<=" << ">=" << "!=" << "=";
		relations->addItems(tempList);
		if(crn == 0)
		{
			relations->setEnabled(false);
			relations->setCurrentIndex(3);
		}
		tableptr->setCellWidget(crn, tableptr->columnCount()-2, relations);
	}

	// Fixates the first row result column for the objective function.
	QTableWidgetItem *temp = new QTableWidgetItem("0");
	tableptr->setItem(0, tableptr->columnCount()-1, temp);
	temp->setFlags(Qt::ItemIsEnabled);
	temp->setBackgroundColor(Qt::lightGray);
	temp->setTextAlignment(Qt::AlignCenter);
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
	delete textEdit;
}
