#ifndef RECIPIENTLIST_H
#define RECIPIENTLIST_H

#include <QObject>

#include "recipientinfo.h"

#include <QtQml>


class RecipientList_P;
class RecipientLoader;
class Recipient;

class RecipientList : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(RecipientList)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    friend class RecipientLoader;


public:
    RecipientList(QObject *parent = 0);
    ~RecipientList();

    int count() const;
    Q_INVOKABLE void clear() const;

    Q_INVOKABLE Recipient * recipient( int index ) const;
    Q_INVOKABLE int recipientIndex( Recipient *recipient ) const;
    Q_INVOKABLE Recipient * addLink( Recipient *link ) const;


signals:
    void countChanged() const;
    void recipientAdded( Recipient *recipient ) const;
    void recipientRemoved( int index ) const;


private:
    RecipientList_P *p;


private slots:
    void receivedRecipientInfo( RecipientInfo recipientInfo ) const;
    void recipientDestroyed();
};

QML_DECLARE_TYPE(RecipientList)

#endif // RECIPIENTLIST_H
