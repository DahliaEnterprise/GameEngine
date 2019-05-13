#ifndef OGLEMASTERCONTROLLER_H
#define OGLEMASTERCONTROLLER_H

#include <QObject>
#include "oglewindow.h"
#include <QThread>
#include "ExampleGames/tennis/tennis.h"
#include <QTimer>
class ogleMasterController : public QObject
{
    Q_OBJECT
public:
    explicit ogleMasterController(QObject *parent = nullptr);
    void start();
    OGLEWindow* getWindow();

private:
    tennis* t;
    OGLEWindow* window;
    QTimer* mousePositionUpdateTimer;

signals:

public slots:
    void frameRenderFinished();

private slots:
    void updatedMousePosition();
};

#endif // OGLEMASTERCONTROLLER_H
