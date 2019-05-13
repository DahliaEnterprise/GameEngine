#ifndef OGLEEMBLEMBOX_H
#define OGLEEMBLEMBOX_H

#include <QObject>
#include <QColor>
#include <QVariant>
class ogleEmblemBox : public QObject
{
    Q_OBJECT
public:
    explicit ogleEmblemBox(QObject *parent = nullptr);
    enum characteristic{CharacteristicBorder,CharacteristicFill,CharacteristicTop,CharacteristicLeft,CharacteristicWidth,CharacteristicHeight};
    void defineEveryCharacteristic(QColor setborder, QColor setfill, int settop, int setleft, int setwidth, int setheight);
    void selectiveCharacteristicUpdate(characteristic property, QVariant value);
    QVariant getCharacteristic(characteristic property);
    QColor getBorderColor();
    QColor getFillColor();

private:
    QColor border;
    QColor fill;
    int top;
    int left;
    int width;
    int height;

signals:

public slots:
};

#endif // OGLEEMBLEMBOX_H
