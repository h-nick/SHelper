#include "include/shelper.h"
#include "include/main.h"
#include <QApplication>
#include <QTranslator>
#include <QDebug>
#include <qdir.h>
#include <qstring.h>
#include <fstream>
#include <experimental/filesystem>
#include <qmessagebox.h>


/*
 *aboutdialog		>>> Shows information about the program and Qt.
 *accumulator		>>> Holds functions to accumulate all the values of a vector into another progressively.
 *barchar			>>> Bar Chart Graph generation for ClassInterval and SimpleFreq
 *classintervalfreqg>>> Graph generator for ClassIntervalFreqT.
 *classintervalfreqt>>> Calculations and table generation for Class-Interval statistical calculations.
 *datainput			>>> Insertion class for statistical data and linear programming data.
 *lpgraphicalm		>>> Linear programming solver and graph generator.
 *shelper			>>> MainWindow.
 *simplefreqt		>>> Calculations and table generation for Simple Frequency statistical calculations.
 *simplexdatainsert	>>> Insertion class for linear programming data solved by simplex method.
 */

void initConfig(QSettings settingsFile)
{
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv); // QApplication must be initialized before any widget.
	std::ofstream configFile;
	std::string path = QCoreApplication::applicationDirPath().toStdString() + "\\config.ini";

	if(!std::experimental::filesystem::exists(std::experimental::filesystem::path(path)))
		QMessageBox(QMessageBox::Information, QTranslator::tr("New configuration file"),
			QTranslator::tr("A configuration file was not found. A new one will be created.")).exec();

	// Creates the configuration file.
	configFile.open(path, std::ios::out);

	if(!configFile.is_open())
		QMessageBox(QMessageBox::Warning, QTranslator::tr("Can not create file"),
			QTranslator::tr("The configuration file couldn't be created or opened. Check the permissions and try again.")
		).exec();


	Shelper w;
	w.show();
	return a.exec();
}
