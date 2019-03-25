#ifndef PERSON_LOGIC_H
#define PERSON_LOGIC_H

#include <QObject>
#include <QRandomGenerator>
#include "gameengine/gameobject.h"

class person_logic : public QObject
{
    Q_OBJECT
public:
    explicit person_logic(QObject *parent = nullptr);
    void start();
    void cycle_logic(gameobject* go);

private:
    int horizontalVelocity;
    int verticalVelocity;

signals:

public slots:
};

#endif // PERSON_LOGIC_H
