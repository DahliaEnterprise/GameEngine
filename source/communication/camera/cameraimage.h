#ifndef CAMERAIMAGE_H
#define CAMERAIMAGE_H

#include <QObject>
#include "gameengine/gameobject.h"

class cameraImage : public QObject
{
    Q_OBJECT
public:
    explicit cameraImage(QObject *parent = nullptr);
    void start();
    void incomingFrame(QImage image);
signals:

public slots:
};

#endif // CAMERAIMAGE_H
