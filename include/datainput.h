#ifndef DATAINPUT_H
#define DATAINPUT_H

#include <QDialog>

namespace Ui {
class DataInput;
}

class DataInput : public QDialog
{
	Q_OBJECT

public:
	explicit DataInput(QWidget *parent = 0);
	~DataInput();

private:
	Ui::DataInput *ui;
};

#endif // DATAINPUT_H
