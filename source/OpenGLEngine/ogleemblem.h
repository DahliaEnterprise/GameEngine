#ifndef OGLEEMBLEM_H
#define OGLEEMBLEM_H

#include <QObject>
#include "OpenGLEngine/ogleemblem/ogleemblembox.h"
class ogleEmblem : public QObject
{
    Q_OBJECT
public:
    explicit ogleEmblem(QObject *parent = nullptr);
    enum EmblemType{TypeBox};
    void determine_frame();

    void start(ogleEmblemBox* setBox);
    ogleEmblemBox* getEmblemBox();

    ogleEmblem::EmblemType getEmblemType();

private:
    EmblemType emblemDatatype;
    ogleEmblemBox* box;

signals:

public slots:
};

#endif // OGLEEMBLEM_H
