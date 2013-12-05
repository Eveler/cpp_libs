#include "trusteelist.h"

#include "trusteelist_p.h"


TrusteeList::TrusteeList(QObject *parent):
  QObject(parent)
{
  // By default, QQuickItem does not draw anything. If you subclass
  // QQuickItem to create a visual item, you will need to uncomment the
  // following line and re-implement updatePaintNode()

  // setFlag(ItemHasContents, true);

  p = new TrusteeList_P( this );
}

TrusteeList::~TrusteeList()
{
  while ( !p->m__Trustees.isEmpty() )
  {
    Trustee *trustee = p->m__Trustees.takeFirst();
    disconnect( trustee, SIGNAL(destroyed()), this, SLOT(trusteeDestroyed()) );
    delete trustee;
    trustee = NULL;
  }

  delete p;
  p = NULL;
}

int TrusteeList::count() const
{
  return p->m__Trustees.count();
}

void TrusteeList::clear() const
{
  while ( !p->m__Trustees.isEmpty() )
  {
    Trustee *trustee = p->m__Trustees.takeFirst();
    disconnect( trustee, SIGNAL(destroyed()), this, SLOT(trusteeDestroyed()) );
    delete trustee;
    trustee = NULL;
  }
  emit countChanged();
}

Trustee * TrusteeList::trustee( int index ) const
{
  if ( index < 0 || index >= count() ) return NULL;

  return p->m__Trustees[index];
}

int TrusteeList::trusteeIndex( Trustee *trustee ) const
{
  return p->m__Trustees.indexOf( trustee );
}

Trustee * TrusteeList::addLink( Trustee *link ) const
{
  if ( p->m__Trustees.contains( link ) ) return link;

  Trustee *newTrustee = new Trustee( p->p_dptr(), link );
  p->m__Trustees << newTrustee;
  connect( newTrustee, SIGNAL(destroyed()), SLOT(trusteeDestroyed()) );
  emit trusteeAdded( newTrustee );
  emit countChanged();
  return newTrustee;
}

Trustee * TrusteeList::find( QVariant identifier ) const
{
  foreach ( Trustee *trustee, p->m__Trustees )
    if ( trustee->identifier() == identifier ) return trustee;

  return NULL;
}

void TrusteeList::receivedTrusteeInfo( TrusteeInfo trusteeinfo ) const
{
  Trustee *newTrustee = new Trustee( p->p_dptr(), trusteeinfo );
  p->m__Trustees << newTrustee;
  connect( newTrustee, SIGNAL(destroyed()), SLOT(trusteeDestroyed()) );
  emit trusteeAdded( newTrustee );
  emit countChanged();
}

void TrusteeList::trusteeDestroyed()
{
  Trustee *trustee = qobject_cast<Trustee *>( sender() );
  int index = p->m__Trustees.indexOf( trustee );
  p->m__Trustees.removeAt( index );
  emit trusteeRemoved( index );
  emit countChanged();
}
