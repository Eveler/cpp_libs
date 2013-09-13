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
    while ( !p->m__Callstatuss.isEmpty() )
    {
        Callstatus *callstatus = p->m__Callstatuss.takeFirst();
        disconnect( callstatus, SIGNAL(destroyed()), this, SLOT(callstatusDestroyed()) );
        delete callstatus;
        callstatus = NULL;
    }

    delete p;
    p = NULL;
}

int CallstatusList::count() const
{
    return p->m__Callstatuss.count();
}

void CallstatusList::clear() const
{
    while ( !p->m__Callstatuss.isEmpty() )
    {
        Callstatus *callstatus = p->m__Callstatuss.takeFirst();
        disconnect( callstatus, SIGNAL(destroyed()), this, SLOT(callstatusDestroyed()) );
        delete callstatus;
        callstatus = NULL;
    }
    emit countChanged();
}

Callstatus * CallstatusList::callstatus( int index ) const
{
    if ( index < 0 || index >= count() ) return NULL;

    return p->m__Callstatuss[index];
}

int CallstatusList::callstatusIndex( Callstatus *callstatus ) const
{
    return p->m__Callstatuss.indexOf( callstatus );
}

Callstatus * CallstatusList::addLink( Callstatus *link ) const
{
    Callstatus *newCallstatus = new Callstatus( p->p_dptr(), link );
    p->m__Callstatuss << newCallstatus;
    connect( newCallstatus, SIGNAL(destroyed()), SLOT(callstatusDestroyed()) );
    emit callstatusAdded( newCallstatus );
    emit countChanged();
    return newCallstatus;
}

void CallstatusList::receivedCallstatusInfo( CallstatusInfo callstatusInfo ) const
{
    Callstatus *newCallstatus = new Callstatus( p->p_dptr(), callstatusInfo );
    p->m__Callstatuss << newCallstatus;
    connect( newCallstatus, SIGNAL(destroyed()), SLOT(callstatusDestroyed()) );
    emit callstatusAdded( newCallstatus );
    emit countChanged();
}

void CallstatusList::callstatusDestroyed()
{
    Callstatus *callstatus = qobject_cast<Callstatus *>( sender() );
    int index = p->m__Callstatuss.indexOf( callstatus );
    p->m__Callstatuss.removeAt( index );
    emit callstatusRemoved( index );
    emit countChanged();
}
