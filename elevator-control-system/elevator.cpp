#include "elevator.h"

Elevator::Elevator(int c, QString n)
{
    residingFloor = c;
    name = n;
    state = "idle";
    direction = "idle";
    request = -1;
    elevatorDoor = new Door();
    wSensor = new weightsensor(500.0);
    displayScreen = new Screen();
    audio = new Audio();
}

QString Elevator::getName(){
    return name;
}

QString Elevator::getState()
{
    return state;
}

int Elevator::getResidingFloor()
{
    return residingFloor;
}

int Elevator::getRequest()
{
    return request;
}

Screen *Elevator::getScreen()
{
    return displayScreen;
}

Audio *Elevator::getAudio()
{
    return audio;
}

void Elevator::setState(QString s)
{
    state = s;
}

void Elevator::setDirection(QString d)
{
    direction = d;
}

void Elevator::setRequests(int r)
{
    request = r;
}

void Elevator::setResidingFloor(int rf)
{
    residingFloor = rf;
}

QString Elevator::openDoor()
{
    QString tmp = QString ("Opening %1 door for 10 seconds...").arg(name);
    elevatorDoor->open();
    return tmp;
}

QString Elevator::closeDoor(bool obstacle)
{
    QString tmp;
    //No obstacle blocking door sensor
    if (elevatorDoor->close(obstacle) == false){
        tmp = QString ("Closing %1 doors...").arg(name);
    }
    //Obstacle is blocking door sensor while closing
    else{
        tmp = QString ("%1 door sensor was interrupted while closing...Opening the doors").arg(name);
    }
    return tmp;
}

void Elevator::loadPassengers(Passengers* p)
{
    //Add to the weight sensor, the weight of the passenger entering the car
    int currWeight = wSensor->getCurrWeight();
    currWeight += p->getWeight();
    wSensor->setCurrWeight(currWeight);
    passengers.append(p);
    //Check for overload
    if (wSensor->isOverload()){
        state = "overload";
    }
    else{
        return;
    }
}

void Elevator::unloadPassengers(Passengers* p)
{
    //Adjust weight sensor
    int currWeight = wSensor->getCurrWeight();
    for (int i = 0; i < passengers.size(); i++){
        if (p->getName() == passengers.at(i)->getName()){
            p->setCurrFloor(residingFloor);
            passengers.removeAt(i);
            currWeight -= p->getWeight();
            wSensor->setCurrWeight(currWeight);
            break;
        }
    }
    //Set the elevator to idle if all passengers are off
    if (passengers.size() == 0){
        state = "idle";
    }
}
//This can be used by passengers to override the default timing of the elevator door closing
QString Elevator::overrideDoorClose()
{
    QString tmp = "Passenger has requested to close doors prematurely...";
    return tmp;
}
//This can be used by passengers to open elevator doors manually
QString Elevator::overrideOpenDoor()
{
    QString tmp = "Passenger has requested to keep the door open...";
    return tmp;
}
//Displays all necessary information to ECS before transporting passengers
QString Elevator::getInfo()
{
    QString tmp;
    tmp = QString ("%1 Maximum Weight: %2, Current Weight: %3, Number of Passengers: %4").arg(name).arg(wSensor->getMaxWeight()).arg(wSensor->getCurrWeight()).arg(passengers.size());
    return tmp;
}

void Elevator::fireSignal(bool fire)
{
    if (fire == true){
        state = "fire";
    }
    return;
}
