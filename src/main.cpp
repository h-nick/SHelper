#include "shelper.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Shelper w;
	w.show();

	return a.exec();
}
