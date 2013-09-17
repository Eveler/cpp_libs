#ifndef RECIPIENTLIST_P_H
#define RECIPIENTLIST_P_H

#include <QObject>

#include "recipientlist.h"
#include "recipient.h"


class RecipientList_P : public QObject
{
    Q_OBJECT
    friend class RecipientList;


public:


signals:


public slots:


private:
    QList<Recipient *> m__Recipients;

    explicit RecipientList_P( RecipientList *parent );
    ~RecipientList_P();

    RecipientList * p_dptr() const;
};

#endif // RECIPIENTLIST_P_H
