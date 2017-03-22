#ifndef SIMPLEFREQT_H
#define SIMPLEFREQT_H

#include <QWidget>

template<class T>
using _vct = std::vector<T>;

//using dVect = std::vector<double>;	//Substitute to typedef.
//using nVect = std::vector<int>;

namespace Ui {
class SimpleFreqT;
}

class SimpleFreqT : public QWidget
{
	Q_OBJECT

public:
	explicit SimpleFreqT(_vct<double> & numeric_data, QWidget *parent = 0);
	~SimpleFreqT();

private:
	Ui::SimpleFreqT *ui;

	_vct<double> variables;
	_vct<int> absolute_freq;
	_vct<double> relative_freq;
	_vct<int> accumulated_freq;
	_vct<double> accumulated_relative_freq;
	_vct<double> relative_percentage;
	_vct<double> accumulated_percentage;

	void buildTable();
	void vectorialCalculations(_vct<double> &);
	void makeVectorUnique(_vct<double> & vector);
	void makeFrequencyTable(_vct<double> & raw_numeric_data);

	template<typename T>
	void makeACMFreqTable(_vct<T> & mainFreq, _vct<T> & ACMFreq);

private slots:
	void showBarChart();
};

#endif // SIMPLEFREQT_H
