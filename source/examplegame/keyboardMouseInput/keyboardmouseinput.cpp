#include "keyboardmouseinput.h"

keyboardMouseInput::keyboardMouseInput(QObject *parent) : QObject(parent)
{

}

void keyboardMouseInput::start()
{
    keyEscape = false;
}

void keyboardMouseInput::incomingPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Escape){ keyEscape = true; }
}

void keyboardMouseInput::incomingReleaseEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Escape){ keyEscape = false; }
}

bool keyboardMouseInput::isKeyEscapePressed(){ return keyEscape; }
