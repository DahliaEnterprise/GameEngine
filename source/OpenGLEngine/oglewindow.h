#ifndef OGLEWINDOW_H
#define OGLEWINDOW_H

#include <QObject>
#include <QWindow>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QPainter>

class OGLEWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OGLEWindow(QWindow *parent = nullptr);
    ~OGLEWindow() override;

    virtual void render(QPainter* painter);
    virtual void render();

    virtual void initialize();

private:
    QOpenGLContext* ogleContext;
    QOpenGLPaintDevice* oglePaintDevice;

signals:

public slots:
    void renderNow();

protected:
    bool event(QEvent* event) override;
    void exposeEvent(QExposeEvent* event) override;

};

#endif // OGLEWINDOW_H
