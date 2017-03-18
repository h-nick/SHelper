/********************************************************************************
** Form generated from reading UI file 'datainsert.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAINSERT_H
#define UI_DATAINSERT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_DataInsert
{
public:
    QGridLayout *gridLayout;
    QPushButton *button_OK;
    QPushButton *button_cancel;
    QSpacerItem *horizontalSpacer;
    QPlainTextEdit *values;
    QLabel *label;

    void setupUi(QDialog *DataInsert)
    {
        if (DataInsert->objectName().isEmpty())
            DataInsert->setObjectName(QStringLiteral("DataInsert"));
        DataInsert->resize(400, 300);
        gridLayout = new QGridLayout(DataInsert);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        button_OK = new QPushButton(DataInsert);
        button_OK->setObjectName(QStringLiteral("button_OK"));

        gridLayout->addWidget(button_OK, 2, 1, 1, 1);

        button_cancel = new QPushButton(DataInsert);
        button_cancel->setObjectName(QStringLiteral("button_cancel"));

        gridLayout->addWidget(button_cancel, 2, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        values = new QPlainTextEdit(DataInsert);
        values->setObjectName(QStringLiteral("values"));

        gridLayout->addWidget(values, 1, 0, 1, 3);

        label = new QLabel(DataInsert);
        label->setObjectName(QStringLiteral("label"));
        label->setTextFormat(Qt::RichText);

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(DataInsert);

        QMetaObject::connectSlotsByName(DataInsert);
    } // setupUi

    void retranslateUi(QDialog *DataInsert)
    {
        DataInsert->setWindowTitle(QApplication::translate("DataInsert", "Dialog", Q_NULLPTR));
        button_OK->setText(QApplication::translate("DataInsert", "OK", Q_NULLPTR));
        button_cancel->setText(QApplication::translate("DataInsert", "Cancel", Q_NULLPTR));
        label->setText(QApplication::translate("DataInsert", "<html><head/><body><p>Insert all the numeric values for the table.<br/>Each value must be in a line by itself.<br/>Use a dot (.) as the decimal denominator.</p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DataInsert: public Ui_DataInsert {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAINSERT_H
