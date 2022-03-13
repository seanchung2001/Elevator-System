#ifndef TIMER_H
#define TIMER_H

#include <QtCore>

class Timer : public QObject
{
    Q_OBJECT

public:
    Timer();
    QTimer *myTimer;

public slots:
    void TimerSlot();
};

#endif // TIMER_H
