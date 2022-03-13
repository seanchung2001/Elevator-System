#include "bell.h"

Bell::Bell()
{

}
//Notifies the ECS that the bell has rung in an elevator
QString Bell::ring()
{
    QString tmp = "Bell Ring!";
    return tmp;
}
