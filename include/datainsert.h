#ifndef DATAINSERT_H
#define DATAINSERT_H

#include <QDialog>
#include <QValidator>
#include <QCloseEvent>

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

protected:
	void closeEvent(QCloseEvent *);

private slots:
	void StatisticalData();

private:
	Ui::DataInsert *ui;
	_vct<double> m_numericData;
};

#endif // DATAINSERT_H
