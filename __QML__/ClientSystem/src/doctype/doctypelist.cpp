#include "doctypelist.h"

#include "doctypelist_p.h"


DoctypeList::DoctypeList(QObject *parent):
    QObject(parent)
{
    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    // setFlag(ItemHasContents, true);

    p = new DoctypeList_P( this );
}

DoctypeList::~DoctypeList()
{
    while ( !p->m__Doctypes.isEmpty() )
    {
        Doctype *doctype = p->m__Doctypes.takeFirst();
        disconnect( doctype, SIGNAL(destroyed()), this, SLOT(doctypeDestroyed()) );
        delete doctype;
        doctype = NULL;
    }

    delete p;
    p = NULL;
}

int DoctypeList::count() const
{
    return p->m__Doctypes.count();
}

void DoctypeList::clear() const
{
    while ( !p->m__Doctypes.isEmpty() )
    {
        Doctype *doctype = p->m__Doctypes.takeFirst();
        disconnect( doctype, SIGNAL(destroyed()), this, SLOT(doctypeDestroyed()) );
        delete doctype;
        doctype = NULL;
    }
    emit countChanged();
}

Doctype * DoctypeList::doctype( int index ) const
{
    if ( index < 0 || index >= count() ) return NULL;

    return p->m__Doctypes[index];
}

int DoctypeList::doctypeIndex( Doctype *doctype ) const
{
    return p->m__Doctypes.indexOf( doctype );
}

Doctype * DoctypeList::addLink( Doctype *link ) const
{
    if ( p->m__Doctypes.contains( link ) ) return link;

    Doctype *newDoctype = new Doctype( p->p_dptr(), link );
    p->m__Doctypes << newDoctype;
    connect( newDoctype, SIGNAL(destroyed()), SLOT(doctypeDestroyed()) );
    emit doctypeAdded( newDoctype );
    emit countChanged();
    return newDoctype;
}

void DoctypeList::receivedDoctypeInfo( DoctypeInfo doctypeInfo ) const
{
    Doctype *newDoctype = new Doctype( p->p_dptr(), doctypeInfo );
    p->m__Doctypes << newDoctype;
    connect( newDoctype, SIGNAL(destroyed()), SLOT(doctypeDestroyed()) );
    emit doctypeAdded( newDoctype );
    emit countChanged();
}

void DoctypeList::doctypeDestroyed()
{
    Doctype *doctype = qobject_cast<Doctype *>( sender() );
    int index = p->m__Doctypes.indexOf( doctype );
    p->m__Doctypes.removeAt( index );
    emit doctypeRemoved( index );
    emit countChanged();
}
