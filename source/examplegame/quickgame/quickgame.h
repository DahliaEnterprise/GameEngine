#ifndef MAINMENU_H
#define MAINMENU_H

#include <QObject>
#include "gameengine/opengl_canvas.h"
#include <QDebug>
#include "gameengine/gameobject.h"
//#include "character/charazard.h"
#include "examplegame/quickgame/card/card_creature.h"
#include <QTimer>
#include "examplegame/keyboardMouseInput/keyboardmouseinput.h"
#include "examplegame/quickgame/card/card_moduspraecptum.h"
#include "examplegame/quickgame/module/card/module_card_hightlightable.h"
#include "examplegame/quickgame/card/card_turnactivatedcard.h"
class quickgame : public QObject
{
    Q_OBJECT
public:
    explicit quickgame(QObject *parent = nullptr);
    ~quickgame();
    void stop();
    void start(keyboardMouseInput* setKeyboardMouseInput);
    QList<gameobject*> frame();


private:
    keyboardMouseInput* keyboardmouse_input;
    QTimer* logicWakeupTimer;
    gameobject* transparent_background;

    card_creature* cardStallion;
    card_moduspraecptum* cardModusPraecptumStallion;
    card_turnactivatedcard* cardTurnActivatedAttackStallion;

    card_creature* cardStallion2;
    card_moduspraecptum* cardModusPraecptumStallion2;
    card_turnactivatedcard* cardTurnActivatedAttackStallion2;


    module_card_hightlightable* module_highlightable_card;

    QList<gameobject*> goList;

signals:
    void frame(QList<gameobject*>);
    void playerRequestingCloseGame();

public slots:

private slots:
    void iterate_logic();
};

#endif // MAINMENU_H
