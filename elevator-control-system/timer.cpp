#include "timer.h"

#include <QtCore>
#include <QDebug>
Timer::Timer()
{
    myTimer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(TimerSlot()));

    timer->start(1000);
}

void Timer::TimerSlot(){
    qDebug() << "Timer executed";
}
