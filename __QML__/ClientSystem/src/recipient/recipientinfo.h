#ifndef RECIPIENTINFO_H
#define RECIPIENTINFO_H

#include <QtCore>


class RecipientInfo
{
public:
    RecipientInfo();
    RecipientInfo( const RecipientInfo &other );
    ~RecipientInfo();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & name() const;
    void setName( const QString &name );


private:
    QVariant m__Identifier;
    QString m__Name;
};

#endif // RECIPIENTINFO_H
