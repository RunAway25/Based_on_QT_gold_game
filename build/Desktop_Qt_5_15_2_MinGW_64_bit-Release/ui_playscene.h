/********************************************************************************
** Form generated from reading UI file 'playscene.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYSCENE_H
#define UI_PLAYSCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayScene
{
public:
    QAction *actionquit;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu;

    void setupUi(QMainWindow *PlayScene)
    {
        if (PlayScene->objectName().isEmpty())
            PlayScene->setObjectName(QString::fromUtf8("PlayScene"));
        PlayScene->resize(800, 600);
        actionquit = new QAction(PlayScene);
        actionquit->setObjectName(QString::fromUtf8("actionquit"));
        centralwidget = new QWidget(PlayScene);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        PlayScene->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PlayScene);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 20));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        PlayScene->setMenuBar(menubar);

        menubar->addAction(menu->menuAction());
        menu->addAction(actionquit);

        retranslateUi(PlayScene);

        QMetaObject::connectSlotsByName(PlayScene);
    } // setupUi

    void retranslateUi(QMainWindow *PlayScene)
    {
        PlayScene->setWindowTitle(QCoreApplication::translate("PlayScene", "MainWindow", nullptr));
        actionquit->setText(QCoreApplication::translate("PlayScene", "\351\200\200\345\207\272", nullptr));
        menu->setTitle(QCoreApplication::translate("PlayScene", "\345\274\200\345\247\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlayScene: public Ui_PlayScene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYSCENE_H
