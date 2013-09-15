#include "callstatuslist.h"

#include "callstatuslist_p.h"


CallstatusList::CallstatusList(QObject *parent):
    QObject(parent)
{
    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    // setFlag(ItemHasContents, true);

    p = new CallstatusList_P( this );
}

CallstatusList::~CallstatusList()
{
    while ( !p->m__Callstatuses.isEmpty() )
    {
        Callstatus *callstatus = p->m__Callstatuses.takeFirst();
        disconnect( callstatus, SIGNAL(destroyed()), this, SLOT(callstatusDestroyed()) );
        delete callstatus;
        callstatus = NULL;
    }

    delete p;
    p = NULL;
}

int CallstatusList::count() const
{
    return p->m__Callstatuses.count();
}

void CallstatusList::clear() const
{
    while ( !p->m__Callstatuses.isEmpty() )
    {
        Callstatus *callstatus = p->m__Callstatuses.takeFirst();
        disconnect( callstatus, SIGNAL(destroyed()), this, SLOT(callstatusDestroyed()) );
        delete callstatus;
        callstatus = NULL;
    }
    emit countChanged();
}

Callstatus * CallstatusList::callstatus( int index ) const
{
    if ( index < 0 || index >= count() ) return NULL;

    return p->m__Callstatuses[index];
}

int CallstatusList::callstatusIndex( Callstatus *callstatus ) const
{
    return p->m__Callstatuses.indexOf( callstatus );
}

Callstatus * CallstatusList::addLink( Callstatus *link ) const
{
    if ( p->m__Callstatuses.contains( link ) ) return link;

    Callstatus *newCallstatus = new Callstatus( p->p_dptr(), link );
    p->m__Callstatuses << newCallstatus;
    connect( newCallstatus, SIGNAL(destroyed()), SLOT(callstatusDestroyed()) );
    emit callstatusAdded( newCallstatus );
    emit countChanged();
    return newCallstatus;
}

Callstatus * CallstatusList::find( QVariant identifier ) const
{
    foreach (Callstatus *callstatus, p->m__Callstatuses)
        if ( callstatus->identifier() == identifier ) return callstatus;

    return NULL;
}

void CallstatusList::addCallstatus( CallstatusInfo callstatusInfo ) const
{
    Callstatus *newCallstatus = new Callstatus( p->p_dptr(), callstatusInfo );
    p->m__Callstatuses << newCallstatus;
    connect( newCallstatus, SIGNAL(destroyed()), SLOT(callstatusDestroyed()) );
    emit callstatusAdded( newCallstatus );
    emit countChanged();
}

void CallstatusList::editCallstatus( CallstatusInfo callstatusInfo ) const
{
    Callstatus *newCallstatus = find( callstatusInfo.identifier() );
    if ( newCallstatus != NULL )
    {
        newCallstatus->setName( callstatusInfo.name() );
        return;
    }

    newCallstatus = new Callstatus( p->p_dptr(), callstatusInfo );
    p->m__Callstatuses << newCallstatus;
    connect( newCallstatus, SIGNAL(destroyed()), SLOT(callstatusDestroyed()) );
    emit callstatusAdded( newCallstatus );
    emit countChanged();
}

void CallstatusList::callstatusDestroyed()
{
    Callstatus *callstatus = qobject_cast<Callstatus *>( sender() );
    int index = p->m__Callstatuses.indexOf( callstatus );
    p->m__Callstatuses.removeAt( index );
    emit callstatusRemoved( index );
    emit countChanged();
}
