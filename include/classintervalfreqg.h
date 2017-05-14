#ifndef CLASSINTERVALFREQG_H
#define CLASSINTERVALFREQG_H

#include <QDialog>
#include <QtCharts/qbarset.h>
#include <QtCharts/qchart.h>
#include <array>

using namespace QtCharts;

template<typename T>
using _vct = std::vector<T>;
using _oda = std::array<int, 2>;

namespace Ui {
class ClassIntervalFreqG;
}

class ClassIntervalFreqG : public QDialog
{
	Q_OBJECT

public:
	explicit ClassIntervalFreqG(_vct<_oda> & classIntervals, _vct<int> & absoluteFreqs, QWidget *parent = 0);
	~ClassIntervalFreqG();

private:
	Ui::ClassIntervalFreqG *ui;
	_vct<_oda> m_allClassIntervals;
	_vct<int> m_absoluteFreq;

	void generateBarSet();
	void generateBar(_vct<QBarSet *> &barSet);
};

#endif // CLASSINTERVALFREQG_H
