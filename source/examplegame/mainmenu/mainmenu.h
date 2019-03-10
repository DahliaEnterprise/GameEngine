#ifndef MAINMENU_H
#define MAINMENU_H

#include <QObject>
#include "gameengine/opengl_canvas.h"
#include <QDebug>
#include "gameengine/gameobject.h"
class mainmenu : public QObject
{
    Q_OBJECT
public:
    explicit mainmenu(QObject *parent = nullptr);
    void start();
    QList<gameobject*> frame();

private:
    gameobject* go;

signals:
    void frame(QList<gameobject*>);

public slots:
};

#endif // MAINMENU_H
