#ifndef DATAINSERT_H
#define DATAINSERT_H

#include <QDialog>
#include <QValidator>

template<class T>
using _vct = std::vector<T>;

namespace Ui {
class DataInsert;
}

class DataInsert : public QDialog
{
	Q_OBJECT

public:
	explicit DataInsert(QWidget *parent = 0);
	~DataInsert();

	const _vct<double> & getVectorData() const;

private slots:
	void datainsertion();

private:
	Ui::DataInsert *ui;
	_vct<double> numeric_data;
};

#endif // DATAINSERT_H
