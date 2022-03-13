#include "doorsensor.h"

DoorSensor::DoorSensor()
{

}
//Checks if there is an obstacle (represented as a boolean) that blocks the door sensor while the door is closing
bool DoorSensor::isInterrupted(bool obstacle)
{
    if (obstacle == true){
        return true;
    }
    else{
        return false;
    }
}
