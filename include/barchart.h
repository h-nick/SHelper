#ifndef BARCHART_H
#define BARCHART_H

#include <QDialog>
#include <array>

template<typename T>
using _vct = std::vector<T>;
using _oda = std::array<int, 2>;

namespace Ui {
class barChart;
}

class barChart : public QDialog
{
	Q_OBJECT

public:
	explicit barChart(_vct<double> variables, _vct<int> absFreq, QWidget *parent = 0);
	explicit barChart(_vct<_oda> classFreq, _vct<int> absFreq, QWidget *parent = 0);
	~barChart();

private:
	Ui::barChart *ui;
};

#endif // BARCHART_H
