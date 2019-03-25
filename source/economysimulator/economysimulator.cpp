#include "economysimulator.h"

economysimulator::economysimulator(QObject *parent) : QObject(parent)
{

}

void economysimulator::start()
{
    game = new economysimulator_gameloop();
}

QList<gameobject*> economysimulator::frame(){ /*game->frame();*/ }

void economysimulator::stop()
{

}
