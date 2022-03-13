#include "passengers.h"

Passengers::Passengers(QString n, float w, int c) {
    name = n;             //Name will be hard-coded to be unique for each passenger to not have passengerID
    weight = w;
    currFloor = c;
    direction = "none";
}

QString Passengers::getName() { return name; }
float Passengers::getWeight() { return weight; }

QString Passengers::getDirection()
{
    return direction;
}
QString Passengers::chooseDirection(QString d){
    direction = d;
    return direction;
}

int Passengers::chooseFloor(int fNum)
{
    return fNum;
}
int Passengers::getCurrFloor() { return currFloor; }

void Passengers::setCurrFloor(int newFloor)
{
    currFloor = newFloor;
}
