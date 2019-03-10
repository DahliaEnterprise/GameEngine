#include "gameloop.h"

gameloop::gameloop(QObject *parent) : QObject(parent)
{

}

void gameloop::start()
{
    gui_mainmenu = new mainmenu();
    gui_mainmenu->start();
}

QList<gameobject*> gameloop::frame()
{
    return gui_mainmenu->frame();
}
