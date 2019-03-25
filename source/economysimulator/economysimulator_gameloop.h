#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <QObject>
#include "gameengine/gameobject.h"
#include <QTimer>
#include "economysimulator/person.h"
#include "economysimulator/person_logic.h"

class economysimulator_gameloop : public QObject
{
    Q_OBJECT
public:
    explicit economysimulator_gameloop(QObject *parent = nullptr);
    void start();
    QList<gameobject*> frame();

private:
    QList<gameobject*> goList;
    QTimer* logicCycler;

    person* personone;
    person_logic* persononelogic;
signals:

public slots:

private slots:
    void iterate_logic();

};

#endif // GAMELOOP_H
