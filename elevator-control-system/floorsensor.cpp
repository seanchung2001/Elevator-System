#include "floorsensor.h"

FloorSensor::FloorSensor()
{
}

QString FloorSensor::detectFloor(int f)
{
    QString tmp = QString (" on floor %1").arg(f);
    return tmp;
}
