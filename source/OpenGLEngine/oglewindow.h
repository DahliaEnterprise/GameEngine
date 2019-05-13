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
#include <QList>
#include <QVector>
#include <QMap>
#include <QThread>
#include <QRandomGenerator>
#include <QOpenGLWindow>
#include <QCursor>
#include <QDateTime>
#include "OpenGLEngine/oglewindowmouseposition.h"
#include "OpenGLEngine/ogleemblem.h"
class OGLEWindow : public QOpenGLWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OGLEWindow(QOpenGLWindow::UpdateBehavior updateBehavior = NoPartialUpdate, QOpenGLWindow *parent = nullptr);
    ~OGLEWindow() override;

    void start();
    void nextFrame(QVector<ogleEmblem*> emblemListToNextFrame);

    ogleWindowMousePosition* getMousePosition();

    //Overloaded
    virtual void render(QPainter* painter);
    virtual void render();

    virtual void initialize();

private:
    //OpenGL and Rendering
    QOpenGLContext* ogleContext;
    QOpenGLPaintDevice* oglePaintDevice;
    QSurfaceFormat format;
    QTimer* renderTimer;
    void initalizeOglePaintDevice();
    ogleWindowMousePosition* OGLEMousePosition;
    QVector<ogleEmblem*> frameAEmblems;

    //Mouse
    qint64 mouseUpdatedTimestamp;
    int mouseX;
    int mouseY;

    //Frames Per Second counter of display
    qint64 framesTimestamp;
    int frames;
    int framesPerSecond;
    void fpsCounterOfDisplay();

signals:
    void frameRenderFinished();

public slots:
    void renderNow();

private slots:
    void requestRenderUpdate();

protected:
    bool event(QEvent* event) override;
    void exposeEvent(QExposeEvent* event) override;
    void mouseMoveEvent(QMouseEvent * event) override;

};

#endif // OGLEWINDOW_H
