#include "person_logic.h"

person_logic::person_logic(QObject *parent) : QObject(parent)
{

}

void person_logic::start()
{

}

void person_logic::cycle_logic(gameobject* go)
{
    //Move in random directions
    ///Generate different direction
    QRandomGenerator random;
    horizontalVelocity = random.bounded(0, 5);
    verticalVelocity = random.bounded(0, 5);
    horizontalVelocity -= 3;
    verticalVelocity -= 3;

    ///Apply changes according to velocity
    QMap<QString, double> dimensions = go->dimensions();
    go->updateImageSpecifications(dimensions.value(QString("x")) + horizontalVelocity,
                                  dimensions.value(QString("y")) + verticalVelocity,
                                  50,50,0.5);
}
