#include "include/shelper.h"
#include <QApplication>
#include <QDir>
#include <QTranslator>
#include <QDebug>

/*
 *aboutdialog		>>> Shows information about the program and Qt.
 *accumulator		>>> Holds functions to accumulate all the values of a vector into another progressively.
 *barchar			>>> Bar Chart Graph generation for ClassInterval and SimpleFreq
 *classintervalfreqt>>> Calculations and table generation for Class-Interval statistical calculations.
 *datainput			>>> Data insertion class.
 *shelper			>>> MainWindow.
 *simplefreqg		>>>	Graph generation for Simple Frequency statistical calculations.
 *simplefreqt		>>> Calculations and table generation for Simple Frequency statistical calculations.
 *
 */


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Shelper w;
	w.show();
	return a.exec();
}
