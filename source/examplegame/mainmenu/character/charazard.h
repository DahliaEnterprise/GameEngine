#ifndef CHARAZARD_H
#define CHARAZARD_H

#include <QObject>
#include "gameengine/gameobject.h"

class charazard : public QObject
{
    Q_OBJECT
public:
    explicit charazard(QObject *parent = nullptr);
    void start();
    gameobject* game_object();

private:
    gameobject* go;


signals:

public slots:
};

#endif // CHARAZARD_H
