#ifndef OGLEEMBLEMVELOCITY_H
#define OGLEEMBLEMVELOCITY_H

#include <QObject>
#include <QLine>
#include <QLineF>
#include <QPoint>
#include <QPointF>
class ogleEmblemVelocity : public QObject
{
    Q_OBJECT
public:
    explicit ogleEmblemVelocity(QObject *parent = nullptr);
    void start(QPointF point1, QPointF point2);
    qreal direction();
    qreal speed();
    QPointF currentPosition();
    QPointF nextPosition();
    void setVelocity(QPointF point1, QPointF point2);

private:
    QLineF angle;

signals:

public slots:
};

#endif // OGLEEMBLEMVELOCITY_H
