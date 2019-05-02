#ifndef VIDEOFRAME_H
#define VIDEOFRAME_H

#include <QObject>
#include "Communications/videoframeinstruction.h"
#include <QVector>
class videoFrame : public QObject
{
    Q_OBJECT
public:
    explicit videoFrame(QObject *parent = nullptr);
    void appendVideoFrameInstruction(videoFrameInstruction* vfi);
    QVector<videoFrameInstruction*> videoFrameInstructionList();

private:
    QVector<videoFrameInstruction*> vfiList;

signals:

public slots:
};

#endif // VIDEOFRAME_H
