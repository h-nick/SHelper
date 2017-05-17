#ifndef BARCHART_H
#define BARCHART_H

#include <QDialog>
#include <QtCharts/qbarset.h>
#include <array>

template<typename T>
using _vct = std::vector<T>;
using _oda = std::array<int, 2>;

using namespace QtCharts;

namespace Ui {
class BarChart;
}

class BarChart : public QDialog
{
	Q_OBJECT

public:
	explicit BarChart(_vct<double> variables, _vct<int> absFreq, QWidget *parent = 0);
	explicit BarChart(_vct<_oda> classInt, _vct<int> absFreq, QWidget *parent = 0);
	~BarChart();

private:
	Ui::BarChart *ui;
	_vct<int> m_absFreq;

	void generateSetCI(_vct<_oda> classInt);
	void generateSetSimple(_vct<double> variables);
	void generateBar(_vct<QtCharts::QBarSet *> &barSet);
};

#endif // BARCHART_H
