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
    transparent_background->updateImageSpecifications(0,0,1920,1080,1);


    cardStallion = new card_creature();
    cardStallion->start(QString(":/examplegame/quickgame/image/card/creature/creature_stallion.png"));
    cardStallion->updateImageSpecifications(710, 380, 200, 270, 1);


    cardModusPraecptumStallion = new card_moduspraecptum();
    cardModusPraecptumStallion->start(QString(":/examplegame/quickgame/image/card/moduspraecptum/moduspraecptum-stallion.png"), QStringList());
    cardModusPraecptumStallion->updateImageSpecification(200, 370, 500, 300, 0.95);

    cardTurnActivatedAttackStallion = new card_turnactivatedcard();
    cardTurnActivatedAttackStallion->start(QString(":/examplegame/quickgame/image/card/moduspraecptum/moduspraecptum-stallion.png"), QStringList());

    module_highlightable_card = new module_card_hightlightable();
    module_highlightable_card->start(keyboardmouse_input);

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
    goList.append(cardModusPraecptumStallion->gameObject());

    //Return Prepared Frame
    return goList;
}


void quickgame::iterate_logic()
{
    //Prepare Frame

    //Close game when escape button is pressed.
    if(keyboardmouse_input->isKeyEscapePressed()){ emit playerRequestingCloseGame(); }

    //Apply "highlightable" module
    //module_highlightable_card->highlightable(cardStallion);

}
