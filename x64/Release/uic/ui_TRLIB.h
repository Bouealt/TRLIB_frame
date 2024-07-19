/********************************************************************************
** Form generated from reading UI file 'TRLIB.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRLIB_H
#define UI_TRLIB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TRLIBClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TRLIBClass)
    {
        if (TRLIBClass->objectName().isEmpty())
            TRLIBClass->setObjectName(QStringLiteral("TRLIBClass"));
        TRLIBClass->resize(600, 400);
        menuBar = new QMenuBar(TRLIBClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        TRLIBClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TRLIBClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TRLIBClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(TRLIBClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        TRLIBClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TRLIBClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TRLIBClass->setStatusBar(statusBar);

        retranslateUi(TRLIBClass);

        QMetaObject::connectSlotsByName(TRLIBClass);
    } // setupUi

    void retranslateUi(QMainWindow *TRLIBClass)
    {
        TRLIBClass->setWindowTitle(QApplication::translate("TRLIBClass", "TRLIB", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TRLIBClass: public Ui_TRLIBClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRLIB_H
