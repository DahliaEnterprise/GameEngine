#include <QApplication>
#include <QThread>
#include "ExampleGames/tennis/tennis.h"
#include "OpenGLEngine/oglemastercontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

     //deprecated:qRegisterMetaType<QVector<QColor>>();


    ogleMasterController* ogle = new ogleMasterController();
    tennis* t = new tennis();
    t->setOpenGLMasterController(ogle);
    t->start();
    ogle->start();

    return a.exec();
}
