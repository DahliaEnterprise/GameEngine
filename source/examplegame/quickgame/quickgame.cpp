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
    cardStallion->updateImageSpecifications(710, 170, 200, 270, 1);

    cardModusPraecptumStallion = new card_moduspraecptum();
    cardModusPraecptumStallion->start(QString(":/examplegame/quickgame/image/card/moduspraecptum/moduspraecptum-stallion.png"), QStringList());
    cardModusPraecptumStallion->updateImageSpecification(100, 100, 500, 320, 1);

    cardTurnActivatedAttackStallion = new card_turnactivatedcard();
    cardTurnActivatedAttackStallion->start(QString(":/examplegame/quickgame/image/card/turnactivatedcard/turnactivatedcard.png"), QStringList());
    cardTurnActivatedAttackStallion->updateImageSpecifications(100, 500, 300, 420, 1);

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
    goList.append(cardTurnActivatedAttackStallion->gameObject());

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

    //Temporary: move card a pixel to the right
    QMap<QString, double> dimensions = cardStallion->dimensions();
    double x = dimensions.value(QString("x"));
    double y = dimensions.value(QString("y"));
    double width = dimensions.value(QString("w"));
    double height = dimensions.value(QString("h"));
    x += 1;
    cardStallion->updateImageSpecifications(x, y, width, height, 1);
}
