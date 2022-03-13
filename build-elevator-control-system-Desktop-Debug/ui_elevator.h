/********************************************************************************
** Form generated from reading UI file 'elevator.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ELEVATOR_H
#define UI_ELEVATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_Elevator
{
public:

    void setupUi(QDialog *Elevator)
    {
        if (Elevator->objectName().isEmpty())
            Elevator->setObjectName(QString::fromUtf8("Elevator"));
        Elevator->resize(400, 300);

        retranslateUi(Elevator);

        QMetaObject::connectSlotsByName(Elevator);
    } // setupUi

    void retranslateUi(QDialog *Elevator)
    {
        Elevator->setWindowTitle(QApplication::translate("Elevator", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Elevator: public Ui_Elevator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ELEVATOR_H
