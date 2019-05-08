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

    void start();

private:
    //Set from outside scope of this
    ogleMasterController* ogle;

signals:

public slots:
};

#endif // TENNIS_H
