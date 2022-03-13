#ifndef FLOORSENSOR_H
#define FLOORSENSOR_H

#include <QList>
#include <QString>

class FloorSensor
{
public:
    FloorSensor();
    QString detectFloor(int);
};

#endif // FLOORSENSOR_H
