#ifndef PASSENGERS_H
#define PASSENGERS_H

#include <QString>

class Passengers
{
public:
    Passengers(QString, float, int);

    QString getName();
    float getWeight();
    QString getDirection();
    QString chooseDirection(QString);
    int chooseFloor(int);
    int getCurrFloor();
    void setCurrFloor(int);

private:
    QString name;
    float weight;
    int currFloor;
    QString direction;

};

#endif // PASSENGERS_H
