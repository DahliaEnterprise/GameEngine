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
class OGLEWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OGLEWindow(QWindow *parent = nullptr);
    ~OGLEWindow() override;
    void defineCommunicationsController(CommunicationsController* setCommunicationsControl);

    virtual void render(QPainter* painter);
    virtual void render();

    virtual void initialize();

private:
    QOpenGLContext* ogleContext;
    QOpenGLPaintDevice* oglePaintDevice;

    bool renderingEnabled;

    //FPS monitoring
    QTimer* framesUpdateKeepAlive;
    qint64 timestamp;
    int frames = 0;

    //Global Scope
    CommunicationsController* communicationsControl;

signals:

public slots:
    void renderNow();
    void updateFrame();
protected:
    bool event(QEvent* event) override;
    void exposeEvent(QExposeEvent* event) override;

};

#endif // OGLEWINDOW_H
