#ifndef SIMPLEFREQG_H
#define SIMPLEFREQG_H

#include <QDialog>

namespace Ui {
class SimpleFreqG;
}

class SimpleFreqG : public QDialog
{
	Q_OBJECT

public:
	explicit SimpleFreqG(QWidget *parent = 0);
	~SimpleFreqG();

private:
	Ui::SimpleFreqG *ui;
};

#endif // SIMPLEFREQG_H
