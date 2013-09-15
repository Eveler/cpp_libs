#include "recipientlist.h"

#include "recipientlist_p.h"


RecipientList::RecipientList(QObject *parent):
    QObject(parent)
{
    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    // setFlag(ItemHasContents, true);

    p = new RecipientList_P( this );
}

RecipientList::~RecipientList()
{
    while ( !p->m__Recipients.isEmpty() )
    {
        Recipient *recipient = p->m__Recipients.takeFirst();
        disconnect( recipient, SIGNAL(destroyed()), this, SLOT(recipientDestroyed()) );
        delete recipient;
        recipient = NULL;
    }

    delete p;
    p = NULL;
}

int RecipientList::count() const
{
    return p->m__Recipients.count();
}

void RecipientList::clear() const
{
    while ( !p->m__Recipients.isEmpty() )
    {
        Recipient *recipient = p->m__Recipients.takeFirst();
        disconnect( recipient, SIGNAL(destroyed()), this, SLOT(recipientDestroyed()) );
        delete recipient;
        recipient = NULL;
    }
    emit countChanged();
}

Recipient * RecipientList::recipient( int index ) const
{
    if ( index < 0 || index >= count() ) return NULL;

    return p->m__Recipients[index];
}

int RecipientList::recipientIndex( Recipient *recipient ) const
{
    return p->m__Recipients.indexOf( recipient );
}

Recipient * RecipientList::addLink( Recipient *link ) const
{
    if ( p->m__Recipients.contains( link ) ) return link;

    Recipient *newRecipient = new Recipient( p->p_dptr(), link );
    p->m__Recipients << newRecipient;
    connect( newRecipient, SIGNAL(destroyed()), SLOT(recipientDestroyed()) );
    emit recipientAdded( newRecipient );
    emit countChanged();
    return newRecipient;
}

void RecipientList::receivedRecipientInfo( RecipientInfo recipientInfo ) const
{
    Recipient *newRecipient = new Recipient( p->p_dptr(), recipientInfo );
    p->m__Recipients << newRecipient;
    connect( newRecipient, SIGNAL(destroyed()), SLOT(recipientDestroyed()) );
    emit recipientAdded( newRecipient );
    emit countChanged();
}

void RecipientList::recipientDestroyed()
{
    Recipient *recipient = qobject_cast<Recipient *>( sender() );
    int index = p->m__Recipients.indexOf( recipient );
    p->m__Recipients.removeAt( index );
    emit recipientRemoved( index );
    emit countChanged();
}
