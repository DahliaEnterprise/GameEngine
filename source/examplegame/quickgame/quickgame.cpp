#include "quickgame.h"

quickgame::quickgame(QObject *parent) : QObject(parent)
{

}

quickgame::~quickgame()
{

}

void quickgame::stop()
{
}


void quickgame::start(keyboardMouseInput* setKeyboardMouseInput)
{
    keyboardmouse_input = setKeyboardMouseInput;
    keyboardmouse_input->start();

    transparent_background = new gameobject();
    transparent_background->start(QImage(QString(":/examplegame/quickimage/image/transparent_background.png")));
    transparent_background->updateImageSpecifications(0,0,1920,1080, 0.0);

    cardStallion = new card_creature();
    cardStallion->start(QString(":/examplegame/quickgame/image/card/creature/creature_stallion.png"), QString(":/examplegame/quickgame/image/card/creature/creature_stallion.png"));
    cardStallion->updateImageSpecifications(200, 100, 200, 270, 0.95);

    logicWakeupTimer = new QTimer();
    logicWakeupTimer->setInterval(5);
    QObject::connect(logicWakeupTimer, SIGNAL(timeout()), this, SLOT(iterate_logic()));
    logicWakeupTimer->start();
}


QList<gameobject*> quickgame::frame()
{
    goList.clear();
    goList.append(transparent_background);
    goList.append(cardStallion->gameObject());

    //Return Prepared Frame
    return goList;
}


void quickgame::iterate_logic()
{
    //Prepare Frame

    //Close game when escape button is pressed.
    if(keyboardmouse_input->isKeyEscapePressed()){ emit playerRequestingCloseGame(); }
    if(keyboardmouse_input->getMouseX() > 200 && keyboardmouse_input->getMouseX() < 400)
    {
        cardStallion->highlighted(true);
    }else{
        cardStallion->highlighted(false);
    }
}
