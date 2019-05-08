#include "oglewindow.h"

OGLEWindow::OGLEWindow(QWindow *parent) : QWindow(parent)
{
    ogleContext = nullptr; oglePaintDevice = nullptr;
    this->setSurfaceType(QWindow::OpenGLSurface);
    format.setSamples(0); format.setSwapBehavior(QSurfaceFormat::DoubleBuffer); format.setStencilBufferSize(8);this->setFormat(format);
    this->create();
    this->setPosition(100,100); this->resize(1280,720);
    framesTimestamp = QDateTime::currentMSecsSinceEpoch(); frames = 0; framesPerSecond = 0;
    renderingEnabled = true;
}

OGLEWindow::~OGLEWindow(){}

void OGLEWindow::start()
{
    //if(framesUpdateKeepAlive == nullptr){ framesUpdateKeepAlive = new QTimer(); QObject::connect(framesUpdateKeepAlive, SIGNAL(timeout()), this, SLOT(updateFrame())); framesUpdateKeepAlive->start(5); }
}


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

//void OGLEWindow::updateFrame(){ requestUpdate(); }

void OGLEWindow::renderNow()
{
    if(this->isExposed() == true)
    {
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
            painter.setRenderHint(QPainter::Antialiasing, true);
            painter.setCompositionMode(QPainter::CompositionMode_SourceOver);


            /** Onscreen work **
            if(onScreenVideoFrames.isEmpty() == false)
            {   //Video Frame Instructions Available
                videoFrame* vFrame = onScreenVideoFrames.at(0);
                while(vFrame->hasNextInstruction() == true)
                {
                    videoFrameInstruction* vfi = vFrame->getNextInstruction();
                    if(vfi->instructionType() == videoFrameInstruction::Text)
                    {
                        QRandomGenerator random;
                        QPen pen;

                        pen.setColor(QColor(25, 255, 200, 255));
                        pen.setWidth(1);
                        painter.setPen(pen);
                        painter.setFont(QFont(QString("Arial"), 15, 1, false));
                        painter.drawText(QPointF(0,100), vfi->getText());

                    }else if(vfi->instructionType() == videoFrameInstruction::UnalteredCameraVideoFrame)
                    {
                        //Deep Copy, Incoming Camera Unaltered Video Frame
                        cameraUnalteredVideoFrameBuffer.map(QAbstractVideoBuffer::ReadOnly);
                        QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(cameraUnalteredVideoFrameBuffer.pixelFormat());
                        QImage VideoFrameAsImage = QImage(cameraUnalteredVideoFrameBuffer.bits(), cameraUnalteredVideoFrameBuffer.width(), cameraUnalteredVideoFrameBuffer.height(), cameraUnalteredVideoFrameBuffer.bytesPerLine(), imageFormat);
                        painter.drawImage(QRect(0,0,1280,720), VideoFrameAsImage);
                    }else if(vfi->instructionType() == videoFrameInstruction::SplitQualitiesVideoFrame)
                    {
                        //Display split quality
                        if(bufferedSplitFrames.isEmpty() == false)
                        {
                            QVector<QColor> frame = bufferedSplitFrames.first();

                            int x = 0; int y = 0;
                            QVector<QColor>::const_iterator iterator = frame.constBegin();
                            while(iterator != frame.constEnd())
                            {
                                QColor color = *iterator;
                                //painter.fillRect(QRect(x,y, 1,1), color);
                                x+= 1;
                                if(x >= 1280)
                                {
                                    x = 0;
                                    y++;
                                }

                                iterator++;
                            }

                            bufferedSplitFrames.removeFirst();
                        }


                        int x = 0; int y = 0;
                        QVector<QColor>::const_iterator iterator = displayMatrix.constBegin();
                        while(iterator != displayMatrix.constEnd())
                        {
                            QColor color = *iterator;
                            //qWarning() << color;
                            //painter.fillRect(QRect(x,y, 1,1), color);
                            //painter.fillRect(QRect(x,y, 1,1), QColor(0,100,0,255));
                            x+= 1;
                            if(x >= 1280)
                            {
                                x = 0;
                                y++;
                            }

                            iterator++;
                        }
                        if(false == cameraSplitByQualityCaptureTimer->isActive()) {cameraSplitByQualityCaptureTimer->start(100);}

                    }
                }

                //Remove consumed frame
                onScreenVideoFrames.removeFirst();

                //Remove frames until size is achieved
                /** DEPRECATED MOVE TO A TIMER BASED GARBASE COLLECTION
                if(onScreenVideoFrames.size() >= 60)
                {
                    bool alternate = false;
                    int index = 0;
                    while(onScreenVideoFrames.size() >= 60)
                    {
                        if(alternate == false)
                        {
                            index += 2;
                            if(index < onScreenVideoFrames.size())
                            {
                                onScreenVideoFrames.removeAt(index);
                                alternate = true;
                            }

                        }else if(alternate == true)
                        {
                            index += 3;
                            if(index < onScreenVideoFrames.size())
                            {
                                onScreenVideoFrames.removeAt(index);
                                alternate = false;
                            }
                        }

                        if(index >= onScreenVideoFrames.size()-1)
                        {
                            index = 0;
                        }
                    }
                }

            }*/
            //render(&painter);

            ogleContext->swapBuffers(this);
        }
    }
}


void OGLEWindow::fpsCounterOfDisplay()
{
    frames++;
    qint64 sinceLastFrame = QDateTime::currentMSecsSinceEpoch() - framesTimestamp;
    if(sinceLastFrame > 1000)
    {
        //qWarning() << frames;
        framesTimestamp = QDateTime::currentMSecsSinceEpoch();
        frames = 0;
    }
}
