#include "oglewindow.h"

OGLEWindow::OGLEWindow(QWindow *parent) : QWindow(parent)
{
    ogleContext = nullptr; oglePaintDevice = nullptr;
    this->setSurfaceType(QWindow::OpenGLSurface);
    format.setSamples(2);//multisampling
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    format.setStencilBufferSize(8);
    this->setFormat(format);
    this->create();

    renderingEnabled = true;
}

OGLEWindow::~OGLEWindow(){}

void OGLEWindow::defineCommunicationsController(CommunicationsController* setCommunicationsControl){ communicationsControl = setCommunicationsControl; }

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
        if(framesUpdateKeepAlive == nullptr)
        {
            framesUpdateKeepAlive = new QTimer();
            QObject::connect(framesUpdateKeepAlive, SIGNAL(timeout()), this, SLOT(updateFrame()));
            framesUpdateKeepAlive->start(5);
        }

        if(timestamp == 0){ timestamp = QDateTime::currentMSecsSinceEpoch(); }

        if(renderingEnabled == true)
        {
            //(Initialize if nessecary and) Make context current
            bool initOGLF = false;
            if(ogleContext == nullptr){ ogleContext = new QOpenGLContext(this); ogleContext->setFormat(format); ogleContext->create(); initOGLF = true; }

            ogleContext->makeCurrent(this);

            if(initOGLF == true){  initializeOpenGLFunctions(); initialize(); }

            //render();
            //Initialize paint device and configure paint device
            if(oglePaintDevice == nullptr){ oglePaintDevice = new QOpenGLPaintDevice(); }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            oglePaintDevice->setSize(size() * devicePixelRatio());
            oglePaintDevice->setDevicePixelRatio(devicePixelRatio());

            /// Draw operations
            QPainter painter(oglePaintDevice);
            painter.setCompositionMode(QPainter::CompositionMode_Source);

            /** Offscreen work **/
            //TODO: accept offscreen work

            /** Onscreen work **/
            QPen pen;
            QRandomGenerator random;

            pen.setColor(QColor(QString::number(random.bounded(255)).toInt(),QString::number(random.bounded(255)).toInt(),QString::number(random.bounded(255)).toInt(),100));
            pen.setWidth(1);
            painter.setPen(pen);
            painter.setFont(QFont(QString("Arial"), 15, 1, false));
            if(bufferedFrames.isEmpty() == false)
            {
                videoFrame* vFrame = bufferedFrames.first();
                if(vFrame != nullptr)
                {
                    QVector<videoFrameInstruction*> vfiList = vFrame->videoFrameInstructionList();
                    if(vfiList.isEmpty() == false)
                    {
                        //TODO: loop through all the instructions contained in the video frame
                        videoFrameInstruction* vfi = vfiList.at(0);
                        painter.drawText(QPointF(0,100), vfi->getText());
                    }
                }
            }
/*

            int x = 0;
            int y = 0;
            for(int i = 0; i < 1000; i++)
            {
                x += 5;
                painter.drawLine(x,0,100,100);
                if(x >= 1000){ x = 0; y += 10;}
            }
*/
            //render(&painter);

            frames++;
            qint64 sinceLastFrame = QDateTime::currentMSecsSinceEpoch() - timestamp;
            if(sinceLastFrame > 1000)
            {
                qWarning() << frames;
                timestamp = QDateTime::currentMSecsSinceEpoch();
                frames = 0;
            }
            ogleContext->swapBuffers(this);
        }
    }
}

void OGLEWindow::updateFrame(){ requestUpdate(); }

/** DEPRECATED
void OGLEWindow::videoFrameInstructions(QList<videoFrameInstruction*> videoFrameInstructionList)
{
    if(videoFrameInstructionList.isEmpty() == false)
    {
        bufferedFrames.append(videoFrameInstructionList);
        //qWarning() << videoFrameInstructionList.at(0)->getText();
    }
}
**/

void OGLEWindow::screenVideoFrame(videoFrame* vFrame)
{
    if(vFrame != nullptr){ bufferedFrames.append(vFrame); }
}
