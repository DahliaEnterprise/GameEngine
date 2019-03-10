#include "mainmenu.h"

mainmenu::mainmenu(QObject *parent) : QObject(parent)
{

}


void mainmenu::start()
{
    transparent_background = new gameobject();
    transparent_background->start(QImage(QString(":/examplegame/mainmenu/image/transparent_background.png")));
    transparent_background->updateImageSpecifications(0,0,1920,1080);

    charazard = new gameobject();
    charazard->start(QImage(QString(":/examplegame/mainmenu/image/index.jpg")));
    charazard->updateImageSpecifications(50, 50, 100, 100);
    x = 50;
}



QList<gameobject*> mainmenu::frame()
{
    QList<gameobject*> goList;
    goList.append(transparent_background);
    goList.append(charazard);
    x += 1;
    charazard->updateImageSpecifications(x, 50, 100, 100);
    return goList;
}
