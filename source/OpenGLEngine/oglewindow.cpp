#include "oglewindow.h"

OGLEWindow::OGLEWindow(QWindow *parent) : QWindow(parent)
{
    ogleContext = nullptr; oglePaintDevice = nullptr;
    this->setSurfaceType(QWindow::OpenGLSurface);
    format.setSamples(8);//multisampling
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    format.setStencilBufferSize(8);
    this->setFormat(format);
    this->create();
    this->setPosition(100,100);
    this->resize(1280,720);
    framesTimestamp = QDateTime::currentMSecsSinceEpoch();
    frames = 0;
    framesPerSecond = 0;
    renderingEnabled = true;
}

OGLEWindow::~OGLEWindow(){}


void OGLEWindow::defineCommunicationsController(CommunicationsController* setCommunicationsControl){ communicationsControl = setCommunicationsControl; }
void OGLEWindow::start()
{

    //Start Camera
    cameraController = new ogleCameraController();
    cameraController->start();

    //Start "Split By Quality" (Off Screen Processor)
    cameraSplitByQualityThread = new QThread();
    offScreenProcessor_splitByQuality = new cameraSplitByQuality();
    offScreenProcessor_splitByQuality->start();
    offScreenProcessor_splitByQuality->moveToThread(cameraSplitByQualityThread);
    cameraSplitByQualityThread->start();

    //Emit Signals of Unaltered Camera Frames
    if(framesUpdateKeepAlive == nullptr){ framesUpdateKeepAlive = new QTimer(); QObject::connect(framesUpdateKeepAlive, SIGNAL(timeout()), this, SLOT(updateFrame())); framesUpdateKeepAlive->start(5); }

    //signals slots
    QObject::connect(cameraController, SIGNAL(unalteredCameraFrame(QVideoFrame)), this, SLOT(cameraEmitting_unalteredCameraFrame(QVideoFrame)));
    QObject::connect(this, SIGNAL(requestSplitByQuality(QVideoFrame)), offScreenProcessor_splitByQuality, SLOT(requestSplitByQuality(QVideoFrame)));
    QObject::connect(offScreenProcessor_splitByQuality, SIGNAL(renderedSplitQualities(QVector<QColor>)), this, SLOT(renderedSplitQualities(QVector<QColor>)));
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

void OGLEWindow::updateFrame(){ requestUpdate(); }

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

            /** Onscreen work **/
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
                        if(splitLQFrame.size() > 0)
                        {
                            int x = 0; int y = 0;
                            for(int i = 0; i < splitLQFrame.size(); i++)
                            {
                                painter.fillRect(QRect(x,y, 1,1), splitLQFrame.at(i));
                                x+= 2;
                                if(x >= 1279)
                                {
                                    x = 0;
                                    y++;
                                }
                            }
                        }

                        //Request another split quality
                        emit requestSplitByQuality(cameraUnalteredVideoFrameBuffer);
                    }
                }

                //Remove consumed frame
                onScreenVideoFrames.removeFirst();

                //Remove frames until size is achieved
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

                //qWarning() << onScreenVideoFrames.size();
            }
            //render(&painter);


            /** Offscreen work **
            if(offScreenVideoFrames.isEmpty() == false)
            {   //Video Frame Instructions Available
                videoFrame* vFrame = offScreenVideoFrames.at(0);
                while(vFrame->hasNextInstruction() == true)
                {
                    videoFrameInstruction* vfi = vFrame->getNextInstruction();
                    if(vfi->instructionType() == videoFrameInstruction::SplitQualitiesVideoFrame)
                    {
                        /*
                        cameraUnalteredVideoFrameBuffer.map(QAbstractVideoBuffer::ReadOnly);
                        QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(cameraUnalteredVideoFrameBuffer.pixelFormat());
                        QImage VideoFrameAsImage = QImage(cameraUnalteredVideoFrameBuffer.bits(), cameraUnalteredVideoFrameBuffer.width(), cameraUnalteredVideoFrameBuffer.height(), cameraUnalteredVideoFrameBuffer.bytesPerLine(), imageFormat);
                        emit requestSplitByQuality(VideoFrameAsImage);
                        /

                        emit requestSplitByQuality(cameraUnalteredVideoFrameBuffer);
                    }
                }

                //Remove consumed frame
                offScreenVideoFrames.removeFirst();

                //Remove frames until size is achieved
                if(offScreenVideoFrames.size() >= 60)
                {
                    bool alternate = false;
                    int index = 0;
                    while(offScreenVideoFrames.size() >= 60)
                    {
                        if(alternate == false)
                        {
                            index += 2;
                            if(index < offScreenVideoFrames.size())
                            {
                                offScreenVideoFrames.removeAt(index);
                                alternate = true;
                            }

                        }else if(alternate == true)
                        {
                            index += 3;
                            if(index < offScreenVideoFrames.size())
                            {
                                offScreenVideoFrames.removeAt(index);
                                alternate = false;
                            }
                        }

                        if(index >= offScreenVideoFrames.size()-1)
                        {
                            index = 0;
                        }
                    }
                }

            }*/

            this->fpsCounterOfDisplay();
            ogleContext->swapBuffers(this);
        }
    }
}


void OGLEWindow::screenVideoFrame(videoFrame* vFrame){ if(vFrame != nullptr){ onScreenVideoFrames.append(vFrame); }}
void OGLEWindow::offScreenVideoFrame(videoFrame* vFrame){ if(vFrame != nullptr){ offScreenVideoFrames.append(vFrame); }}


void OGLEWindow::cameraEmitting_unalteredCameraFrame(QVideoFrame vFrame){ cameraUnalteredVideoFrameBuffer = vFrame; }

void OGLEWindow::renderedSplitQualities(QVector<QColor> lqFrame){ splitLQFrame = lqFrame; }


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
