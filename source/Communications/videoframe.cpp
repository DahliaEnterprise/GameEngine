#include "videoframe.h"

videoFrame::videoFrame(QObject *parent) : QObject(parent)
{

}

void videoFrame::appendVideoFrameInstruction(videoFrameInstruction* vfi){ vfiList.append(vfi); }

QVector<videoFrameInstruction*> videoFrame::videoFrameInstructionList(){ return vfiList; }
