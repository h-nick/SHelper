#include "include\settingsconfig.h"
#include "include/shelper.h"
#include <QApplication>
#include <QTranslator>
#include <QDir>
#include <experimental\filesystem>


/*
 *aboutdialog		>>> Shows information about the program and Qt.
 *accumulator		>>> Holds functions to accumulate all the values of a vector into another progressively.
 *barchar			>>> Bar Chart Graph generation for ClassInterval and SimpleFreq
 *classintervalfreqg>>> Graph generator for ClassIntervalFreqT.
 *classintervalfreqt>>> Calculations and table generation for Class-Interval statistical calculations.
 *datainput			>>> Insertion class for statistical data and linear programming data.
 *lpgraphicalm		>>> Linear programming solver and graph generator.
 *SettingsConfig	>>> Class to create and manage settings file.
 *shelper			>>> MainWindow.
 *simplefreqt		>>> Calculations and table generation for Simple Frequency statistical calculations.
 *simplexdatainsert	>>> Insertion class for linear programming data solved by simplex method.
 */

void loadLocale(SettingsConfig *configuration)
{
	QDir masterPath = QCoreApplication::applicationDirPath();
	masterPath.cdUp();
	masterPath.cd(masterPath.absolutePath() + "/locale");

	QTranslator *locale = new QTranslator();
	locale->load(QString(configuration->getLocale()), masterPath.absolutePath());

	qApp->installTranslator(locale);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv); // QApplication must be initialized before any widget.
	SettingsConfig *configuration = new SettingsConfig();
	loadLocale(configuration);
	Shelper w;
	w.show();
	return a.exec();
}
