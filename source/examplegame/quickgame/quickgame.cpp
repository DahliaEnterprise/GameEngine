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

    transparent_background = new gameobject();//Ensures visual updates do not trail and imprint into the background.
    transparent_background->start(QImage(QString(":/examplegame/quickgame/image/transparent_background.png")));
    transparent_background->updateImageSpecifications(1,1,1920,1080,0.01);

    cardStallion = new card_creature();
    cardStallion->start(QString(":/examplegame/quickgame/image/card/creature/creature_stallion.png"));
    cardStallion->updateImageSpecifications(630, 10, 275, 370, 1);

    cardModusPraecptumStallion = new card_moduspraecptum();
    QStringList moduspraecptum_list;
    moduspraecptum_list.append(QString("tired points 100"));
    cardModusPraecptumStallion->start(QString(":/examplegame/quickgame/image/card/moduspraecptum/moduspraecptum-stallion.png"), moduspraecptum_list);
    cardModusPraecptumStallion->updateImageSpecification(20, 10, 600, 370, 1);

    cardTurnActivatedAttackStallion = new card_turnactivatedcard();
    QStringList turnactivated_list;
    turnactivated_list.append(QString("victim reduces 20 tired points"));
    cardTurnActivatedAttackStallion->start(QString(":/examplegame/quickgame/image/card/turnactivatedcard/turnactivatedcard.png"), turnactivated_list);
    cardTurnActivatedAttackStallion->updateImageSpecifications(20, 390, 300, 420, 1);

    cardStallion2 = new card_creature();
    cardStallion2->start(QString(":/examplegame/quickgame/image/card/creature/creature_stallion.png"));
    cardStallion2->updateImageSpecifications(1015, 10, 275, 375, 1);

    cardModusPraecptumStallion2 = new card_moduspraecptum();
    cardModusPraecptumStallion2->start(QString(":/examplegame/quickgame/image/card/moduspraecptum/moduspraecptum-stallion.png"), QStringList());
    cardModusPraecptumStallion2->updateImageSpecification(1300, 10, 600, 370, 1);

    cardTurnActivatedAttackStallion2 = new card_turnactivatedcard();
    cardTurnActivatedAttackStallion2->start(QString(":/examplegame/quickgame/image/card/turnactivatedcard/turnactivatedcard.png"), QStringList());
    cardTurnActivatedAttackStallion2->updateImageSpecifications(1300, 390, 300, 420, 1);

    module_highlightable_card = new module_card_hightlightable();
    module_highlightable_card->start(keyboardmouse_input);

    module_clickable_card = new module_card_clickable();
    module_clickable_card->start(keyboardmouse_input);

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
    goList.append(cardTurnActivatedAttackStallion->gameObject());

    goList.append(cardStallion2->gameObject());
    goList.append(cardModusPraecptumStallion2->gameObject());
    goList.append(cardTurnActivatedAttackStallion2->gameObject());

    //Return Prepared Frame
    return goList;
}


void quickgame::iterate_logic()
{
    //Prepare Frame

    //Close game when escape button is pressed.
    if(keyboardmouse_input->isKeyEscapePressed()){ emit playerRequestingCloseGame(); }

    //Apply "highlightable" module
    module_highlightable_card->highlightable(cardTurnActivatedAttackStallion);
    //module_highlightable_card->highlightable(cardTurnActivatedAttackStallion2);

    //Apply "clickable" module
    bool clicked = module_clickable_card->mouseClickedCardArea(cardTurnActivatedAttackStallion->gameObject()->dimensions());
    if(clicked == true)
    {
        qWarning() << "turn card activated";
        QStringList cardActions = cardTurnActivatedAttackStallion->card_actions();
        QStringList modusPraecptumActions = cardModusPraecptumStallion->card_actions();
        //this->apply_turn(cardActions, modusPraecptumActions);
    }
}
