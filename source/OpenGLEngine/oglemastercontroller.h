#ifndef OGLEMASTERCONTROLLER_H
#define OGLEMASTERCONTROLLER_H

#include <QObject>
#include "oglewindow.h"
#include "Communications/communicationscontroller.h"
#include <QThread>
class ogleMasterController : public QObject
{
    Q_OBJECT
public:
    explicit ogleMasterController(QObject *parent = nullptr);
    void start();

private:
    OGLEWindow* window;

    QThread* communicationsControlThread;
    CommunicationsController* communicationsControl;


signals:

public slots:
};

#endif // OGLEMASTERCONTROLLER_H
