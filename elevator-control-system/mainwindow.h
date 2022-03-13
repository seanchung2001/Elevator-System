#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QTimer>
#include <QList>

#include "passengers.h"
#include "floor.h"
#include "elevator.h"
#include "ecs.h"
#include "bell.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void logToSystem();

private slots:
    void normalMode();
    void overloadMode();
    void doorObstacleMode();
    void helpMode();
    void fireMode();
    void poweroutMode();

private:
    Ui::MainWindow *ui;

    //Processing time
    //Timer is set at 1 second for convenience
    QTimer *timer;

    //Printing stuff to ecs screen
    //messages will be appended to 'info' and at the end of each simulation, will loop through 'info' to print all the messages to the GUI.
    QList<QString> info;

    //Sometimes our functions will return a QList<QString> of what should be printed in the ecs log
    //In that case, moreInfo will be used to store the strings and will append everything to 'info'.
    //moreInfo acts as a tmp variable for info.
    QList<QString> moreInfo;

    //Create Elevator Passengers
    //In our simulation, we have 5 passengers
    Passengers *passenger1;
    Passengers *passenger2;
    Passengers *passenger3;
    Passengers *passenger4;
    Passengers *passenger5;

    //Create Floors of Building
    //Our simulation will create 6 floors numbered (0-5) with floor 0 being the main floor
    Floor *floor0;
    Floor *floor1;
    Floor *floor2;
    Floor *floor3;
    Floor *floor4;
    Floor *floor5;

    //Create Elevators
    Elevator *elevator1;
    Elevator *elevator2;
    Elevator *elevator3;
    Elevator *inUse1;
    Elevator *inUse2;
    Elevator *inUse3;

    //Create Bell
    Bell *bell;

    //Create Elevator Control System
    ECS *elevatorControlSystem;

};
#endif // MAINWINDOW_H
