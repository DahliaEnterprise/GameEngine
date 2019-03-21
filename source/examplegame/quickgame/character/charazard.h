#ifndef CHARAZARD_H
#define CHARAZARD_H

#include <QObject>
#include "gameengine/gameobject.h"
#include <QDateTime>
#include <QDebug>
class charazard : public QObject
{
    Q_OBJECT
public:
    explicit charazard(QObject *parent = nullptr);
    void start();
    gameobject* game_object();
    void step_logic();

private:
    gameobject* go;

    //Coordinates
    int y;

    //Gravity
    qint64 timestampSinceGravityApplied;
    qint64 milisecondToPassUntilGravityApplied;

    //Wing Flap
    bool wingsFlapping;
    qint64 timestampSinceWingsStartedFlapping;
    qint64 milisecondsToPassUntilLiftIsApplied;
    int liftAppliedDuringFlap;
    qint64 timestampSinceWingsStoppedFlapping;


    ///Private Functions
    void gravity();
    void wingFlap();

signals:

public slots:
};

#endif // CHARAZARD_H
