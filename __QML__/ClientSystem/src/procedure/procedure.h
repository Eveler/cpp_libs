#ifndef PROCEDURE_H
#define PROCEDURE_H

#include <QObject>

#include "procedureinfo.h"

#include <QtQml>


class Procedure_P;
class ProcedureList;

class Procedure : public QObject, public ProcedureInfo
{
    Q_OBJECT
    Q_DISABLE_COPY(Procedure)
    friend class ProcedureList;
    Q_PROPERTY(int index READ index NOTIFY indexChanged)
    Q_PROPERTY(QVariant identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)


public:
    Procedure( ProcedureList *parent = 0 );
    Procedure( ProcedureList *parent, const ProcedureInfo &info );
    Procedure( ProcedureList *parent, Procedure *link );
    ~Procedure();

    Q_INVOKABLE ProcedureList * procedureList() const;

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
    Procedure_P *p;
};

QML_DECLARE_TYPE(Procedure)

#endif // PROCEDURE_H
