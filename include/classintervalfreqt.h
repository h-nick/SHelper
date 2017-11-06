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

private:
	enum class opType
	{
		TYPE_DEVIATION,
		TYPE_VARIANCE,
		TYPE_KURTOSIS
	};

	enum class posType
	{
		QUARTILE,
		SEXTILE,
		DECILE,
		PERCENTILE
	};

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

	double getTotalRealAmplitude();
	bool areThereIntegers();
	void getClassIntervalRanges();
	void getClassMarks();
	void getSingleClassIntervalRange();
	void vectorialCalculations();
	void buildTable();
	void printData();

	// Central trends:
	double m_arithmeticAverage;
	double m_geometricAverage;
	double m_mode = 0;
	double m_median;
	double m_approxMode;
	double m_approxMedian;
	void calculateAverages();
	void calculateTrueMedian();
	void calculateTrueMode();

	// Position trends:
	std::array<double, 4> m_quartiles;
	double m_interquartileRange;
	double m_interquartileDeviation;
	std::array<double, 6> m_sextiles;
	std::array<double, 10> m_deciles;
	std::array<double, 100> m_percentiles;
	double positionConstant(int position, posType type);
	int positionCalculations(const int positionConst);

	// Measures of dispersion:
	double m_range;
	double m_standardDeviation;
	double m_variance;
	double m_typicalDeviation;
	double m_varianceCoefficient;
	double m_coefficientPearson;
	double m_coefficientBowley;
	double m_coefficientKurtosis;
	_vct<double> calculateAllDeviations();
	void calculateDispersion(_vct<double> deviation, opType type);
	QString getShape();
	void calculateCoefficients();

private slots:
	void showFreqPolygon();
	void showHistogram();
	void showOgive();
	void positionTrends(posType type);
	void printPosition(int type);
};
#endif // CLASSINTERVALFREQT_H
