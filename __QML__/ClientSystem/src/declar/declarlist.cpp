#include "declarlist.h"

#include "declarlist_p.h"


DeclarList::DeclarList(QObject *parent):
  QObject(parent)
{
  // By default, QQuickItem does not draw anything. If you subclass
  // QQuickItem to create a visual item, you will need to uncomment the
  // following line and re-implement updatePaintNode()

  // setFlag(ItemHasContents, true);

  p = new DeclarList_P( this );
}

DeclarList::~DeclarList()
{
  while ( !p->m__Declars.isEmpty() )
  {
    Declar *declar = p->m__Declars.takeFirst();
    disconnect( declar, SIGNAL(destroyed()), this, SLOT(declarDestroyed()) );
    delete declar;
    declar = NULL;
  }

  delete p;
  p = NULL;
}

int DeclarList::count() const
{
  return p->m__Declars.count();
}

void DeclarList::clear() const
{
  while ( !p->m__Declars.isEmpty() )
  {
    Declar *declar = p->m__Declars.takeFirst();
    disconnect( declar, SIGNAL(destroyed()), this, SLOT(declarDestroyed()) );
    delete declar;
    declar = NULL;
  }
  emit countChanged();
}

Declar * DeclarList::declar( int index ) const
{
  if ( index < 0 || index >= count() ) return NULL;

  return p->m__Declars[index];
}

int DeclarList::declarIndex( Declar *declar ) const
{
  return p->m__Declars.indexOf( declar );
}

Declar * DeclarList::addLink( Declar *link ) const
{
  if ( p->m__Declars.contains( link ) ) return link;

  Declar *newDeclar = new Declar( p->p_dptr(), link );
  p->m__Declars << newDeclar;
  connect( newDeclar, SIGNAL(destroyed()), SLOT(declarDestroyed()) );
  emit declarAdded( newDeclar );
  emit countChanged();
  return newDeclar;
}

Declar * DeclarList::find( QVariant identifier ) const
{
  foreach ( Declar *declar, p->m__Declars )
    if ( declar->identifier() == identifier ) return declar;

  return NULL;
}

void DeclarList::receivedDeclarInfo( DeclarInfo declarinfo ) const
{
  Declar *newDeclar = new Declar( p->p_dptr(), declarinfo );
  p->m__Declars << newDeclar;
  connect( newDeclar, SIGNAL(destroyed()), SLOT(declarDestroyed()) );
  emit declarAdded( newDeclar );
  emit countChanged();
}

void DeclarList::declarDestroyed()
{
  Declar *declar = qobject_cast<Declar *>( sender() );
  int index = p->m__Declars.indexOf( declar );
  p->m__Declars.removeAt( index );
  emit declarRemoved( index );
  emit countChanged();
}
