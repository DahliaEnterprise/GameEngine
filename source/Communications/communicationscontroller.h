#ifndef COMMUNICATIONSCONTROLLER_H
#define COMMUNICATIONSCONTROLLER_H

#include <QObject>
#include "Communications/qcameracontroller.h"
#include <QTimer>
#include <QDebug>
#include <QList>
#include "Communications/videoframeinstruction.h"

class CommunicationsController : public QObject
{
    Q_OBJECT
public:
    explicit CommunicationsController(QObject *parent = nullptr);
    void start();
    void offscreenWork();
    void onscreenWork();

private:
    QCameraController* cameraController;
    QTimer* processorKeepAlive;
    QList<videoFrameInstruction*> videoFrame; //First shows closest to screen, last shows furthest

signals:
    void videoFrameInstructions(QList<videoFrameInstruction*>);

public slots:

private slots:
    void processor();
};

#endif // COMMUNICATIONSCONTROLLER_H
