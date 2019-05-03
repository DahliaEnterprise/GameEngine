#ifndef OGLEWINDOW_H
#define OGLEWINDOW_H

#include <QObject>
#include <QWindow>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QPainter>
#include <QDateTime>
#include <QDebug>
#include <QTimer>
#include <QRandomGenerator>
#include "Communications/communicationscontroller.h"
#include "Communications/videoframeinstruction.h"
#include <QList>
#include <QVector>
#include <QCamera>
#include "OpenGLEngine/camera/oglecameracontroller.h"
#include <QMap>
#include <QVector>
#include <QColor>
#include "OpenGLEngine/camera/camerasplitbyquality.h"
#include <QThread>
class OGLEWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OGLEWindow(QWindow *parent = nullptr);
    ~OGLEWindow() override;

    void defineCommunicationsController(CommunicationsController* setCommunicationsControl);
    void start();

    virtual void render(QPainter* painter);
    virtual void render();

    virtual void initialize();

private:
    //OpenGL and Rendering
    QOpenGLContext* ogleContext;
    QOpenGLPaintDevice* oglePaintDevice;
    QSurfaceFormat format;
    bool renderingEnabled;
    QVector<videoFrame*> onScreenVideoFrames;
    QVector<videoFrame*> offScreenVideoFrames;

    //Hardware relating to graphics
    ogleCameraController* cameraController;

    QVideoFrame cameraUnalteredVideoFrameBuffer;

    QThread* cameraSplitByQualityThread;
    cameraSplitByQuality* offScreenProcessor_splitByQuality;
    QVector<QColor> splitLQFrame;

    //Frames Per Second counter of display
    QTimer* framesUpdateKeepAlive = nullptr;
    qint64 framesTimestamp;
    int frames;
    int framesPerSecond;

    void fpsCounterOfDisplay();

    //Global Scope
    CommunicationsController* communicationsControl;

signals:
    void requestedUnalteredCameraFrame(QVideoFrame);
    void requestSplitByQuality(QVideoFrame);

public slots:
    void renderNow();
    void updateFrame();
    void screenVideoFrame(videoFrame*);
    void offScreenVideoFrame(videoFrame* vFrame);

    void cameraEmitting_unalteredCameraFrame(QVideoFrame vFrame);

private slots:
    void renderedSplitQualities(QVector<QColor>);

protected:
    bool event(QEvent* event) override;
    void exposeEvent(QExposeEvent* event) override;

};

#endif // OGLEWINDOW_H
