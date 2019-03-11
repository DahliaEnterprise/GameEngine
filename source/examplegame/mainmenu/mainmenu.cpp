#include "mainmenu.h"

mainmenu::mainmenu(QObject *parent) : QObject(parent)
{

}


void mainmenu::start(keyboardMouseInput* setKeyboardMouseInput)
{
    keyboardmouse_input = setKeyboardMouseInput;
    keyboardmouse_input->start();

    transparent_background = new gameobject();
    transparent_background->start(QImage(QString(":/examplegame/mainmenu/image/transparent_background.png")));
    transparent_background->updateImageSpecifications(0,0,1920,1080);

    playersCharacter = new charazard();
    playersCharacter->start();
    x = 50;

    logicWakeupTimer = new QTimer();
    logicWakeupTimer->setInterval(100);
    QObject::connect(logicWakeupTimer, SIGNAL(timeout()), this, SLOT(iterate_logic()));
    logicWakeupTimer->start();
}


QList<gameobject*> mainmenu::frame()
{
    //Prepare Frame
    QList<gameobject*> goList;
    goList.append(transparent_background);
    goList.append(playersCharacter->game_object());

    //Return Prepared Frame
    return goList;
}



void mainmenu::iterate_logic()
{
    //Temp logic
    if(keyboardmouse_input->isKeyEscapePressed())
    {
        emit playerRequestingCloseGame();
    }

    playersCharacter->game_object()->updateImageSpecifications(x, 150, 200, 200);

    QTimer::singleShot(5, this, SLOT(iterate_logic()));
}
