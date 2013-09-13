#ifndef CALLSTATUSINFO_H
#define CALLSTATUSINFO_H

#include <QtCore>


class CallstatusInfo
{
public:
    CallstatusInfo();
    CallstatusInfo( const CallstatusInfo &other );
    ~CallstatusInfo();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & name() const;
    void setName( const QString &name );


private:
    QVariant m__Identifier;
    QString m__Name;
};

#endif // CALLSTATUSINFO_H
