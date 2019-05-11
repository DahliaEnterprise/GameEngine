#ifndef OGLEMASTERCONTROLLER_H
#define OGLEMASTERCONTROLLER_H

#include <QObject>
#include "oglewindow.h"
#include <QThread>
class ogleMasterController : public QObject
{
    Q_OBJECT
public:
    explicit ogleMasterController(QObject *parent = nullptr);
    void start();
    OGLEWindow* getWindow();

private:
    OGLEWindow* window;

signals:
    void frameRenderFinished();

public slots:
};

#endif // OGLEMASTERCONTROLLER_H
