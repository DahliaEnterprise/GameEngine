#include "card_moduspraecptum.h"

card_moduspraecptum::card_moduspraecptum(QObject *parent) : QObject(parent)
{

}

void card_moduspraecptum::start(QString imageUrl, QStringList setModuspraecptum_list)
{
    //Copy
    QStringList::const_iterator iterator = setModuspraecptum_list.constBegin(); while(iterator != setModuspraecptum_list.constEnd()){ QString moduspraeceptum = *iterator; moduspraecptum_list.append(moduspraeceptum); iterator++; }

    //Process Modus Praecptum List
    this->process_moduspraecptum();

    //Initalize
    moduspraecptumCardSourceImage = QImage(imageUrl);
    moduspraecptumCardImage = QImage(792, 612, QImage::Format_ARGB32);

    //Draw card image
    QPainter painter(&moduspraecptumCardImage); painter.setRenderHint(QPainter::HighQualityAntialiasing); painter.setOpacity(1);
    painter.drawImage(QRectF(0,0,792,612), moduspraecptumCardSourceImage);
    QPen red; red.setColor(QColor(Qt::white)); red.setStyle(Qt::SolidLine); red.setWidth(30); painter.setPen(red);

    int fontId = QFontDatabase::addApplicationFont(QString(":/examplegame/quickgame/fonts/Herey Script Free Version.ttf"));
    QString hereyScriptFreeVersion = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font = painter.font();
    font.setPixelSize(40);
    font.setFamily(QString("Arial"));
    painter.setFont(font);
    painter.drawText(QPointF(30, 150), QString("100 Tired Points"));

    //Attach image resource to game object
    moduspraecptumGO = new gameobject();
    moduspraecptumGO->start(moduspraecptumCardImage);

    //Produce a highlighted image of a card
    moduspraecptumCardHighlightedImage = QImage(792, 612, QImage::Format_ARGB32);
    QPainter painter2(&moduspraecptumCardHighlightedImage); painter2.setRenderHint(QPainter::HighQualityAntialiasing);
    painter2.drawImage(QRect(0,0,792,612), moduspraecptumCardSourceImage);
    QPen green; green.setColor(QColor(Qt::green)); green.setStyle(Qt::SolidLine); green.setWidth(30); painter2.setPen(green);
    painter2.drawRoundedRect(QRectF(0,0,792,612), 20, 20, Qt::AbsoluteSize);
}

gameobject* card_moduspraecptum::gameObject(){ return moduspraecptumGO; }

void card_moduspraecptum::updateImageSpecification(double x, double y, double width, double height, double opacity){ moduspraecptumGO->updateImageSpecifications(x,y,width,height,opacity); }

void card_moduspraecptum::process_moduspraecptum()
{
    QStringList::const_iterator iterator = moduspraecptum_list.constBegin();
    while(iterator != moduspraecptum_list.constEnd())
    {
        QString moduspraecptum_command = *iterator;

        //Is tired points?
        if(moduspraecptum_command.mid(0, 1).compare(QString("t")) == 0)
        {
            if(moduspraecptum_command.mid(0, 12).compare(QString("tired points")) == 0)
            {
                points_tired = moduspraecptum_command.mid(13, -1).toInt();
            }
        }
        iterator++;
    }
}

QStringList card_moduspraecptum::card_actions(){ return moduspraecptum_list; }
