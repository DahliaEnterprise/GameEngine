#ifndef TENNIS_H
#define TENNIS_H

#include <QObject>
#include <QOpenGLPaintDevice>
#include "ExampleGames/tennis/tennis_script.h"
#include "OpenGLEngine/oglewindowmouseposition.h"
#include <QDebug>
#include <QVector>
#include "OpenGLEngine/ogleemblem.h"
class tennis : public QObject
{
    Q_OBJECT
public:
    explicit tennis(QObject *parent = nullptr);

    void start();
    QVector<ogleEmblem*> determine_frame();
    void updatedMousePosition(ogleWindowMousePosition* newMousePosition);

private:
    tennis_script* logic;

    //Shared
    ogleWindowMousePosition* mousePosition;

signals:

public slots:


private slots:

};

#endif // TENNIS_H
