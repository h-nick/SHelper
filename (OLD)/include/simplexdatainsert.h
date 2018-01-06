#ifndef SIMPLEXDATAINSERT_H
#define SIMPLEXDATAINSERT_H

#include <QDialog>

namespace Ui {
class SimplexDataInsert;
}

class SimplexDataInsert : public QDialog
{
	Q_OBJECT

public:
	explicit SimplexDataInsert(QWidget *parent = 0);
	~SimplexDataInsert();

private:
	Ui::SimplexDataInsert *ui;
};

#endif // SIMPLEXDATAINSERT_H
