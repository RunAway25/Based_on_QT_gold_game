/********************************************************************************
** Form generated from reading UI file 'selectlevel.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTLEVEL_H
#define UI_SELECTLEVEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectLevel
{
public:
    QAction *actionquit;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SelectLevel)
    {
        if (SelectLevel->objectName().isEmpty())
            SelectLevel->setObjectName(QString::fromUtf8("SelectLevel"));
        SelectLevel->resize(800, 600);
        actionquit = new QAction(SelectLevel);
        actionquit->setObjectName(QString::fromUtf8("actionquit"));
        centralwidget = new QWidget(SelectLevel);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        SelectLevel->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SelectLevel);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 20));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        SelectLevel->setMenuBar(menubar);
        statusbar = new QStatusBar(SelectLevel);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SelectLevel->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(actionquit);

        retranslateUi(SelectLevel);

        QMetaObject::connectSlotsByName(SelectLevel);
    } // setupUi

    void retranslateUi(QMainWindow *SelectLevel)
    {
        SelectLevel->setWindowTitle(QCoreApplication::translate("SelectLevel", "MainWindow", nullptr));
        actionquit->setText(QCoreApplication::translate("SelectLevel", "\351\200\200\345\207\272", nullptr));
        menu->setTitle(QCoreApplication::translate("SelectLevel", "\345\274\200\345\247\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectLevel: public Ui_SelectLevel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLEVEL_H
