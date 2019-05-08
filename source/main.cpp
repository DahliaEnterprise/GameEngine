#include <QApplication>
#include <QThread>

#include "OpenGLEngine/oglemastercontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

     //deprecated:qRegisterMetaType<QVector<QColor>>();

    ogleMasterController* ogle = new ogleMasterController();
    ogle->start();

    return a.exec();
}
