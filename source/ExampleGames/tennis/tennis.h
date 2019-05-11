#ifndef TENNIS_H
#define TENNIS_H

#include <QObject>
#include "OpenGLEngine/oglemastercontroller.h"
#include <QOpenGLPaintDevice>
#include "ExampleGames/tennis/tennis_script.h"
#include <QThread>
class tennis : public QObject
{
    Q_OBJECT
public:
    explicit tennis(QObject *parent = nullptr);

    void setOpenGLMasterController(ogleMasterController* setOgle);

    bool start();

private:
    QThread* logicThread;
    tennis_script* logic;

    //Set from outside scope of this
    ogleMasterController* ogle; bool OGLEMasterController_isSet = false;

signals:

public slots:

private slots:
    void ogleAvailableForNextFrame();
};

#endif // TENNIS_H
