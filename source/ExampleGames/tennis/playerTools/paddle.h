#ifndef PADDLE_H
#define PADDLE_H

#include <QObject>
#include <QDebug>
class paddle : public QObject
{
    Q_OBJECT
public:
    explicit paddle(QObject *parent = nullptr);
    void start(int screenWidth, int screenHeight);
    void determine_frame();

private:

signals:

public slots:
};

#endif // PADDLE_H
