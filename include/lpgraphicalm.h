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
	std::vector<QPointF> m_restrictionPoints;
	std::vector<QPointF> m_vertexPoints;

	void determinePoints(std::vector<double> restriction);
	void graphicate();
	void getVertex();
};

#endif // LPGRAPHICALM_H
