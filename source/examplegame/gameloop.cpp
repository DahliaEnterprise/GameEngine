#include "gameloop.h"

gameloop::gameloop(QObject *parent) : QObject(parent)
{

}

void gameloop::start(keyboardMouseInput* setKeyboardMouseInput)
{
    //Keyboard and Mouse Input
    keyboardmouseInput = setKeyboardMouseInput;

    //Graphical Menus
    gui_mainmenu = new mainmenu();
    QObject::connect(gui_mainmenu, SIGNAL(playerRequestingCloseGame()), this, SIGNAL(playerRequestingCloseGame()));
    gui_mainmenu->start(keyboardmouseInput);
}

QList<gameobject*> gameloop::frame(){ return gui_mainmenu->frame(); }
