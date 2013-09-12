#ifndef PROCEDURELIST_P_H
#define PROCEDURELIST_P_H

#include <QObject>

#include "procedurelist.h"
#include "procedure.h"


class ProcedureList_P : public QObject
{
    Q_OBJECT
    friend class ProcedureList;


public:


signals:


public slots:


private:
    QList<Procedure *> m__Procedures;

    explicit ProcedureList_P( ProcedureList *parent );
    ~ProcedureList_P();

    ProcedureList * p_dptr() const;
};

#endif // PROCEDURELIST_P_H
