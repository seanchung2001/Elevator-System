#include "screen.h"

//Each elevator has a display screen
Screen::Screen()
{
}

QString Screen::displayFloor()
{
    QString tmp = "Displaying floors on elevator screen for passengers...";
    return tmp;
}

QString Screen::displayWarning()
{
    QString tmp = "Displaying warning message on elevator display screen";
    return tmp;
}
