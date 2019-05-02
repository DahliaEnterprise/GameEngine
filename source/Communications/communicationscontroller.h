#ifndef COMMUNICATIONSCONTROLLER_H
#define COMMUNICATIONSCONTROLLER_H

#include <QObject>
#include "Communications/qcameracontroller.h"
#include <QTimer>
#include <QDebug>
#include <QList>
#include "Communications/videoframeinstruction.h"
#include "Communications/videoframe.h"
#include <QPainter>
class CommunicationsController : public QObject
{
    Q_OBJECT
public:
    explicit CommunicationsController(QObject *parent = nullptr);
    void start();

private:
    QCameraController* cameraController;
    QTimer* processorKeepAlive;

signals:
    void videoFrameInstructions(QList<videoFrameInstruction*>);
    void screenVideoFrame(videoFrame*);

public slots:

private slots:
    void processor();
};

#endif // COMMUNICATIONSCONTROLLER_H
