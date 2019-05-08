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

private:
    OGLEWindow* window;

signals:

public slots:
};

#endif // OGLEMASTERCONTROLLER_H
