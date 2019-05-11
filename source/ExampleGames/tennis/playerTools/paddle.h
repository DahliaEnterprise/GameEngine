#ifndef PADDLE_H
#define PADDLE_H

#include <QObject>

class paddle : public QObject
{
    Q_OBJECT
public:
    explicit paddle(QObject *parent = nullptr);

signals:

public slots:
};

#endif // PADDLE_H