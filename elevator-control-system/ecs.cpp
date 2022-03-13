#include "ecs.h"

ECS::ECS()
{
    state = "on";
}

void ECS::setElevator(Elevator* e){
    elevators.append(e);
}

void ECS::setFloor(Floor* f)
{
    floors.append(f);
}
//Since we are using 'InUse' elevators to carry out requests, we must set the appropriate elevator to the state of one of the 'InUse' elevators.
void ECS::replaceElevator(Elevator* e)
{
    if (e->getName() == "Elevator 1"){
        elevators.pop_front();
        elevators.push_front(e);
        return;
    }
    else if(e->getName() == "Elevator 2"){
        Elevator* tmp = elevators.at(0);
        elevators.pop_front();
        elevators.pop_front();
        elevators.push_front(e);
        elevators.push_front(tmp);
        return;
    }
    else if (e->getName() == "Elevator 3"){
        elevators.pop_back();
        elevators.push_back(e);
        return;
    }
}

Elevator *ECS::getElevator(int floorNum, QString direction)
{
    QList<Elevator*> idleElevators;
    //This elevator will be returned by ECS
    Elevator* returnElevator;
    //closest floor will be set to the number of floors in the building for now (for Elevator-Centered Strategy, handling variability)
    int closestFloor = 6;
    for (int i = 0; i < elevators.size(); i++){
        //Find all idle elevators
        if (elevators.at(i)->getState() == "idle"){
            idleElevators.append(elevators.at(i));
        }
    }
    for (int j = 0; j < idleElevators.size(); j++) {
        //If an idle elevator is on the floor of the requesting passenger, look no further and return that elevator.
        if (idleElevators.at(j)->getResidingFloor() == floorNum) {
            returnElevator = idleElevators.at(j);
            break;
        }
        //These else-if statements check the absolute value for determining the elevator that is nearest to the passenger
        else if (idleElevators.at(j)->getResidingFloor() > floorNum) {
            if (idleElevators.at(j)->getResidingFloor() - floorNum < closestFloor) {
                returnElevator = idleElevators.at(j);
            }
        }
        else if (idleElevators.at(j)->getResidingFloor() < floorNum) {
            if (floorNum - idleElevators.at(j)->getResidingFloor() < closestFloor) {
                returnElevator = idleElevators.at(j);
            }
        }
    }
    //Check which elevator we are returning so that we can set the state, direction and request in the elevators list.
    if (elevators.at(0)->getName() == returnElevator->getName()){
        elevators.at(0)->setDirection(direction);
        elevators.at(0)->setState("busy");
        elevators.at(0)->setRequests(floorNum);
    }
    else if (elevators.at(1)->getName() == returnElevator->getName()){
        elevators.at(1)->setDirection(direction);
        elevators.at(1)->setState("busy");
        elevators.at(1)->setRequests(floorNum);
    }
    else if (elevators.at(2)->getName() == returnElevator->getName()){
        elevators.at(2)->setDirection(direction);
        elevators.at(2)->setState("busy");
        elevators.at(2)->setRequests(floorNum);
    }
    return returnElevator;
}

QList<QString> ECS::moveElevator(Elevator* e, int newFloor)
{
    QList<QString> tmp;
    QString tmpString;
    //Check if the eelvator is in an overload state
    if (e->getState() == "overload"){
        tmpString = QString ("---OVERLOAD--- %1 exceeds the maximum cargo capacity, please lighten the load...").arg(e->getName());
        tmp.append(tmpString);
        emergencyStop(e, -1, "overload");
        return tmp;
    }
    tmpString = QString ("%1 heading from floor %2 to floor %3...").arg(e->getName()).arg(e->getResidingFloor()).arg(newFloor);
    tmp.append(tmpString);
    e->setRequests(newFloor);
    //Elevator is moving down
    if (e->getResidingFloor() > newFloor){
        //Move the elevator towards requested floor
        for (int i = e->getResidingFloor()-1; i >= newFloor; i--){
            //Check for fire signals while moving the elevator
            if (e->getState() == "fire"){
                tmpString = "---FIRE SIGNAL--- Please evacuate from the elevator once a safe floor is reached...";
                tmp.append(tmpString);
                tmp.append("Commanding all elevators to move to a safe floor...");
                tmp.append(e->getAudio()->audioWarning());
                tmp.append(e->getScreen()->displayWarning());
                emergencyStop(e, i, "fire");
                return tmp;
            }
            //Check for power-out signals while moving the elevator
            if (state == "off"){
                tmp.append("---POWER OUT---: Turning on backup power generator... Please evacuate once a safe floor is reached...");
                tmp.append(e->getAudio()->audioWarning());
                tmp.append(e->getScreen()->displayWarning());
                emergencyStop(e, i, "Power Out");
                return tmp;
            }
            //Reached destination floor
            if (i == newFloor-1){
                stop(e, i);
                break;
            }
            tmpString = e->getName();
            tmpString.append(floors.at(i)->getFloorSensor()->detectFloor(i));
            tmp.append(tmpString);
            updateFloor(e, i);
        }
    }
    //Elevator moving up
    else if (e->getResidingFloor() < newFloor){
        //Move the elevator to requested floor
        for (int i = e->getResidingFloor()+1; i <= newFloor; i++){
            //Check for fire signals while moving elevator
            if (e->getState() == "fire"){
                tmpString = "---FIRE SIGNAL--- Please evacuate from the elevator once a safe floor is reached...";
                tmp.append(tmpString);
                tmp.append(e->getAudio()->audioWarning());
                tmp.append(e->getScreen()->displayWarning());
                emergencyStop(e, i, "fire");
                return tmp;
            }
            //Check for power-off signals while moving elevator
            if (state == "off") {
                tmp.append("---POWER OUT--- Turning on backup power generator... Please evacuate once a safe floor is reached...");
                tmp.append(e->getAudio()->audioWarning());
                tmp.append(e->getScreen()->displayWarning());
                emergencyStop(e, i, "Power Out");
                return tmp;
            }
            //Reached destination floor
            if (i == newFloor+1){
                stop(e, i);
                break;
            }
            tmpString = e->getName();
            tmpString.append(floors.at(i)->getFloorSensor()->detectFloor(i));
            tmp.append(tmpString);
            updateFloor(e, i);
        }
    }
    //Return a list of QStrings to be printed to the GUI
    return tmp;
}

//numSec simulates the number of seconds that passed before building services connects with passenger
QList<QString> ECS::helpRequest(Passengers* p, int numSec){
    QList<QString> tmp;
    QString tmpString;
    tmpString = QString ("---HELP REQUEST--- from %1... Attempting to connect with building safety services").arg(p->getName());
    tmp.append(tmpString);
    if (numSec > 5){
        tmpString = "No response from building safety services within 5 seconds...Placing 911 call";
        tmp.append(tmpString);
        tmp.append(connectCall());
    }
    else{
        tmpString = "Connection with building safety services made!";
        tmp.append(tmpString);
        tmp.append(connectCall());
    }
    return tmp;
}

QString ECS::connectCall()
{
    return "Making connection with passenger through elevator audio system...";
}

void ECS::stop(Elevator* e, int i)
{
    //Set the appropriate variables
    e->setState("busy");
    e->setResidingFloor(i);
    e->setDirection("up");
}

void ECS::updateFloor(Elevator* e, int i)
{
    //Set the appropriate variables
    e->setState("busy");
    e->setResidingFloor(i);
    e->setDirection("up");
}

void ECS::emergencyStop(Elevator* e, int i, QString s)
{
    if (s == "overload") {
        e->setState("overload");
        e->setRequests(-1);
    }
    //Set the appropriate variables
    e->setResidingFloor(i);
    e->setDirection("idle");
    e->setRequests(-1);
    e->setState("fire");
    state = s;
    return;
}

void ECS::turnPowerOff()
{
    state = "off";
}

void ECS::turnPowerOn(){
    state = "on";
}
