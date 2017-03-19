/********************************************************************************
** Form generated from reading UI file 'simplefreqg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMPLEFREQG_H
#define UI_SIMPLEFREQG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SimpleFreqG
{
public:
    QPushButton *button_return;

    void setupUi(QDialog *SimpleFreqG)
    {
        if (SimpleFreqG->objectName().isEmpty())
            SimpleFreqG->setObjectName(QStringLiteral("SimpleFreqG"));
        SimpleFreqG->resize(400, 300);
        button_return = new QPushButton(SimpleFreqG);
        button_return->setObjectName(QStringLiteral("button_return"));
        button_return->setGeometry(QRect(310, 260, 75, 23));

        retranslateUi(SimpleFreqG);

        QMetaObject::connectSlotsByName(SimpleFreqG);
    } // setupUi

    void retranslateUi(QDialog *SimpleFreqG)
    {
        SimpleFreqG->setWindowTitle(QApplication::translate("SimpleFreqG", "Dialog", Q_NULLPTR));
        button_return->setText(QApplication::translate("SimpleFreqG", "Return", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SimpleFreqG: public Ui_SimpleFreqG {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMPLEFREQG_H
