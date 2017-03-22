#ifndef SIMPLEFREQG_H
#define SIMPLEFREQG_H

#include <QDialog>
#include <QtCharts/qbarset.h>
#include <QtCharts/qchart.h>

using namespace QtCharts;

template<typename T>
using _vct = std::vector<T>;

using _ptr = std::vector<QBarSet *>;

namespace Ui {
class SimpleFreqG;
}

class SimpleFreqG : public QDialog
{
	Q_OBJECT

public:
	explicit SimpleFreqG(_vct<double> &variables, _vct<int> &absolute_freq, QWidget *parent = 0);
	~SimpleFreqG();

private:
	Ui::SimpleFreqG *ui;
	_vct<double> m_variables;
	_vct<int> m_absolute_freq;

	void generateSet();
	void generateBar(_ptr & barsetPtr);

};

#endif // SIMPLEFREQG_H
