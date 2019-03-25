#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <QImage>
#include <QPen>
#include <QPainter>
#include "gameengine/gameobject.h"
class person : public QObject
{
    Q_OBJECT
public:
    explicit person(QObject *parent = nullptr);
    void start();
    gameobject* gameObject();
    void updateImageSpecification(double x, double y, double width, double height, qreal opactiy);

private:
    QImage image;
    gameobject* go;

signals:

public slots:
};

#endif // PERSON_H
