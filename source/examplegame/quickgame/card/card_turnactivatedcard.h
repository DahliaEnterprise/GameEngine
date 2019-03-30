#ifndef CARD_TURNACTIVATEDCARD_H
#define CARD_TURNACTIVATEDCARD_H

#include <QObject>
#include <QImage>
#include <QPainter>
#include "gameengine/gameobject.h"

class card_turnactivatedcard : public QObject
{
    Q_OBJECT
public:
    explicit card_turnactivatedcard(QObject *parent = nullptr);
    void start(QString imageUrl, QStringList turnactivatedcard_list);
    gameobject* gameObject();
    void highlighted(bool setIsHighlighted);
    void updateImageSpecifications(double x, double y, double width, double height, double opacity);

private:
    QImage turnactivatedcardSourceImage;
    QImage turnactivatedcardImage;
    QImage turnactivatedcardHighlightedImage;
    gameobject* turnactivatedcardGo;
    bool isHighlighted;

signals:

public slots:
};

#endif // CARD_TURNACTIVATEDCARD_H
