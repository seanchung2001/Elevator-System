#ifndef DOOR_H
#define DOOR_H

#include <QString>

#include <doorsensor.h>

class Door
{
public:
    Door();
    void open();
    bool close(bool);

private:
    QString doorState;
    DoorSensor* dSensor;
};

#endif // DOOR_H
