#include "oglewindow.h"

OGLEWindow::OGLEWindow(QOpenGLWindow::UpdateBehavior updateBehavior, QOpenGLWindow *parent)
{
    //Initalize variables intended to begin nullptr or zero'ed.
    ogleContext = nullptr; oglePaintDevice = nullptr;

    //Configure
    this->setSurfaceType(QWindow::OpenGLSurface);format.setSamples(4);format.setVersion(4,0); format.setSwapBehavior(QSurfaceFormat::SingleBuffer);this->setFormat(format);this->create();this->setPosition(100,100); this->resize(1280,720);
    framesTimestamp = QDateTime::currentMSecsSinceEpoch(); frames = 0; framesPerSecond = 0;

}

OGLEWindow::~OGLEWindow(){}

void OGLEWindow::start(){this->setTitle(QString("Dahlias OpenGL Engine - Dogle"));OGLEMousePosition = new ogleWindowMousePosition();mouseUpdatedTimestamp=0;renderTimer = new QTimer();renderTimer->start(2);QObject::connect(renderTimer, SIGNAL(timeout()), this, SLOT(requestRenderUpdate()));}
void OGLEWindow::render(QPainter* painter){ Q_UNUSED(painter); }
void OGLEWindow::initialize(){}
void OGLEWindow::render(){}
bool OGLEWindow::event(QEvent* event){bool output = false; if(event->type() == QEvent::UpdateRequest){renderNow();output = true;}else{output = QWindow::event(event);} return output;}
void OGLEWindow::exposeEvent(QExposeEvent *event){ Q_UNUSED(event);this->renderNow(); }
void OGLEWindow::mouseMoveEvent(QMouseEvent * event){ if(mouseUpdatedTimestamp==0){mouseUpdatedTimestamp=QDateTime::currentMSecsSinceEpoch();} if((QDateTime::currentMSecsSinceEpoch() - mouseUpdatedTimestamp) > 15){mouseUpdatedTimestamp=QDateTime::currentMSecsSinceEpoch();mouseX=event->x();mouseY=event->y();} }
ogleWindowMousePosition* OGLEWindow::getMousePosition(){OGLEMousePosition->setMousePosition(mouseX,mouseY); return OGLEMousePosition;}

void OGLEWindow::nextFrame(QVector<ogleEmblem*> emblemListToNextFrame)
{
    frameAEmblems = emblemListToNextFrame;
}

void OGLEWindow::renderNow()
{
    this->fpsCounterOfDisplay();

    if(this->isExposed() == true)
    {

        ///(Initialize if nessecary and) Make context current
        bool initOGLF=false;if(ogleContext == nullptr){ogleContext=new QOpenGLContext(this);ogleContext->setFormat(format);ogleContext->create();initOGLF=true;}ogleContext->makeCurrent(this);if(initOGLF==true){initializeOpenGLFunctions();initialize();}this->initalizeOglePaintDevice();

        ///Draw to screen according to emblem specification
        QPainter painter(oglePaintDevice);
        painter.setRenderHint(QPainter::Antialiasing, false);
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        QVector<ogleEmblem*>::iterator emblemIterator = frameAEmblems.begin();
        while(emblemIterator != frameAEmblems.end())
        {
            //Determine drawing instructions assertained by emblem datatype
            ogleEmblem* emblem = *emblemIterator;
            if(ogleEmblem::EmblemType::TypeBox == emblem->getEmblemType())
            {
                ogleEmblemBox* box = emblem->getEmblemBox();
                int top = box->getCharacteristic(ogleEmblemBox::CharacteristicTop).toInt();
                int left = box->getCharacteristic(ogleEmblemBox::CharacteristicLeft).toInt();
                int width = box->getCharacteristic(ogleEmblemBox::CharacteristicWidth).toInt();
                int height = box->getCharacteristic(ogleEmblemBox::CharacteristicHeight).toInt();
                QColor fill = box->getFillColor();
                painter.fillRect(QRect(left,top,width,height),fill);

                //
                if(box->prerenderedAvailable() == true)
                {

                    //painter.drawImage(QRect(left,top,width,height), box->getPrerendered());
                    //box->getPrerendered();
                }else if(box->prerenderedAvailable() == false){
                    QImage boxImage = QImage(width,height, QImage::Format_ARGB32);
                    QPainter boxImagePainter(&boxImage);

                    boxImagePainter.fillRect(QRect(left,top,width,height),fill);
                    box->incomingPrerender(boxImage);
                }
            }

            //Next emblem
            emblemIterator++;
        }
        //calling (base-class) render after drawing here
        //render(&painter);
        ogleContext->swapBuffers(this);
        emit frameRenderFinished();
    }
}


void OGLEWindow::fpsCounterOfDisplay(){frames++; qint64 sinceLastFrame = QDateTime::currentMSecsSinceEpoch() - framesTimestamp; if(sinceLastFrame > 1000){qWarning() << frames;framesTimestamp = QDateTime::currentMSecsSinceEpoch();frames = 0;}}
void OGLEWindow::requestRenderUpdate(){this->requestUpdate();}
void OGLEWindow::initalizeOglePaintDevice(){if(oglePaintDevice == nullptr){oglePaintDevice = new QOpenGLPaintDevice();}glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);oglePaintDevice->setSize(size() * devicePixelRatio());oglePaintDevice->setDevicePixelRatio(devicePixelRatio());}
