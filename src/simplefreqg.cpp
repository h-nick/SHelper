#include <QDebug>
#include <QtCharts/qbarcategoryaxis.h>
#include <QtCharts/qbarseries.h>
#include <QtCharts/qchartview.h>
#include "include/simplefreqg.h"
#include "ui_simplefreqg.h"

/* TODO: Most memory leaks of the class have been corrected. But they haven't been checked yet...
 * In other words: Check for memory leaks.
 */

SimpleFreqG::SimpleFreqG(_vct<double> & variables, _vct<int> & absolute_freq, QWidget *parent) :
	QDialog(parent), m_variables(variables), m_absolute_freq(absolute_freq),
	ui(new Ui::SimpleFreqG)
{
	ui->setupUi(this);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
	connect(ui->button_close, SIGNAL(pressed()), this, SLOT(close()));

	generateSet();
}

SimpleFreqG::~SimpleFreqG()
{
	delete ui;
}

void SimpleFreqG::generateSet()
{
	/* dItr iterates through the variables vector which will be used to generate
	 * the chart indexes. _ptr barsetPtr (std::vector<QBarSet *> barsetPtr) holds the
	 * sets of the chart itself.
	 * nItr will set the frequency of the variable
	 */

	_vct<double>::const_iterator dItr = m_variables.begin();
	_vct<int>::const_iterator nItr = m_absolute_freq.begin();

	_ptr barsetPtr;
	barsetPtr.resize(m_variables.size()); // The amount of sets must be equal to the amount of variables.
	_ptr::iterator pItr = barsetPtr.begin();

	for(; dItr != m_variables.end(); dItr++)
	{
		*pItr = new QBarSet(QString::number(*dItr), this);
		**(pItr++) << *(nItr++); /* Adds the nItr-dereference (the variable frequency) to the
								  * dereference of the pointer accesed by
								  * dereferencing pItr... This is kinda messy... which is what
								  * the set points to.
								  */
	}

	generateBar(barsetPtr);

}

void SimpleFreqG::generateBar(_ptr & barsetPtr)
{
	/* Once all the sets are created, they must be added to a serie.
	 * Since each set is composed of only one variable in the simple frequency
	 * table, each set will be a bar by itself.
	 */

	QBarSeries *series = new QBarSeries(this);
	_ptr::const_iterator pItr = barsetPtr.begin();

	for(; pItr != barsetPtr.end(); pItr++)
	{
		series->append(*pItr);
	}

	QChart *chart = new QChart();
	chart->addSeries(series);
	chart->setTitle("CHART_TITLE_GOES_HERE"); // NOTE: Placeholder.
	chart->setAnimationOptions(QChart::SeriesAnimations);
	chart->createDefaultAxes(); /* NOTE: Without QBarCategoryAxis, this puts a number "1" below
								 * the bars (Since there's only one category).
								 */
	chart->legend()->setAlignment(Qt::AlignBottom);
	chart->setTheme(QChart::ChartThemeQt);
	chart->setAttribute(Qt::WA_DeleteOnClose);

	/*
	QChartView *chartview = new QChartView(chart, this);
	chartview->setRenderHint(QPainter::Antialiasing);
	chartview->show();

	* This is commented because a custom widget was created to show the
	* bar chart. Without the Qt Designer Custom Widget, this step would
	* be necessary
	*/

	ui->CustomChartWidget->setChart(chart); // Sets the chart to the customwidget.
}
