#include "opengl.h"

opengl::opengl(opengl_canvas* setCanvas)
{
    canvas = setCanvas;
}

void opengl::start(keyboardMouseInput* setKeyboardMouseInput)
{
    keyboardmouse_input = setKeyboardMouseInput;

    this->move(0, 0);
    QDesktopWidget* desktop = QApplication::desktop();
    int screen_width = desktop->width();
    int screen_height = desktop->height();
    //this->setFixedSize(screen_width, screen_height);
    //this->setFixedSize(500, 500);
    this->resize(1280,720);
    this->setAutoFillBackground(false);
    //muted:this->setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    //muted:this->setAttribute(Qt::WA_NoSystemBackground, true);
    //muted:this->setAttribute(Qt::WA_TranslucentBackground, true);
    //muted:this->setAttribute(Qt::WA_AlwaysStackOnTop);

    this->setUpdateBehavior(QOpenGLWidget::PartialUpdate);

    QSurfaceFormat surface = this->format();
    surface.setMajorVersion(3);
    surface.setRenderableType(QSurfaceFormat::OpenGLES);
    //surface.setSamples(8);
    surface.setSwapBehavior(QSurfaceFormat::TripleBuffer);
    this->setFormat(surface);
}



void opengl::paintEvent(QPaintEvent* event)
{
    //Initalize and Setup Painter
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setCompositionMode(QPainter::CompositionMode_Source);

    //Render
    canvas->paint(&painter, event);

    //Clear resources
    painter.end();
}

void opengl::keyPressEvent(QKeyEvent* event){ keyboardmouse_input->incomingPressEvent(event); }
void opengl::keyReleaseEvent(QKeyEvent* event){ keyboardmouse_input->incomingReleaseEvent(event); }
void opengl::mousePressEvent(QMouseEvent* event){ keyboardmouse_input->incomingMousePressEvent(event); }
//void opengl::mouseMoveEvent(QMouseEvent* event){ keyboardmouse_input->incomingMouseMoveEvent(event); }
void opengl::mouseReleaseEvent(QMouseEvent* event){ keyboardmouse_input->incomingMouseReleaseEvent(event); }
void opengl::gpu_update(){ this->update(); }
