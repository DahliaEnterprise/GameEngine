#ifndef PREDICTIVEMOUSEPOSITION_H
#define PREDICTIVEMOUSEPOSITION_H

#include <QObject>

class predictiveMousePosition : public QObject
{
    Q_OBJECT
public:
    explicit predictiveMousePosition(QObject *parent = nullptr);
    void determineCorrection(int mouseX, int newMouseX);
    int getCorrectedX();

private:
    int correctedX;

signals:

public slots:
};

#endif // PREDICTIVEMOUSEPOSITION_H
