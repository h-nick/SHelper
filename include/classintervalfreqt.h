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
	void showFreqPolygon();
	void showHistogram();
	void showOgive();

private:
	Ui::ClassIntervalFreqT *ui;

	_vct<int> m_absoluteFreq;
	_vct<int> m_accAbsoluteFreq;
	_vct<int> m_classMarks;
	_vct<double> m_relativeFreq;
	_vct<double> m_accRelativeFreq;
	_vct<double> m_relativePrcntgs;
	_vct<double> m_accRelativePrcntgs;
	_vct<double> m_rawNumericData;
	_vct<_oda> m_allClassIntervals; // Holds all the class interval ranges.
	int m_totalElements = 0;
	int m_classInterval;
	int getTotalRealAmplitude();
	void getClassIntervalRanges();
	void getClassMarks();
	void getSingleClassIntervalRange();
	void vectorialCalculations();
	void buildTable();
	void printData();

	template<typename T>
	void makeACMFreqTable(_vct<T> &mainFreq, _vct<T> &ACMFreq);

	// Central trends:
	double m_arithmeticAverage;
	double m_geometricAverage;
	double m_mode;
	double m_median;
	void calculateAverages();
	void calculateMedian();
	void calculateMode(int lowerLimit);

	// Position trends:
	std::array<double, 4> m_quartiles;
	std::array<double, 6> m_sextiles;
	std::array<double, 10> m_deciles;
	std::array<double, 100> m_percentiles;
	void positionFormula();
	void calculatePosition();

	// Measures of dispersion:
	double m_range;
	double m_standardDeviation;
	double m_variance;
	double m_varianceCoefficient;
	double m_coefficientPearson;
	double m_coefficientBowley;
	double m_coefficientKurtosis;
	_vct<double> calculateAllDeviations();
	void calculateDispersion(_vct<double> deviation, int cType);
	void calculateVariance(_vct<double> deviation);
	void calculateCoefficients(_vct<double> deviation);
};

#endif // CLASSINTERVALFREQT_H
