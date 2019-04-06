#include "module_card_clickable.h"

module_card_clickable::module_card_clickable(QObject *parent) : QObject(parent)
{

}


void module_card_clickable::start(keyboardMouseInput* setkeyboardmouse_input){ keyboardmouse_input = setkeyboardmouse_input; }


bool module_card_clickable::mouseClickedCardArea(QMap<QString, double> dimensions)
{
    bool output = false;

    //Check if mouse is hovering over card.
    double x = dimensions.value(QString("x"));
    double y = dimensions.value(QString("y"));
    double width = dimensions.value(QString("w"));
    double height = dimensions.value(QString("h"));

    double mouseX = keyboardmouse_input->getMouseX();
    double mouseY = keyboardmouse_input->getMouseY();
    bool mouseOverCardArea = false;
    if(mouseX >= x && mouseX <= (x + width)){ if(mouseY >= y && mouseY < (y + height)){ mouseOverCardArea = true; } }
    if(mouseOverCardArea == true){ if(keyboardmouse_input->getLeftMouseDown() == true){ output = true; } }


    return output;
}
