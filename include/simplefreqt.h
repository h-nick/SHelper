#ifndef SIMPLEFREQT_H
#define SIMPLEFREQT_H

#include <QDialog>

template<class T>
using _vct = std::vector<T>;

//using dVect = std::vector<double>;	//Substitute to typedef.
//using nVect = std::vector<int>;

namespace Ui {
class SimpleFreqT;
}

class SimpleFreqT : public QDialog
{
	Q_OBJECT

public:
	explicit SimpleFreqT(_vct<double> & numeric_data, QWidget *parent = 0);
	~SimpleFreqT();

private:
	Ui::SimpleFreqT *ui;
	int absoluteSum = 0;

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
};

#endif // SIMPLEFREQT_H
