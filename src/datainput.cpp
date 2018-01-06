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
#include <QMessageBox>
#include "include/datainput.h"
#include "ui_datainput.h"

// FIXME: There's a memory leak somewhere around here.
DataInput::DataInput(opType type, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DataInput)
{
	ui->setupUi(this);
	ui->retranslateUi(this);
	QSignalMapper *map = new QSignalMapper(this);
	connect(ui->buttonCancel, SIGNAL(pressed()), this, SLOT(close()));

	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
	QLabel *info = new QLabel(this);
	info->deleteLater();

	if(type == opType::TYPE_STATISTIC) // If the data's going to be used for statistical calculations.
	{
			connect(map, SIGNAL(mapped(QWidget*)), this, SLOT(statisticalData(QWidget*)));
			info->setText(this->tr("Insert all the numeric values for the table.\n"
						  "Each value must be in a line by itself.\n"
						  "Use a dot (.) as the decimal denominator.\n"));
			QTextEdit *textEdit = new QTextEdit(this);

			ui->mainLayout->addWidget(info, 0, 0, Qt::AlignCenter);
			ui->mainLayout->addWidget(textEdit, 1, 0, Qt::AlignCenter);

			connect(ui->buttonProceed, SIGNAL(pressed()), map, SLOT(map()));
			map->setMapping(ui->buttonProceed, textEdit);
	}
	/*else // If the data's going to be used for linear programming calculations.
	{
		/* Generates the formLayout elements to determine the size of the problem
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

		if(type == opType::TYPE_LPGRAPHICAL)
		{
			info->setText(info->text() + "\n2D Graphical method can only have two variables.");
			numOfVars->setRange(2, 2);
			numOfVars->setEnabled(false);
		}
		ui->mainLayout->addWidget(info, 0, 0, Qt::AlignTop);


		/* Lambda to generate the table and calls prepareTable(QWidget *).
		 * A QMetaObject::Connection pointer is used so it can be disconnected later inside the
		 * Lambda (Gets the pointer via copy).
		 *
		QMetaObject::Connection * buttonConn = new QMetaObject::Connection;
		*buttonConn = connect(ui->buttonProceed, &QPushButton::pressed, [=, this]()
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
	}*/
}

void DataInput::closeEvent(QCloseEvent *event)
{
	qDebug() << "DataInput::m_dataIsSet = " << m_dataIsSet;

	if(m_dataIsSet)
		event->accept();
	else
	{
		m_statisticalData.clear();
		m_coefficientGroup.clear();
		event->accept();
		// Clears all stored data so the other functions in the stack don't get called.
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
/*
std::vector<std::vector<double>> DataInput::getLinearProgrammingData()
{
	return m_coefficientGroup;
}

void DataInput::linearProgrammingData(QWidget *table)
{
	QTableWidget *tableptr = static_cast<QTableWidget *>(table);

	// NOTE: This can probably be optimized.
	for(int crnRow = 0; crnRow < tableptr->rowCount(); crnRow++)
	{
		/* Stores each row in a vector. Each vector is then stored in another vector.
		 * Vector 0 corresponds to the Object Function.
		 *
		std::vector<double> variableGroup;
		for(int crnCol = 0; crnCol < tableptr->columnCount()-2; crnCol++)
			variableGroup.push_back(tableptr->item(crnRow, crnCol)->text().toDouble());

		variableGroup.push_back(tableptr->item(crnRow, tableptr->columnCount()-1)->text().toDouble());
		m_coefficientGroup.push_back(variableGroup);
	}
		delete tableptr;
		this->close();
}

void DataInput::prepareTable(QWidget *table)
{
	QTableWidget *tableptr = static_cast<QTableWidget *>(table);
	QStringList tempList;

	// Renames all the columns to have "variable" labels. X1, X2, etc.
	// Also renames the last 2 columns and first row accordingly.
	for(int crn = 0; crn < tableptr->columnCount()-2;)
		tempList.append("X" + QString::number(++crn));
	tempList.append("Rel");
	tempList.append("Result");
	tableptr->setHorizontalHeaderLabels(tempList);

	tempList.clear();
	tempList.append("Obj");
	for(int crn = 1; crn < tableptr->rowCount();)
		tempList.append("R" + QString::number(crn++));
	tableptr->setVerticalHeaderLabels(tempList);

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

	this->resize(500, 300);
}*/

void DataInput::statisticalData(QWidget *textEdit)
{
	// Gets all the written text on the QPlainTextEdit.
	QString data = static_cast<QTextEdit *>(textEdit)->toPlainText();

	// Separates the string into lines.
	QStringList lines = data.split("\n", QString::SkipEmptyParts);

	// Adds each value of the QStringList to the data vector.
	foreach(QString data, lines)
		m_statisticalData.push_back(data.toDouble());

	if (m_statisticalData.size() > 1) // As long as there are more than one element.
	{
		m_dataIsSet = true;
		this->close();
		delete textEdit;
	}
	else
	{
		m_statisticalData.clear();
		QMessageBox::information(this, "Not enough elements", "Please insert more than one element.");
	}
}
