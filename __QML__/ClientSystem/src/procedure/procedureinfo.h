#ifndef PROCEDUREINFO_H
#define PROCEDUREINFO_H

#include <QtCore>


class ProcedureInfo
{
public:
    ProcedureInfo();
    ProcedureInfo( const ProcedureInfo &other );
    ~ProcedureInfo();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & name() const;
    void setName( const QString &name );


private:
    QVariant m__Identifier;
    QString m__Name;
};

#endif // PROCEDUREINFO_H
