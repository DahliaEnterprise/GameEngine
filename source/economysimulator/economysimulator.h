#ifndef ECONOMYSIMULATOR_H
#define ECONOMYSIMULATOR_H

#include <QObject>
#include "gameengine/gameobject.h"
#include "economysimulator/economysimulator_gameloop.h"

class economysimulator : public QObject
{
    Q_OBJECT
public:
    explicit economysimulator(QObject *parent = nullptr);
    void start();
    void stop();

private:
    economysimulator_gameloop* game;
    QList<gameobject*> frame();

signals:

public slots:
};

#endif // ECONOMYSIMULATOR_H
