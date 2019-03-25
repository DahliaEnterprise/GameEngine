#include "economysimulator_gameloop.h"

economysimulator_gameloop::economysimulator_gameloop(QObject *parent) : QObject(parent)
{

}

void economysimulator_gameloop::start()
{
    personone = new person();
    personone->start();
    personone->updateImageSpecification(100,100,50,50,0.5);
    persononelogic = new person_logic();
    persononelogic->start();

    logicCycler = new QTimer();
    logicCycler->setInterval(5);
    QObject::connect(logicCycler, SIGNAL(timeout()), this, SLOT(iterate_logic()));
    logicCycler->start();
}


QList<gameobject*> economysimulator_gameloop::frame()
{
    goList.clear();
    //goList.append();

    return goList;
}


void economysimulator_gameloop::iterate_logic()
{
    //Apply person logic
}
