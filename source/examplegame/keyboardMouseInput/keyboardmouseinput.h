#ifndef KEYBOARDMOUSEINPUT_H
#define KEYBOARDMOUSEINPUT_H

#include <QObject>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <QMouseEvent>
#include <QCursor>
class keyboardMouseInput : public QObject
{
    Q_OBJECT
public:
    explicit keyboardMouseInput(QObject *parent = nullptr);
    void start();
    bool isKeyEscapePressed();
    int getMouseX();
    int getMouseY();
    bool getLeftMouseDown();

private:
    QTimer* pullTimer;

    bool keyEscape;
    int mouseX;
    int mouseY;
    bool leftMouseDown;

signals:

public slots:
    void incomingMousePressEvent(QMouseEvent* event);
    void incomingMouseReleaseEvent(QMouseEvent* event);
    void incomingMouseMoveEvent();
    void incomingPressEvent(QKeyEvent* event);
    void incomingReleaseEvent(QKeyEvent* event);

protected:

    void keyReleaseEvent(QKeyEvent* event);

};

#endif // KEYBOARDMOUSEINPUT_H
