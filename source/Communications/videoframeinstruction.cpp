#include "videoframeinstruction.h"

videoFrameInstruction::videoFrameInstruction(QObject *parent) : QObject(parent)
{

}

void videoFrameInstruction::text(QString textToDisplay){ textString.clear(); textString.append(textToDisplay); }

QString videoFrameInstruction::getText(){ return textString; }

