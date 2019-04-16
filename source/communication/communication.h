#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QList>
#include "gameengine/gameobject.h"
#include "communication/communication_graphics_and_processing.h"
class communication : public QObject
{
    Q_OBJECT
public:
    explicit communication(QObject *parent = nullptr);
    void start();
    QList<gameobject*> frame();

private:
    communication_graphics_and_processing* graphicsandprocessing;

signals:
    void userRequestingCloseApp();

public slots:
};

#endif // COMMUNICATION_H
