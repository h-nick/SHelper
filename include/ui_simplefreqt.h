/********************************************************************************
** Form generated from reading UI file 'simplefreqt.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMPLEFREQT_H
#define UI_SIMPLEFREQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SimpleFreqT
{
public:
    QGridLayout *gridLayout;
    QTableWidget *table;

    void setupUi(QDialog *SimpleFreqT)
    {
        if (SimpleFreqT->objectName().isEmpty())
            SimpleFreqT->setObjectName(QStringLiteral("SimpleFreqT"));
        SimpleFreqT->resize(750, 373);
        gridLayout = new QGridLayout(SimpleFreqT);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        table = new QTableWidget(SimpleFreqT);
        if (table->columnCount() < 7)
            table->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        table->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        table->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        table->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        table->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        table->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        table->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        table->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        table->setObjectName(QStringLiteral("table"));

        gridLayout->addWidget(table, 0, 0, 1, 1);


        retranslateUi(SimpleFreqT);

        QMetaObject::connectSlotsByName(SimpleFreqT);
    } // setupUi

    void retranslateUi(QDialog *SimpleFreqT)
    {
        SimpleFreqT->setWindowTitle(QApplication::translate("SimpleFreqT", "Dialog", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = table->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("SimpleFreqT", "Variable (X)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = table->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("SimpleFreqT", "Absolute Freq (fi)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = table->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("SimpleFreqT", "Relative Freq (hi)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = table->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("SimpleFreqT", "AAbs Freq (Fi)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = table->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("SimpleFreqT", "ARel Freq (Hi)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = table->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("SimpleFreqT", "Relative %", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = table->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("SimpleFreqT", "Acmlt %", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SimpleFreqT: public Ui_SimpleFreqT {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMPLEFREQT_H
