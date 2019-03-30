#ifndef MODULE_CARD_HIGHTLIGHTABLE_H
#define MODULE_CARD_HIGHTLIGHTABLE_H

#include <QObject>
#include "examplegame/quickgame/card/card_creature.h"
#include "examplegame/keyboardMouseInput/keyboardmouseinput.h"
#include "examplegame/quickgame/card/card_moduspraecptum.h"
#include "examplegame/quickgame/card/card_turnactivatedcard.h"

class module_card_hightlightable : public QObject
{
    Q_OBJECT
public:
    explicit module_card_hightlightable(QObject *parent = nullptr);
    void start(keyboardMouseInput* setkeyboardmouse_input);
    void highlightable(card_creature* card);
    void highlightable(card_moduspraecptum* card);
    void highlightable(card_turnactivatedcard* card);
    bool mouseOverCardArea(QMap<QString, double> dimensions);

private:
    keyboardMouseInput* keyboardmouse_input;

signals:

public slots:
};

#endif // MODULE_CARD_HIGHTLIGHTABLE_H
