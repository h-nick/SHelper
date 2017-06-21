#ifndef LPGRAPHICALM_H
#define LPGRAPHICALM_H

#include <QDialog>
#include <QPointF>
#include <QList>

namespace Ui {
class LPGraphicalM;
}

class LPGraphicalM : public QDialog
{
	Q_OBJECT

public:
	explicit LPGraphicalM(std::vector<std::vector<double> > coefficientGroup,
						  QWidget *parent = 0);
	~LPGraphicalM();

private:
	Ui::LPGraphicalM *ui;
	std::vector<std::vector<double>> m_coefficientGroup;
	QList<QPointF> m_restrictionPoints;

	void determinePoints(std::vector<double> restriction);
	void graphicate();
};

#endif // LPGRAPHICALM_H
