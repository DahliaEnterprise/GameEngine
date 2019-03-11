#include "charazard.h"

charazard::charazard(QObject *parent) : QObject(parent)
{

}

void charazard::start()
{
    go = new gameobject();
    go->start(QImage(QString(":/examplegame/mainmenu/image/charazard.png")));
    go->updateImageSpecifications(50, 50, 200, 200);
}

gameobject* charazard::game_object(){ return go; }
