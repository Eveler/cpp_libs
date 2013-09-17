#include "procedurelist_p.h"


ProcedureList_P::ProcedureList_P( ProcedureList *parent ) :
    QObject(parent),
    m__Procedures(QList<Procedure *>())
{
}

ProcedureList_P::~ProcedureList_P()
{
}

ProcedureList * ProcedureList_P::p_dptr() const
{
    return qobject_cast<ProcedureList *>( parent() );
}

