#ifndef FLOOR_H
#define FLOOR_H

#include <QString>

#include "floorsensor.h"

class Floor
{
public:
    Floor(int);
    void setDirection(QString);
    void serviced();
    int getFloorNum();
    FloorSensor* getFloorSensor();
private:
    QString direction;
    int floorNum;
    FloorSensor* fSensor;
};

#endif // FLOOR_H
