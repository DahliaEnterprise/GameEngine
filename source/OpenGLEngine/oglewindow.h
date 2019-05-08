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
class OGLEWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OGLEWindow(QWindow *parent = nullptr);
    ~OGLEWindow() override;

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
    QTimer* renderTimer;

    //Frames Per Second counter of display
    qint64 framesTimestamp;
    int frames;
    int framesPerSecond;

    void fpsCounterOfDisplay();

signals:

public slots:
    void renderNow();
    //void updateFrame();

private slots:
    void requestRenderUpdate();

protected:
    bool event(QEvent* event) override;
    void exposeEvent(QExposeEvent* event) override;

};

#endif // OGLEWINDOW_H
