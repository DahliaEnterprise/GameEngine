#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QMap>
class gameobject : public QObject
{
    Q_OBJECT
public:
    explicit gameobject(QObject *parent = nullptr);
    ~gameobject();
    void start(QImage setImage);
    void updateImageSpecifications(double x, double y, double width, double height, qreal opacity = 1);
    void paint(QPainter* painter);
    QMap<QString, double> dimensions();

private:
    double x;
    double y;
    double width;
    double height;
    qreal opacity;
    QImage image;

signals:

public slots:
};

#endif // GAMEOBJECT_H
