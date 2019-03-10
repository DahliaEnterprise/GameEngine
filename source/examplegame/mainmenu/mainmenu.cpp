#include "mainmenu.h"

mainmenu::mainmenu(QObject *parent) : QObject(parent)
{
}

void mainmenu::start()
{
    go = new gameobject();
    go->start(QImage(QString(":/examplegame/mainmenu/image/index.jpg")));
    go->updateImageSpecifications(50, 50, 100, 100);
}

QList<gameobject*> mainmenu::frame()
{
    QList<gameobject*> goList;
    goList.append(go);
    return goList;
}
