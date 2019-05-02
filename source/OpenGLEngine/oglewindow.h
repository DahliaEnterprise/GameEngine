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
class OGLEWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OGLEWindow(QWindow *parent = nullptr);
    ~OGLEWindow() override;
    void start();

    void defineCommunicationsController(CommunicationsController* setCommunicationsControl);

    virtual void render(QPainter* painter);
    virtual void render();

    virtual void initialize();

private:
    //OpenGL and Rendering
    QOpenGLContext* ogleContext;
    QOpenGLPaintDevice* oglePaintDevice;
    QSurfaceFormat format;
    bool renderingEnabled;
    QList<videoFrame*> bufferedFrames;

    //Hardware relating to graphics
    ogleCameraController* cameraController;
    QVideoFrame cameraUnalteredVideoFrameBuffer;
    QMap<int, qint64> unalteredCameraVideoStream_fpsManagement;
    QMap<int, QVideoFrame> unalteredCameraVideoStream_sustainedFrame;

    //Frames Per Second counter of display
    QTimer* framesUpdateKeepAlive = nullptr;
    qint64 timestamp;
    int frames = 0;

    //Global Scope
    CommunicationsController* communicationsControl;

signals:
    void requestedUnalteredCameraFrame(QVideoFrame shallowVFrame);

public slots:
    void renderNow();
    void updateFrame();
    void screenVideoFrame(videoFrame*);
    void unalteredCameraFrame(QVideoFrame vFrame);

protected:
    bool event(QEvent* event) override;
    void exposeEvent(QExposeEvent* event) override;

};

#endif // OGLEWINDOW_H
