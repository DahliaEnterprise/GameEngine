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
    //charazard* playersCharacter;

    card_creature* cardStallion;

    QList<gameobject*> goList;

signals:
    void frame(QList<gameobject*>);
    void playerRequestingCloseGame();

public slots:

private slots:
    void iterate_logic();
};

#endif // MAINMENU_H
