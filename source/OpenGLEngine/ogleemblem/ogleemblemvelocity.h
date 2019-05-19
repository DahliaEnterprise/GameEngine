#ifndef OGLEEMBLEMVELOCITY_H
#define OGLEEMBLEMVELOCITY_H

#include <QObject>

class ogleEmblemVelocity : public QObject
{
    Q_OBJECT
public:
    explicit ogleEmblemVelocity(QObject *parent = nullptr);
    void start(int currentX, int currentY, int velocityX, int velocityY);
    int currentX();
    int direction();

signals:

public slots:
};

#endif // OGLEEMBLEMVELOCITY_H
