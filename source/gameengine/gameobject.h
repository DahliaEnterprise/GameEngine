#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QPainter>
#include <QImage>
class gameobject : public QObject
{
    Q_OBJECT
public:
    explicit gameobject(QObject *parent = nullptr);
    void start(QImage setImage);
    void updateImageSpecifications(double x, double y, double width, double height);
    void paint(QPainter* painter);

private:
    double x;
    double y;
    double width;
    double height;
    QImage image;

signals:

public slots:
};

#endif // GAMEOBJECT_H
