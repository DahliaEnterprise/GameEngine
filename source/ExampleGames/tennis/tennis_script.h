#ifndef TENNIS_SCRIPT_H
#define TENNIS_SCRIPT_H

#include <QObject>
#include <QTimer>
#include "OpenGLEngine/ogleemblem.h"
#include "ExampleGames/tennis/playerTools/paddle.h"
class tennis_script : public QObject
{
    Q_OBJECT
public:
    explicit tennis_script(QObject *parent = nullptr);
    void start();
    void determine_frame();

private:
    QTimer* scriptKeepalive;

    bool objectsInitialized;

    ogleEmblem* playerOneEmblem;
    paddle* playerOnePaddle;


signals:

public slots:
    void wakeupScript();
    void cycleLogic();

};

#endif // TENNIS_SCRIPT_H
