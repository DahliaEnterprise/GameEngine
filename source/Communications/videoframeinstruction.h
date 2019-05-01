#ifndef VIDEOFRAMEINSTRUCTION_H
#define VIDEOFRAMEINSTRUCTION_H

#include <QObject>

class videoFrameInstruction : public QObject
{
    Q_OBJECT
public:
    explicit videoFrameInstruction(QObject *parent = nullptr);

    void text(QString textToDisplay);
    QString getText();

private:
    QString textString;

signals:

public slots:
};

#endif // VIDEOFRAMEINSTRUCTION_H
