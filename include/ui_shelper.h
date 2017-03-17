/********************************************************************************
** Form generated from reading UI file 'shelper.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHELPER_H
#define UI_SHELPER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Shelper
{
public:
    QWidget *centralWidget;
    QPushButton *button_simplefreq;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Shelper)
    {
        if (Shelper->objectName().isEmpty())
            Shelper->setObjectName(QStringLiteral("Shelper"));
        Shelper->resize(523, 362);
        centralWidget = new QWidget(Shelper);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        button_simplefreq = new QPushButton(centralWidget);
        button_simplefreq->setObjectName(QStringLiteral("button_simplefreq"));
        button_simplefreq->setGeometry(QRect(10, 20, 71, 51));
        Shelper->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Shelper);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 523, 21));
        Shelper->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Shelper);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Shelper->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Shelper);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Shelper->setStatusBar(statusBar);

        retranslateUi(Shelper);

        QMetaObject::connectSlotsByName(Shelper);
    } // setupUi

    void retranslateUi(QMainWindow *Shelper)
    {
        Shelper->setWindowTitle(QApplication::translate("Shelper", "Shelper", Q_NULLPTR));
        button_simplefreq->setText(QApplication::translate("Shelper", "Simple Freq.\n"
"Table", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Shelper: public Ui_Shelper {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHELPER_H
