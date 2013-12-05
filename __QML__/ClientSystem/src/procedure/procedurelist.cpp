#include "procedurelist.h"

#include "procedurelist_p.h"


ProcedureList::ProcedureList(QObject *parent):
    QObject(parent)
{
    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    // setFlag(ItemHasContents, true);

    p = new ProcedureList_P( this );
}

ProcedureList::~ProcedureList()
{
    while ( !p->m__Procedures.isEmpty() )
    {
        Procedure *procedure = p->m__Procedures.takeFirst();
        disconnect( procedure, SIGNAL(destroyed()), this, SLOT(procedureDestroyed()) );
        delete procedure;
        procedure = NULL;
    }

    delete p;
    p = NULL;
}

int ProcedureList::count() const
{
    return p->m__Procedures.count();
}

void ProcedureList::clear() const
{
    while ( !p->m__Procedures.isEmpty() )
    {
        Procedure *procedure = p->m__Procedures.takeFirst();
        disconnect( procedure, SIGNAL(destroyed()), this, SLOT(procedureDestroyed()) );
        delete procedure;
        procedure = NULL;
    }
    emit countChanged();
}

Procedure * ProcedureList::procedure( int index ) const
{
    if ( index < 0 || index >= count() ) return NULL;

    return p->m__Procedures[index];
}

int ProcedureList::procedureIndex( Procedure *procedure ) const
{
    return p->m__Procedures.indexOf( procedure );
}

Procedure * ProcedureList::addLink( Procedure *link ) const
{
    if ( p->m__Procedures.contains( link ) ) return link;

    Procedure *newProcedure = new Procedure( p->p_dptr(), link );
    p->m__Procedures << newProcedure;
    connect( newProcedure, SIGNAL(destroyed()), SLOT(procedureDestroyed()) );
    emit procedureAdded( newProcedure );
    emit countChanged();
    return newProcedure;
}

Procedure * ProcedureList::find( QVariant identifier ) const
{
  foreach ( Procedure *procedure, p->m__Procedures )
    if ( procedure->identifier() == identifier ) return procedure;

  return NULL;
}

void ProcedureList::receivedProcedureInfo( ProcedureInfo procedureInfo ) const
{
    Procedure *newProcedure = new Procedure( p->p_dptr(), procedureInfo );
    p->m__Procedures << newProcedure;
    connect( newProcedure, SIGNAL(destroyed()), SLOT(procedureDestroyed()) );
    emit procedureAdded( newProcedure );
    emit countChanged();
}

void ProcedureList::procedureDestroyed()
{
    Procedure *procedure = qobject_cast<Procedure *>( sender() );
    int index = p->m__Procedures.indexOf( procedure );
    p->m__Procedures.removeAt( index );
    emit procedureRemoved( index );
    emit countChanged();
}
