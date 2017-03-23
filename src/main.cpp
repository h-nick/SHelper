#include "include/shelper.h"
#include <QApplication>
#include <QDir>
#include <QTranslator>
#include <QDebug>

/* TODO: makeACMFreqTable should be its own function */

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Shelper w;
	w.show();
	return a.exec();
}
