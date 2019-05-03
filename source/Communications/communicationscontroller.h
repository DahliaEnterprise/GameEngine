#ifndef COMMUNICATIONSCONTROLLER_H
#define COMMUNICATIONSCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QList>
#include "Communications/videoframeinstruction.h"
#include "Communications/videoframe.h"
#include <QPainter>
#include <QDateTime>
class CommunicationsController : public QObject
{
    Q_OBJECT
public:
    explicit CommunicationsController(QObject *parent = nullptr);
    void start();

private:
    QTimer* processorKeepAlive;
    qint64 timestampUnalteredCameraFrame;
    int targetVFIrate;
    int timebetweenFrames;
    int updateInterval;

signals:
    void screenVideoFrame(videoFrame*);
    void offScreenVideoFrame(videoFrame*);

public slots:

private slots:
    void processor();
};

#endif // COMMUNICATIONSCONTROLLER_H
