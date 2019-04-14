#ifndef CARD_MODUSPRAECPTUM_H
#define CARD_MODUSPRAECPTUM_H

#include <QObject>
#include <QImage>
#include <QPainter>
#include "gameengine/gameobject.h"
#include <QFontDatabase>
#include <QDebug>
class card_moduspraecptum : public QObject
{
    Q_OBJECT
public:
    explicit card_moduspraecptum(QObject *parent = nullptr);
    void start(QString imageUrl, QStringList moduspraecptum_list);
    gameobject* gameObject();
    void updateImageSpecification(double x, double y, double width, double height, double opacity);


private:
    QImage moduspraecptumCardSourceImage;
    QImage moduspraecptumCardImage;
    gameobject* moduspraecptumGO;
    QImage moduspraecptumCardHighlightedImage;

    QStringList moduspraecptum_list;

    int points_tired;

    void process_moduspraecptum();

signals:

public slots:
};

#endif // CARD_MODUSPRAECPTUM_H
