#include "communication_graphics_and_processing.h"

communication_graphics_and_processing::communication_graphics_and_processing(QObject *parent) : QObject(parent)
{

}

void communication_graphics_and_processing::start()
{
    //no particular order
    //Initailize networking
    net = new network();

    //Initailize frame to display


    //Initialize webcam stream


}
