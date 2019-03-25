#ifndef CARD_TURNACTIVATEDCARD_H
#define CARD_TURNACTIVATEDCARD_H

#include <QObject>

class card_turnactivatedcard : public QObject
{
    Q_OBJECT
public:
    explicit card_turnactivatedcard(QObject *parent = nullptr);
    void start(QString imageUrl, QStringList turnactivatedcard_list);


signals:

public slots:
};

#endif // CARD_TURNACTIVATEDCARD_H
