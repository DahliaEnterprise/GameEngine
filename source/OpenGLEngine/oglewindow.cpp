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
    this->resize(1280,720);
    timestamp = QDateTime::currentMSecsSinceEpoch();
    frames = 0;
    framesPerSecond = 0;
    renderingEnabled = true;
    timestampLastOnScreenFrameProduced = 0;
}

OGLEWindow::~OGLEWindow(){}

void OGLEWindow::start()
{
    cameraController = new ogleCameraController();
    cameraController->start();
    QObject::connect(cameraController, SIGNAL(unalteredCameraFrame(QVideoFrame)), this, SLOT(unalteredCameraFrame(QVideoFrame)));
}

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

void OGLEWindow::updateFrame(){ requestUpdate(); }

void OGLEWindow::renderNow()
{
    if(this->isExposed() == true)
    {
        if(framesUpdateKeepAlive == nullptr)
        {
            framesUpdateKeepAlive = new QTimer();
            QObject::connect(framesUpdateKeepAlive, SIGNAL(timeout()), this, SLOT(updateFrame()));
            framesUpdateKeepAlive->start(1);
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
            painter.setRenderHint(QPainter::Antialiasing, true);
            painter.setCompositionMode(QPainter::CompositionMode_Source);

            /** Offscreen work **/
            //TODO: Crunch offscreen work, return back to sender

            /** Onscreen work **/
            if(bufferedOnScreenFrames.isEmpty() == false)
            {
                videoFrame* vFrame = bufferedOnScreenFrames.first();
                if(vFrame != nullptr)
                {
                    QVector<videoFrameInstruction*> vfiList = vFrame->videoFrameInstructionList();
                    if(vfiList.isEmpty() == false)
                    {

                        QVector<videoFrameInstruction*>::const_iterator vfiListIterator = vfiList.constBegin();
                        while(vfiListIterator != vfiList.constEnd())
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
                            }else if(vfi->instructionType() == 1)
                            {
                                //Draw camera video frame
                                if(unalteredCameraVideoStream_fpsManagement.isEmpty() == true){ unalteredCameraVideoStream_fpsManagement.insert(vfi->unalteredCameraVideo_getFpsMonitorId(), QDateTime::currentMSecsSinceEpoch()); }else{ if(unalteredCameraVideoStream_fpsManagement.contains(vfi->unalteredCameraVideo_getFpsMonitorId()) == false){ unalteredCameraVideoStream_fpsManagement.insert(vfi->unalteredCameraVideo_getFpsMonitorId(), QDateTime::currentMSecsSinceEpoch()); }else{ qint64 timestampLastframeProduced = unalteredCameraVideoStream_fpsManagement.value(vfi->unalteredCameraVideo_getFpsMonitorId()); qint64 timesinceLastframeProduced = QDateTime::currentMSecsSinceEpoch() - timestampLastframeProduced; qint64 msBetweenFrames = 1000 / vfi->unalteredCameraVideo_getMaxFps(); if(timesinceLastframeProduced >= msBetweenFrames){ if(unalteredCameraVideoStream_sustainedFrame.isEmpty() == true){ QVideoFrame shallow = cameraUnalteredVideoFrameBuffer;  unalteredCameraVideoStream_sustainedFrame.insert(vfi->unalteredCameraVideo_getFpsMonitorId(), shallow); }else{ if(unalteredCameraVideoStream_sustainedFrame.contains(vfi->unalteredCameraVideo_getFpsMonitorId()) == false){ QVideoFrame shallow = cameraUnalteredVideoFrameBuffer; unalteredCameraVideoStream_sustainedFrame.insert(vfi->unalteredCameraVideo_getFpsMonitorId(), shallow); }else{ unalteredCameraVideoStream_sustainedFrame.remove(vfi->unalteredCameraVideo_getFpsMonitorId()); QVideoFrame shallow = cameraUnalteredVideoFrameBuffer; unalteredCameraVideoStream_sustainedFrame.insert(vfi->unalteredCameraVideo_getFpsMonitorId(), shallow); } } unalteredCameraVideoStream_fpsManagement.remove(vfi->unalteredCameraVideo_getFpsMonitorId()); unalteredCameraVideoStream_fpsManagement.insert(vfi->unalteredCameraVideo_getFpsMonitorId(), QDateTime::currentMSecsSinceEpoch()); }
                                    QVideoFrame unalteredVideoFrame = unalteredCameraVideoStream_sustainedFrame.value(vfi->unalteredCameraVideo_getFpsMonitorId());
                                    unalteredVideoFrame.map(QAbstractVideoBuffer::ReadOnly);
                                    QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(unalteredVideoFrame.pixelFormat());
                                    QImage VideoFrameAsImage = QImage(unalteredVideoFrame.bits(), unalteredVideoFrame.width(), unalteredVideoFrame.height(), unalteredVideoFrame.bytesPerLine(), imageFormat);
                                    painter.drawImage(QRect(0,0,1280,720), VideoFrameAsImage);
                                }
                                }
                            }

                            vfiListIterator++;
                        }
                    }

                    qWarning() << " size:" << bufferedOnScreenFrames.size();

                    //Drop frames?
                    qint64 sinceLastOnScreenFrameProduced = QDateTime::currentMSecsSinceEpoch() - timestampLastOnScreenFrameProduced;
                    if(sinceLastOnScreenFrameProduced > 5)
                    {
                        if(bufferedOnScreenFrames.size() >= 60)
                        {
                            for(int i = 0; i < bufferedOnScreenFrames.size(); i++)
                            {
                                bufferedOnScreenFrames.removeLast();
                            }


                            timestampLastOnScreenFrameProduced = QDateTime::currentMSecsSinceEpoch();
                        }
                    }
                }

                //Remove used video frame
                if(bufferedOnScreenFrames.isEmpty() == false){ bufferedOnScreenFrames.removeFirst(); }

            }

            //render(&painter);

            frames++;
            qint64 sinceLastFrame = QDateTime::currentMSecsSinceEpoch() - timestamp;
            if(sinceLastFrame > 1000)
            {
                //qWarning() << frames;
                timestamp = QDateTime::currentMSecsSinceEpoch();
                frames = 0;
            }
            ogleContext->swapBuffers(this);
        }
    }
}


void OGLEWindow::screenVideoFrame(videoFrame* vFrame){ if(vFrame != nullptr){ bufferedOnScreenFrames.append(vFrame); } }

void OGLEWindow::unalteredCameraFrame(QVideoFrame vFrame){ cameraUnalteredVideoFrameBuffer = vFrame;  }

