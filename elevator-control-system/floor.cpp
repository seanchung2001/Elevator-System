#include "floor.h"

Floor::Floor(int f)
{
    floorNum = f;
    direction = "idle";
    fSensor = new FloorSensor();
}

void Floor::setDirection(QString informDirection)
{
    direction = informDirection;
}

void Floor::serviced()
{
    direction = "idle";
}

int Floor::getFloorNum() { return floorNum; }

FloorSensor* Floor::getFloorSensor()
{
    return fSensor;
}
