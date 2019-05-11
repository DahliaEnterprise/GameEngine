#ifndef OGLEEMBLEM_H
#define OGLEEMBLEM_H

#include <QObject>

class ogleEmblem : public QObject
{
    Q_OBJECT
public:
    explicit ogleEmblem(QObject *parent = nullptr);
    void determine_frame();

signals:

public slots:
};

#endif // OGLEEMBLEM_H
