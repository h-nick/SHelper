#ifndef SHELPER_H
#define SHELPER_H

#include <QMainWindow>
#include <QCloseEvent>

template<class T>
using _vct = std::vector<T>;

namespace Ui {
class Shelper;
}

class Shelper : public QMainWindow
{
	Q_OBJECT

public:
	explicit Shelper(QWidget *parent = 0);
	~Shelper();

protected:
	void closeEvent(QCloseEvent *event);

private slots:
	void callSimpleFreqT();
	void callClassIntervalFreqT();
	void showAbout();
	void changeLang();
	void test();

private:
	Ui::Shelper *ui;
	_vct<double> obtainData();
};

#endif // SHELPER_H
