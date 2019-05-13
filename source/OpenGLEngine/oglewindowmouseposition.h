#ifndef OGLEWINDOWMOUSEPOSITION_H
#define OGLEWINDOWMOUSEPOSITION_H

#include <QObject>

class ogleWindowMousePosition : public QObject
{
    Q_OBJECT
public:
    explicit ogleWindowMousePosition(QObject *parent = nullptr);
    void setMousePosition(int setMouseX, int setMouseY);
    int getMouseX();
    int getMouseY();

private:
    int mouseX;
    int mouseY;

signals:

public slots:
};

#endif // OGLEWINDOWMOUSEPOSITION_H
