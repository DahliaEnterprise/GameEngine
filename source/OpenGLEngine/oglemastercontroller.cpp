#include "oglemastercontroller.h"

ogleMasterController::ogleMasterController(QObject *parent) : QObject(parent)
{

}

void ogleMasterController::start()
{
    ///Visual Controller
    communicationsControlThread = new QThread();
    communicationsControl = new CommunicationsController();
    communicationsControl->moveToThread(communicationsControlThread);
    communicationsControlThread->start();
    communicationsControl->start();

    ///Display
    window = new OGLEWindow();
    window->defineCommunicationsController(communicationsControl);
    window->resize(QSize(1280, 720));
    window->show();

    //signals slots
    QObject::connect(communicationsControl, SIGNAL(videoFrameInstructions(QList<videoFrameInstruction*>)),
                     window,
                SLOT(videoFrameInstructions(QList<videoFrameInstruction*>)));
}
