#include "charazard.h"

charazard::charazard(QObject *parent) : QObject(parent)
{

}



void charazard::start()
{
    milisecondToPassUntilGravityApplied = 5;

    wingsFlapping = false;
    timestampSinceWingsStartedFlapping = QDateTime::currentMSecsSinceEpoch();
    timestampSinceWingsStoppedFlapping = QDateTime::currentMSecsSinceEpoch();
    milisecondsToPassUntilLiftIsApplied = 1;
    liftAppliedDuringFlap = 0;

    y = 50;
    go = new gameobject();
    go->start(QImage(QString(":/examplegame/quickgame/image/charazard.png")));
    go->updateImageSpecifications(50, y, 200, 200);
}


gameobject* charazard::game_object(){ return go; }



void charazard::step_logic()
{
    //Gravity
    this->gravity();

    //Wing Flap
    this->wingFlap();
}



void charazard::gravity()
{
    ///Determine how many units of gravity need to be applied.

    //Determine time since gravity was last applied.
    qint64 timeSinceGravityApplied = QDateTime::currentMSecsSinceEpoch() - timestampSinceGravityApplied;

    //Determine if enough time has passed to apply gravity.
    if(timeSinceGravityApplied >= milisecondToPassUntilGravityApplied)
    {
        y += 1;
        go->updateImageSpecifications(50, y, 200, 200);

        //Update timestamp gravity applied.
        timestampSinceGravityApplied = QDateTime::currentMSecsSinceEpoch();
    }
}



void charazard::wingFlap()
{
    if(wingsFlapping == false)
    {
        //Determine if it is time to start a "flap".
        qint64 milisecondsSinceLastFlap = QDateTime::currentMSecsSinceEpoch() - timestampSinceWingsStoppedFlapping;
        if(milisecondsSinceLastFlap >= 100)
        {
            wingsFlapping = true;
            timestampSinceWingsStartedFlapping = QDateTime::currentSecsSinceEpoch();
        }
    }else if(wingsFlapping == true)
    {
        y -= 1;

        //Determine if it time to stop flapping.
        qint64 milisecondsSinceWingsStartedFlapping = QDateTime::currentMSecsSinceEpoch() - timestampSinceWingsStartedFlapping;
        if(milisecondsSinceWingsStartedFlapping >= 100)
        {
            wingsFlapping = false;
            timestampSinceWingsStoppedFlapping = QDateTime::currentMSecsSinceEpoch();
        }
    }
}
