#include "door.h"

Door::Door()
{
    doorState = "closed";
    dSensor = new DoorSensor();
}

void Door::open()
{
    doorState = "open";
}
//For closing elevator door, we check if the doorsensor is interrupted while closing. If so, we open the elevator door back up (in Elevator class)
bool Door::close(bool obstacle)
{
    if(dSensor->isInterrupted(obstacle)){
        return false;
    }
    else{
        return true;
    }
}
