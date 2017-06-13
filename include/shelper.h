#ifndef SHELPER_H
#define SHELPER_H

#include <QMainWindow>
#include <QCloseEvent>
#include "datainput.h"

template<class T>
using _vct = std::vector<T>;

namespace Ui {
class Shelper;
}

class Shelper : public QMainWindow
{
	Q_OBJECT

public:
	explicit Shelper(QWidget *parent = 0);
	~Shelper();

protected:
	void closeEvent(QCloseEvent *event);

private slots:
	void callSimpleFreqT();
	void callClassIntervalFreqT();
	void lpGraphical();
	void lpDual();
	void lpSimplex();
	void showAbout();
	void changeLang();

private:
	Ui::Shelper *ui;
	_vct<double> obtainStatisticalData(DataInput::opType type);
	void obtainLPGData(DataInput::opType type,
					   std::vector<double> &X, std::vector<double> &Y, std::vector<double> &Obj);
	// TODO: obtainLPGData() will have to be modified later to work with Simplex/Dual.
};

#endif // SHELPER_H
