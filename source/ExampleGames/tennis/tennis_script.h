#ifndef TENNIS_SCRIPT_H
#define TENNIS_SCRIPT_H

#include <QObject>
#include <QTimer>
#include "OpenGLEngine/ogleemblem.h"
#include "ExampleGames/tennis/playerTools/paddle.h"
#include "OpenGLEngine/oglewindowmouseposition.h"
#include "ExampleGames/tennis/aiTools/aipaddle.h"
#include "ExampleGames/tennis/token.h"
class tennis_script : public QObject
{
    Q_OBJECT
public:
    explicit tennis_script(QObject *parent = nullptr);
    void start();
    QVector<ogleEmblem*> determine_frame();
    void updatedMousePosition(ogleWindowMousePosition* newMousePosition);

private:
    QTimer* scriptKeepalive;

    paddle* playerOnePaddle;
    aiPaddle* playerAiPaddle;
    token* ball;

signals:

public slots:
    void cycleLogic();

};

#endif // TENNIS_SCRIPT_H
