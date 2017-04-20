#include "include/shelper.h"
#include <QApplication>
#include <QDir>
#include <QTranslator>
#include <QDebug>

/*
 *	aboutdialog			>>> Shows information about the program and Qt.
 *	classintervalfreq	>>> Calculations and table generation for Class-Interval statistical calculations.
 *	datainser			>>> Data insertion for statistical calculations.
 *	shelper				>>> MainWindow.
 *	simplefreqg			>>>	Graph generation for Simple Frequency statistical calculations.
 *	simplefreqt			>>> Calculations and table generation for Simple Frequency statistical calculations.
 */


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Shelper w;
	w.show();
	return a.exec();
}
