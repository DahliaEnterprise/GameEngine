#ifndef MAINMENU_H
#define MAINMENU_H

#include <QObject>
#include "gameengine/opengl_canvas.h"
#include <QDebug>
#include "gameengine/gameobject.h"
#include "character/charazard.h"
#include <QTimer>
#include "modules/keyboardMouseInput/keyboardmouseinput.h"

class mainmenu : public QObject
{
    Q_OBJECT
public:
    explicit mainmenu(QObject *parent = nullptr);
    void start(keyboardMouseInput* setKeyboardMouseInput);
    QList<gameobject*> frame();

private:
    keyboardMouseInput* keyboardmouse_input;
    QTimer* logicWakeupTimer;
    gameobject* transparent_background;
    gameobject* charazardGO;
    charazard* playersCharacter;
    double x;

signals:
    void frame(QList<gameobject*>);
    void playerRequestingCloseGame();

public slots:

private slots:
    void iterate_logic();
};

#endif // MAINMENU_H
