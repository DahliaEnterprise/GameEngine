#include "videoframe.h"

videoFrame::videoFrame(QObject *parent) : QObject(parent)
{
    vfiList = new QVector<videoFrameInstruction*>();
    nextInstruction = 0;
}

void videoFrame::appendVideoFrameInstruction(videoFrameInstruction* vfi){ vfiList->append(vfi); }

QVector<videoFrameInstruction*>* videoFrame::videoFrameInstructionList(){ return vfiList; }

videoFrameInstruction* videoFrame::getNextInstruction()
{
    videoFrameInstruction* output = nullptr;

    if(nextInstruction < vfiList->size())
    {
        output = vfiList->at(nextInstruction);
        nextInstruction++;
    }

    return output;
}

bool videoFrame::hasNextInstruction()
{
    bool output = false;

    if(nextInstruction < vfiList->size())
    {
        output = true;
    }


    return output;
}
