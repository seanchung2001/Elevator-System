#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QString>
#include <QList>
#include <QDebug>

#include "passengers.h"
#include "door.h"
#include "weightsensor.h"
#include "screen.h"
#include "audio.h"

class Elevator
{
public:
    Elevator(int, QString);
    QString getName();
    QString getState();
    int getResidingFloor();
    int getRequest();
    Screen* getScreen();
    Audio* getAudio();
    void setState(QString);
    void setDirection(QString);
    void setRequests(int);
    void setResidingFloor(int);
    QString openDoor();
    QString closeDoor(bool);
    void loadPassengers(Passengers*);
    void unloadPassengers(Passengers*);
    QString overrideDoorClose();
    QString overrideOpenDoor();
    QString getInfo();
    void fireSignal(bool);

private:
    int residingFloor;
    QString name;
    QString state;
    QString direction;
    int request;
    QList<Passengers*> passengers;
    Door* elevatorDoor;
    weightsensor* wSensor;
    Screen* displayScreen;
    Audio* audio;
};

#endif // ELEVATOR_H
