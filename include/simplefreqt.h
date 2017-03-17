#ifndef SIMPLEFREQT_H
#define SIMPLEFREQT_H

#include <QDialog>

namespace Ui {
class SimpleFreqT;
}

class SimpleFreqT : public QDialog
{
	Q_OBJECT

public:
	explicit SimpleFreqT(QWidget *parent = 0);
	~SimpleFreqT();

private:
	Ui::SimpleFreqT *ui;
};

#endif // SIMPLEFREQT_H
