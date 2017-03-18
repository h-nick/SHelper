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
	connect(ui->button_OK, SIGNAL(pressed()), this, SLOT(datainsertion()));
}

DataInsert::~DataInsert()
{
	delete ui;
}

void DataInsert::datainsertion()
{
/*	FIXME: QDoubleValidator kinda works. But returns Not-Acceptable if there's a newlines. Perhaps
*	QValidator should be used instead or perhaps the way the data values are entered should be changed.
*/

	QDoubleValidator val(ui->values);
	std::vector<double> numeric_data;
	QString data = ui->values->toPlainText(); // Gets all the written text on the QPlainTextEdit.

	int cont = 0;
	if(val.validate(data, cont) == QValidator::Acceptable)
	{
		QStringList string_lines = data.split("\n", QString::SkipEmptyParts); // Separates the
																		 // string into lines.

		foreach(QString data, string_lines)	// Adds each value of the stringlist to the vector.
			numeric_data.push_back(data.toDouble());

		// Then iterates through it. (This is for debug purposes only).
		std::vector<double>::const_iterator it_vec;
		it_vec = numeric_data.begin();
		while(it_vec != numeric_data.end())
		{
			qDebug() << QString::number(*it_vec);
			it_vec++;
		}
	}
}
