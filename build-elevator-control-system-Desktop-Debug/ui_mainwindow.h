/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QListWidget *ecsLog;
    QPushButton *normal;
    QPushButton *overload;
    QPushButton *doorObstacle;
    QPushButton *help;
    QPushButton *fire;
    QPushButton *power_out;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        ecsLog = new QListWidget(centralwidget);
        ecsLog->setObjectName(QString::fromUtf8("ecsLog"));
        ecsLog->setGeometry(QRect(30, 10, 741, 241));
        normal = new QPushButton(centralwidget);
        normal->setObjectName(QString::fromUtf8("normal"));
        normal->setGeometry(QRect(140, 284, 81, 31));
        overload = new QPushButton(centralwidget);
        overload->setObjectName(QString::fromUtf8("overload"));
        overload->setGeometry(QRect(140, 350, 81, 31));
        doorObstacle = new QPushButton(centralwidget);
        doorObstacle->setObjectName(QString::fromUtf8("doorObstacle"));
        doorObstacle->setGeometry(QRect(340, 284, 91, 31));
        help = new QPushButton(centralwidget);
        help->setObjectName(QString::fromUtf8("help"));
        help->setGeometry(QRect(340, 350, 91, 31));
        fire = new QPushButton(centralwidget);
        fire->setObjectName(QString::fromUtf8("fire"));
        fire->setGeometry(QRect(530, 284, 81, 31));
        power_out = new QPushButton(centralwidget);
        power_out->setObjectName(QString::fromUtf8("power_out"));
        power_out->setGeometry(QRect(530, 350, 81, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        normal->setText(QApplication::translate("MainWindow", "Normal", nullptr));
        overload->setText(QApplication::translate("MainWindow", "overload", nullptr));
        doorObstacle->setText(QApplication::translate("MainWindow", "Door Obstacle", nullptr));
        help->setText(QApplication::translate("MainWindow", "Help", nullptr));
        fire->setText(QApplication::translate("MainWindow", "Fire", nullptr));
        power_out->setText(QApplication::translate("MainWindow", "Power Out", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
