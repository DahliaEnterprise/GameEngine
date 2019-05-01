#include "oglewindow.h"

OGLEWindow::OGLEWindow(QWindow *parent) : QWindow(parent)
{
    ogleContext = nullptr; oglePaintDevice = nullptr;
    this->setSurfaceType(QWindow::OpenGLSurface);
}

OGLEWindow::~OGLEWindow(){}

void OGLEWindow::render(QPainter* painter){ Q_UNUSED(painter); }
void OGLEWindow::initialize(){}
void OGLEWindow::render(){}

bool OGLEWindow::event(QEvent* event)
{
    bool output = false;
    if(event->type() == QEvent::UpdateRequest)
    {
        renderNow();
        output = true;
    }else{
        output = QWindow::event(event);
    }
    return true;
}

void OGLEWindow::exposeEvent(QExposeEvent *event){ this->renderNow(); }

void OGLEWindow::renderNow()
{
    if(this->isExposed() == true)
    {
        //(Initialize if nessecary and) Make context current
        bool initOGLF = false;
        if(ogleContext == nullptr){ ogleContext = new QOpenGLContext(this); ogleContext->setFormat(requestedFormat()); ogleContext->create(); initOGLF = true; }

        ogleContext->makeCurrent(this);

        if(initOGLF == true){ initializeOpenGLFunctions(); initialize(); }

        //render();
        //Initialize paint device and configure paint device
        if(oglePaintDevice == nullptr){ oglePaintDevice = new QOpenGLPaintDevice(); }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        oglePaintDevice->setSize(size() * devicePixelRatio());
        oglePaintDevice->setDevicePixelRatio(devicePixelRatio());

        //Draw operations
        QPainter painter(oglePaintDevice);
        QPen pen;
        pen.setColor(QColor(100,100,0,100));
        pen.setWidth(1);
        painter.setPen(pen);
        int x = 0;
        int y = 0;
        for(int i = 0; i < 1000; i++)
        {
            x += 5;
            painter.drawLine(x,0,100,100);
            if(x >= 1000){ x = 0; y += 10;}
        }

        render(&painter);

        ogleContext->swapBuffers(this);
    }
}
