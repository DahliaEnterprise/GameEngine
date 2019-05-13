#ifndef PREDICTIVEMOUSEPOSITION_H
#define PREDICTIVEMOUSEPOSITION_H

#include <QObject>

class predictiveMousePosition : public QObject
{
    Q_OBJECT
public:
    explicit predictiveMousePosition(QObject *parent = nullptr);
    void determineCorrection(int mouseX, int newMouseX, int mouseY, int newMouseY);
    int getCorrectedX();
    int getCorrectedY();

private:
    int correctedX;
    int correctedY;

signals:

public slots:
};

#endif // PREDICTIVEMOUSEPOSITION_H
