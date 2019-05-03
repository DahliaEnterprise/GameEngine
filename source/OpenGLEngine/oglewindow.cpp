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
    cameraController = new ogleCameraController();
    cameraController->start();

    if(framesUpdateKeepAlive == nullptr){ framesUpdateKeepAlive = new QTimer(); QObject::connect(framesUpdateKeepAlive, SIGNAL(timeout()), this, SLOT(updateFrame())); framesUpdateKeepAlive->start(5); }
    QObject::connect(cameraController, SIGNAL(unalteredCameraFrame(QVideoFrame)), this, SLOT(cameraEmitting_unalteredCameraFrame(QVideoFrame)));
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
            painter.setCompositionMode(QPainter::CompositionMode_Source);

            /** Offscreen work **/
            //TODO: Crunch offscreen work, return back to sender

            /** Onscreen work **/
            if(onScreenVideoFrames.isEmpty() == false)
            {   //Video Frame Instructions Available
                videoFrame* vFrame = onScreenVideoFrames.at(0);
                while(vFrame->hasNextInstruction() == true)
                {
                    videoFrameInstruction* vfi = vFrame->getNextInstruction();
                    if(vfi->instructionType() == videoFrameInstruction::UnalteredCameraVideoFrame)
                    {
                        //Deep Copy, Incoming Camera Unaltered Video Frame
                        cameraUnalteredVideoFrameBuffer.map(QAbstractVideoBuffer::ReadOnly);
                        QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(cameraUnalteredVideoFrameBuffer.pixelFormat());
                        QImage VideoFrameAsImage = QImage(cameraUnalteredVideoFrameBuffer.bits(), cameraUnalteredVideoFrameBuffer.width(), cameraUnalteredVideoFrameBuffer.height(), cameraUnalteredVideoFrameBuffer.bytesPerLine(), imageFormat);
                        painter.drawImage(QRect(0,0,1280,720), VideoFrameAsImage);
                    }
                }

                //Remove consumed frame
                onScreenVideoFrames.removeFirst();

                //Remove frames until size is achieved
                if(onScreenVideoFrames.size() > 60)
                {
                    bool odd = false;
                    while(onScreenVideoFrames.size() > 60)
                    {
                        if(odd == false)
                        {
                            onScreenVideoFrames.removeAt(2);
                            odd = true;
                        }else if(odd == true)
                        {
                            onScreenVideoFrames.removeAt(5);
                        }
                    }
                }

                qWarning() << onScreenVideoFrames.size();
            }




            /*
            videoFrame* vFrame = bufferedOnScreenVideoFrameInstructions;
            if(vFrame != nullptr)
            {

                /*while(vFrame->hasNextInstruction() == true)
                {
                    //Get next instruction
                    //videoFrameInstruction* vfi = vFrame->getNextInstruction();

                    //Assume camera image is to be displayed
                    //QVideoFrame shallow = cameraUnalteredVideoFrameBuffer;
                    //shallow.map(QAbstractVideoBuffer::ReadOnly);
                    //QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(cameraUnalteredVideoFrameBuffer.pixelFormat());
                    //QImage VideoFrameAsImage = QImage(cameraUnalteredVideoFrameBuffer.bits(), cameraUnalteredVideoFrameBuffer.width(), cameraUnalteredVideoFrameBuffer.height(), cameraUnalteredVideoFrameBuffer.bytesPerLine(), imageFormat);
                    //painter.drawImage(QRect(0,0,1280,720), VideoFrameAsImage);
                }*/

                /*
                QVector<videoFrameInstruction*>* vfiList = vFrame->videoFrameInstructionList();
                if(vfiList != nullptr)
                {

                    for(int i = 0; i < vfiList->size(); i++)
                    {

                        videoFrameInstruction* vfi = *vfiListIterator;
                        if(vfi->instructionType() == 0)
                        {
                            QPen pen;
                            QRandomGenerator random;

                            pen.setColor(QColor(QString::number(random.bounded(255)).toInt(),QString::number(random.bounded(255)).toInt(),QString::number(random.bounded(255)).toInt(),100));
                            pen.setWidth(1);
                            painter.setPen(pen);
                            painter.setFont(QFont(QString("Arial"), 15, 1, false));

                            videoFrameInstruction* vfi = vfiList.at(0);
                            painter.drawText(QPointF(0,100), vfi->getText());

                        }else if(vfi->instructionType() == 1){
                            /*
                            //Draw camera video frame
                            if(unalteredCameraVideoStream_fpsManagement.isEmpty() == true){ unalteredCameraVideoStream_fpsManagement.insert(vfi->unalteredCameraVideo_getFpsMonitorId(), QDateTime::currentMSecsSinceEpoch()); }else{ if(unalteredCameraVideoStream_fpsManagement.contains(vfi->unalteredCameraVideo_getFpsMonitorId()) == false){ unalteredCameraVideoStream_fpsManagement.insert(vfi->unalteredCameraVideo_getFpsMonitorId(), QDateTime::currentMSecsSinceEpoch()); }else{ qint64 timestampLastframeProduced = unalteredCameraVideoStream_fpsManagement.value(vfi->unalteredCameraVideo_getFpsMonitorId()); qint64 timesinceLastframeProduced = QDateTime::currentMSecsSinceEpoch() - timestampLastframeProduced; qint64 msBetweenFrames = 1000 / vfi->unalteredCameraVideo_getMaxFps(); if(timesinceLastframeProduced >= msBetweenFrames){ if(unalteredCameraVideoStream_sustainedFrame.isEmpty() == true){ QVideoFrame shallow = cameraUnalteredVideoFrameBuffer;  unalteredCameraVideoStream_sustainedFrame.insert(vfi->unalteredCameraVideo_getFpsMonitorId(), shallow); }else{ if(unalteredCameraVideoStream_sustainedFrame.contains(vfi->unalteredCameraVideo_getFpsMonitorId()) == false){ QVideoFrame shallow = cameraUnalteredVideoFrameBuffer; unalteredCameraVideoStream_sustainedFrame.insert(vfi->unalteredCameraVideo_getFpsMonitorId(), shallow); }else{ unalteredCameraVideoStream_sustainedFrame.remove(vfi->unalteredCameraVideo_getFpsMonitorId()); QVideoFrame shallow = cameraUnalteredVideoFrameBuffer; unalteredCameraVideoStream_sustainedFrame.insert(vfi->unalteredCameraVideo_getFpsMonitorId(), shallow); } } unalteredCameraVideoStream_fpsManagement.remove(vfi->unalteredCameraVideo_getFpsMonitorId()); unalteredCameraVideoStream_fpsManagement.insert(vfi->unalteredCameraVideo_getFpsMonitorId(), QDateTime::currentMSecsSinceEpoch()); }
                                QVideoFrame unalteredVideoFrame = unalteredCameraVideoStream_sustainedFrame.value(vfi->unalteredCameraVideo_getFpsMonitorId());
                                unalteredVideoFrame.map(QAbstractVideoBuffer::ReadOnly);
                                QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(unalteredVideoFrame.pixelFormat());
                                QImage VideoFrameAsImage = QImage(unalteredVideoFrame.bits(), unalteredVideoFrame.width(), unalteredVideoFrame.height(), unalteredVideoFrame.bytesPerLine(), imageFormat);
                                painter.drawImage(QRect(0,0,1280,720), VideoFrameAsImage);
                            }c
                            }

                        }

                    }

                }*/
                //vfiList.clear();
            //}
            //render(&painter);

            frames++;
            qint64 sinceLastFrame = QDateTime::currentMSecsSinceEpoch() - framesTimestamp;
            if(sinceLastFrame > 1000)
            {
                //qWarning() << frames;
                framesTimestamp = QDateTime::currentMSecsSinceEpoch();
                frames = 0;
            }
            ogleContext->swapBuffers(this);
        }
    }
}


void OGLEWindow::screenVideoFrame(videoFrame* vFrame)
{
    if(vFrame != nullptr)
    {
        //bufferedOnScreenVideoFrameInstructions = vFrame;
        onScreenVideoFrames.append(vFrame);
    }
}

void OGLEWindow::cameraEmitting_unalteredCameraFrame(QVideoFrame vFrame){ cameraUnalteredVideoFrameBuffer = vFrame; }

