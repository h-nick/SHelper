#ifndef SHELPER_H
#define SHELPER_H

#include <QMainWindow>

namespace Ui {
class Shelper;
}

class Shelper : public QMainWindow
{
	Q_OBJECT

public:
	explicit Shelper(QWidget *parent = 0);
	~Shelper();

private slots:
	void callSimpleFreqT();

private:
	Ui::Shelper *ui;
};

#endif // SHELPER_H
