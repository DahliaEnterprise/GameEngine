#include "gameloop.h"

gameloop::gameloop(QObject *parent) : QObject(parent)
{

}

gameloop::~gameloop()
{
    quickGame->deleteLater();
}

void gameloop::start(keyboardMouseInput* setKeyboardMouseInput)
{
    //Keyboard and Mouse Input
    keyboardmouseInput = setKeyboardMouseInput;

    //Graphical Menus
    quickGame = new quickgame();
    QObject::connect(quickGame, SIGNAL(playerRequestingCloseGame()), this, SIGNAL(playerRequestingCloseGame()));
    quickGame->start(keyboardmouseInput);
}

QList<gameobject*> gameloop::frame(){ return quickGame->frame(); }

void gameloop::stop(){ quickGame->stop(); }
