#ifndef TENNIS_H
#define TENNIS_H

#include <QObject>

class tennis : public QObject
{
    Q_OBJECT
public:
    explicit tennis(QObject *parent = nullptr);

signals:

public slots:
};

#endif // TENNIS_H