#ifndef TENNIS_H
#define TENNIS_H

#include <QObject>
#include "OpenGLEngine/oglemastercontroller.h"
#include <QOpenGLPaintDevice>
class tennis : public QObject
{
    Q_OBJECT
public:
    explicit tennis(QObject *parent = nullptr);

    void setOpenGLMasterController(ogleMasterController* setOgle);

    bool start();

    void ogleAvailableForNextFrame();

private:
    //Set from outside scope of this
    ogleMasterController* ogle; bool OGLEMasterController_isSet = false;

signals:

public slots:
};

#endif // TENNIS_H
