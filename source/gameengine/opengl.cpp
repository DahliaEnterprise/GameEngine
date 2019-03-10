#include "opengl.h"

opengl::opengl(opengl_canvas* setCanvas)
{
    canvas = setCanvas;
}

void opengl::start()
{
    this->move(0, 0);
    QDesktopWidget* desktop = QApplication::desktop();
    int screen_width = desktop->width();
    int screen_height = desktop->height();
    this->setFixedSize(screen_width, screen_height);
    this->setAutoFillBackground(false);
    this->setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_NoSystemBackground, true);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setAttribute(Qt::WA_AlwaysStackOnTop);

    this->setUpdateBehavior(QOpenGLWidget::NoPartialUpdate);

    QSurfaceFormat surface = this->format();
    surface.setSamples(8);
    surface.setSwapBehavior(QSurfaceFormat::TripleBuffer);
    this->setFormat(surface);
}

void opengl::paintEvent(QPaintEvent* event)
{
    //Initalize and Setup Painter
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

    //Render
    canvas->paint(&painter, event);

    //Clear resources
    painter.end();
}

void opengl::gpu_update(){ this->update(); }
