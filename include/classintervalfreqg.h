#ifndef CLASSINTERVALFREQG_H
#define CLASSINTERVALFREQG_H

#include <QDialog>
#include <QtCharts/qsplineseries.h>
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
	explicit ClassIntervalFreqG(_vct<_oda> & classIntervals, _vct<int> & AbsFreq, QWidget *parent = 0);
	explicit ClassIntervalFreqG(_vct<int> & classMarks, _vct<int> & acmAbsFreq, QWidget *parent = 0);
	~ClassIntervalFreqG();

private:
	Ui::ClassIntervalFreqG *ui;
	_vct<_oda> m_allClassIntervals;
	_vct<int> m_classMarks;
	_vct<int> m_freq;

	void generateFreqPol();
	void generateOjive();
	void generateChart(QSplineSeries *chartSeries);
};

#endif // CLASSINTERVALFREQG_H
