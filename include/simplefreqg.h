#ifndef SIMPLEFREQG_H
#define SIMPLEFREQG_H

#include <QDialog>

template<typename T>
using _vct = std::vector<T>;

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

};

#endif // SIMPLEFREQG_H
