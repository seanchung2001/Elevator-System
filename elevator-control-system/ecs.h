#ifndef ECS_H
#define ECS_H

#include <QString>
#include <QList>
#include <QDebug>

#include "elevator.h"
#include "floor.h"
#include "passengers.h"

class ECS
{
public:
    ECS();
    void setElevator(Elevator*);
    void setFloor(Floor*);
    void replaceElevator(Elevator*);
    Elevator* getElevator(int, QString);
    QList<QString> moveElevator(Elevator*, int);
    QList<QString> helpRequest(Passengers*, int);
    QString connectCall();
    void stop(Elevator*, int);
    void updateFloor(Elevator*, int);
    void emergencyStop(Elevator*, int, QString);
    void turnPowerOff();
    void turnPowerOn();
private:
    QList<Elevator*> elevators;
    QList<Floor*> floors;
    QString state;
};

#endif // ECS_H
