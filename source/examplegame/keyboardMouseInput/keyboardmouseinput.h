#ifndef KEYBOARDMOUSEINPUT_H
#define KEYBOARDMOUSEINPUT_H

#include <QObject>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>

class keyboardMouseInput : public QObject
{
    Q_OBJECT
public:
    explicit keyboardMouseInput(QObject *parent = nullptr);
    void start();
    bool isKeyEscapePressed();

private:
    QTimer* pullTimer;

    bool keyEscape;

signals:

public slots:
    void incomingPressEvent(QKeyEvent* event);
    void incomingReleaseEvent(QKeyEvent* event);

protected:

    void keyReleaseEvent(QKeyEvent* event);

};

#endif // KEYBOARDMOUSEINPUT_H
