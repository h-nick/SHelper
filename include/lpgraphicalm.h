#ifndef LPGRAPHICALM_H
#define LPGRAPHICALM_H

#include <QDialog>

namespace Ui {
class LPGraphicalM;
}

class LPGraphicalM : public QDialog
{
	Q_OBJECT

public:
	explicit LPGraphicalM(std::vector<double> X, std::vector<double> Y, std::vector<double> Z,
						  QWidget *parent = 0);
	~LPGraphicalM();

private:
	Ui::LPGraphicalM *ui;

	std::vector<double> varX, varY, varZ, objFn;
};

#endif // LPGRAPHICALM_H
