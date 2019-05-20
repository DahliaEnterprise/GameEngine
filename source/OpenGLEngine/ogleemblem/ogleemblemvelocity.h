#ifndef OGLEEMBLEMVELOCITY_H
#define OGLEEMBLEMVELOCITY_H

#include <QObject>
#include <QLine>
#include <QPoint>
class ogleEmblemVelocity : public QObject
{
    Q_OBJECT
public:
    explicit ogleEmblemVelocity(QObject *parent = nullptr);
    void start(QPoint point1, QPoint point2);
    qreal direction();
    qreal speed();
    QPointF currentPosition();
    void setVelocity(QPoint point1, QPoint point2);

private:
    QLineF angle;

signals:

public slots:
};

#endif // OGLEEMBLEMVELOCITY_H
