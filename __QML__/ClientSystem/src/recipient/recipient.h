#ifndef RECIPIENT_H
#define RECIPIENT_H

#include <QObject>

#include "recipientinfo.h"

#include <QtQml>


class Recipient_P;
class RecipientList;

class Recipient : public QObject, public RecipientInfo
{
    Q_OBJECT
    Q_DISABLE_COPY(Recipient)
    friend class RecipientList;
    Q_PROPERTY(int index READ index NOTIFY indexChanged)
    Q_PROPERTY(QVariant identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)


public:
    Recipient( RecipientList *parent = 0 );
    Recipient( RecipientList *parent, const RecipientInfo &info );
    Recipient( RecipientList *parent, Recipient *link );
    ~Recipient();

    Q_INVOKABLE RecipientList * procedureList() const;

    int index() const;

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & name() const;
    void setName(  const QString &name );


signals:
    void indexChanged();
    void identifierChanged();
    void nameChanged();


public slots:


private:
    Recipient_P *p;
};

QML_DECLARE_TYPE(Recipient)

#endif // RECIPIENT_H
