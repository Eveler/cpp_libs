#include "humanlist.h"

#include "humanlist_p.h"


HumanList::HumanList(QObject *parent):
    QObject(parent)
{
    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    // setFlag(ItemHasContents, true);

    p = new HumanList_P( this );
}

HumanList::~HumanList()
{
    while ( !p->m__Humans.isEmpty() )
    {
        Human *human = p->m__Humans.takeFirst();
        disconnect( human, SIGNAL(destroyed()), this, SLOT(humanDestroyed()) );
        delete human;
        human = NULL;
    }

    delete p;
    p = NULL;
}

int HumanList::count() const
{
    return p->m__Humans.count();
}

void HumanList::clear() const
{
    while ( !p->m__Humans.isEmpty() )
    {
        Human *human = p->m__Humans.takeFirst();
        disconnect( human, SIGNAL(destroyed()), this, SLOT(humanDestroyed()) );
        delete human;
        human = NULL;
    }
    emit countChanged();
}

Human * HumanList::human( int index ) const
{
    if ( index < 0 || index >= count() ) return NULL;

    return p->m__Humans[index];
}

int HumanList::humanIndex( Human *human ) const
{
    return p->m__Humans.indexOf( human );
}

Human * HumanList::addLink( Human *link ) const
{
    if ( p->m__Humans.contains( link ) ) return link;

    Human *newHuman = new Human( p->p_dptr(), link );
    p->m__Humans << newHuman;
    connect( newHuman, SIGNAL(destroyed()), SLOT(humanDestroyed()) );
    emit humanAdded( newHuman );
    emit countChanged();
    return newHuman;
}

void HumanList::receivedHumanInfo( HumanInfo humanInfo ) const
{
    Human *newHuman = new Human( p->p_dptr(), humanInfo );
    p->m__Humans << newHuman;
    connect( newHuman, SIGNAL(destroyed()), SLOT(humanDestroyed()) );
    emit humanAdded( newHuman );
    emit countChanged();
}

void HumanList::humanDestroyed()
{
    Human *human = qobject_cast<Human *>( sender() );
    int index = p->m__Humans.indexOf( human );
    p->m__Humans.removeAt( index );
    emit humanRemoved( index );
    emit countChanged();
}
