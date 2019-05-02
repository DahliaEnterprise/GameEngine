#include "videoframeinstruction.h"

videoFrameInstruction::videoFrameInstruction(QObject *parent) : QObject(parent){}

int videoFrameInstruction::instructionType(){ return instructionDataType; }

//
void videoFrameInstruction::text(QString textToDisplay){ instructionDataType = VideoInstructionDataType::Text; textString.clear(); textString.append(textToDisplay); }
QString videoFrameInstruction::getText(){ return textString; }


//
void videoFrameInstruction::unalteredCameraVideo(int setFpsMonitorId, int setMaxFps, double setX, double setY, double setWidth, double setHeight){ instructionDataType = VideoInstructionDataType::UnalteredCameraVideoFrame; fpsMonitorId=setFpsMonitorId;maxFps=setMaxFps;x=setX;y=setY;width=setWidth;height=setHeight; }
int videoFrameInstruction::unalteredCameraVideo_getMaxFps(){ return maxFps; }
int videoFrameInstruction::unalteredCameraVideo_getFpsMonitorId(){ return fpsMonitorId; }
