#include "keyboardmouseinput.h"

keyboardMouseInput::keyboardMouseInput(QObject *parent) : QObject(parent)
{

}

void keyboardMouseInput::start()
{
    keyEscape = false;
    leftMouseDown = false;
    pullTimer = new QTimer();
    pullTimer->setInterval(50);
    QObject::connect(pullTimer, SIGNAL(timeout()), this, SLOT(incomingMouseMoveEvent()));
    pullTimer->start();
}

void keyboardMouseInput::incomingMousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        leftMouseDown = true;
    }
}

void keyboardMouseInput::incomingMouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        leftMouseDown = false;
    }
}

void keyboardMouseInput::incomingMouseMoveEvent()
{
    mouseX = QCursor::pos().x();
    mouseY = QCursor::pos().y();
}

void keyboardMouseInput::incomingPressEvent(QKeyEvent* event)
{
    //Keyboard
    if(event->key() == Qt::Key_Escape){ keyEscape = true; }
}

void keyboardMouseInput::incomingReleaseEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Escape){ keyEscape = false; }
}

bool keyboardMouseInput::isKeyEscapePressed(){ return keyEscape; }

int keyboardMouseInput::getMouseX(){ return mouseX; }

int keyboardMouseInput::getMouseY(){ return mouseY; }

bool keyboardMouseInput::getLeftMouseDown(){ return leftMouseDown; }
