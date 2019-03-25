#include "module_card_hightlightable.h"

module_card_hightlightable::module_card_hightlightable(QObject *parent) : QObject(parent)
{

}

void module_card_hightlightable::start(keyboardMouseInput* setkeyboardmouse_input){ keyboardmouse_input = setkeyboardmouse_input; }

void module_card_hightlightable::highlightable(card_creature* card)
{
    //Check if mouse is hovering over card.
    QMap<QString, double> dimensions = card->gameObject()->dimensions();
    double x = dimensions.value(QString("x"));
    double y = dimensions.value(QString("y"));
    double width = dimensions.value(QString("w"));
    double height = dimensions.value(QString("h"));

    double mouseX = keyboardmouse_input->getMouseX();
    double mouseY = keyboardmouse_input->getMouseY();
    bool highlighted = false;
    qWarning() << mouseY << " " << y;
    if(mouseX >= x && mouseX <= (x + width))
    {
        if(mouseY >= y && mouseY < (y + height)){
            highlighted = true;
        }
    }
    card->highlighted(highlighted);
}

void module_card_hightlightable::highlightable(card_moduspraecptum* card)
{

}
