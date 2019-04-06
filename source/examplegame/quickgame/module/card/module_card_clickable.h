#ifndef MODULE_CARD_CLICKABLE_H
#define MODULE_CARD_CLICKABLE_H

#include <QObject>
#include "examplegame/keyboardMouseInput/keyboardmouseinput.h"

class module_card_clickable : public QObject
{
    Q_OBJECT
public:
    explicit module_card_clickable(QObject *parent = nullptr);
    void start(keyboardMouseInput* setkeyboardmouse_input);
    bool mouseClickedCardArea(QMap<QString, double> dimensions);

private:
    keyboardMouseInput* keyboardmouse_input;

signals:

public slots:
};

#endif // MODULE_CARD_CLICKABLE_H
