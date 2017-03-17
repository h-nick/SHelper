#ifndef DATAINSERT_H
#define DATAINSERT_H

#include <QDialog>

namespace Ui {
class DataInsert;
}

class DataInsert : public QDialog
{
	Q_OBJECT

public:
	explicit DataInsert(QWidget *parent = 0);
	~DataInsert();

private:
	Ui::DataInsert *ui;
};

#endif // DATAINSERT_H
