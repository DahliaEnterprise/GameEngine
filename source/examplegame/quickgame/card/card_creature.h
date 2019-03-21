#ifndef CARD_CREATURE_H
#define CARD_CREATURE_H

#include <QObject>
#include <QImage>
#include "gameengine/gameobject.h"
#include <QDebug>
class card_creature : public QObject
{
    Q_OBJECT
public:
    explicit card_creature(QObject *parent = nullptr);
    void start(QString imageUrl, QString imageUrlHighlighted);
    gameobject* gameObject();
    void highlighted(bool setIsHighlighted);
    void updateImageSpecifications(double x, double y, double width, double height, qreal opacity);

private:
    QImage creatureCardSourceImage;
    QImage creatureCardImage;
    gameobject* creatureCardGameObject;

    QImage creatureCardHighlightedImage;

    bool isHighlighted;

signals:

public slots:
};

#endif // CARD_CREATURE_H
