#ifndef HEAD_H
#define HEAD_H

#include <QObject>
#include "gameengine.h"
#include "gameengine/opengl.h"
#include <QThread>
#include <QTimer>
class head : public QObject
{
    Q_OBJECT
public:
    explicit head(QObject *parent = nullptr);
    void start();

private:
    gameloop* game;
    gameengine* engine;
    QTimer* frameTimer;

signals:

public slots:

private slots:
    void frameTimeout();
};

#endif // HEAD_H
