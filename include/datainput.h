#ifndef DATAINPUT_H
#define DATAINPUT_H

#include <QDialog>
#include <QTextEdit>
#include <QDebug>
#include <QCloseEvent>

namespace Ui {
class DataInput;
}

class DataInput : public QDialog
{
	Q_OBJECT

public:
	enum class opType
	{
		TYPE_STATISTIC,
		TYPE_LPGRAPHICAL,
		TYPE_LPGENERAL
	};


	explicit DataInput(opType type, QWidget *parent = 0);
	~DataInput();
	std::vector<double> getStatisticalData();

private slots:
	void statisticalData(QWidget *textEdit);

private:
	Ui::DataInput *ui;
	std::vector<double> m_statisticalData, m_objFn;
	std::vector<std::vector<double>> m_coefficientGroup;
	void DataInput::closeEvent(QCloseEvent *event);
	bool m_dataIsSet = false;
};
#endif // DATAINPUT_H
