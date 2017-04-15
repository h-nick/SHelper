#ifndef CLASSINTERVALFREQT_H
#define CLASSINTERVALFREQT_H

#include <QWidget>
#include <array>

template<typename T>
using _vct = std::vector<T>;
using _oda = std::array<int, 2>; // One Dimensional Array.

namespace Ui {
class ClassIntervalFreqT;
}

class ClassIntervalFreqT : public QWidget
{
	Q_OBJECT

public:
	explicit ClassIntervalFreqT(_vct<double> &numeric_data, QWidget *parent = 0);
	~ClassIntervalFreqT();

private slots:
	void showFreqPoligon();
	void showHistogram();
	void showOjive();

private:
	Ui::ClassIntervalFreqT *ui;

	_oda m_classIntervalRange; // Holds the class interval range.
	_vct<int> m_absoluteFreq;
	_vct<int> m_accAbsoluteFreq;
	_vct<int> m_classMarks;
	_vct<double> m_relativeFreq;
	_vct<double> m_accRelativeFreq;
	_vct<double> m_relativePrcntgs;
	_vct<double> m_accRelativePrcntgs;
	_vct<double> m_rawNumericData;
	_vct<_oda> m_allClassIntervals; // Holds all the class interval ranges.

	int getTotalRealAmplitude();
	void getClassIntervalRanges();
	void getClassMarks();
	void vectorialCalculations();
	void buildTable();

	template<typename T>
	void makeACMFreqTable(_vct<T> &mainFreq, _vct<T> &ACMFreq);
};

#endif // CLASSINTERVALFREQT_H
