#include "declarclientlist.h"

#include "declarclientlist_p.h"


DeclarClientList::DeclarClientList(QObject *parent):
  QObject(parent)
{
  // By default, QQuickItem does not draw anything. If you subclass
  // QQuickItem to create a visual item, you will need to uncomment the
  // following line and re-implement updatePaintNode()

  // setFlag(ItemHasContents, true);

  p = new DeclarClientList_P( this );
}

DeclarClientList::~DeclarClientList()
{
  while ( !p->m__DeclarClients.isEmpty() )
  {
    DeclarClient *declarclient = p->m__DeclarClients.takeFirst();
    disconnect( declarclient, SIGNAL(destroyed()), this, SLOT(declarclientDestroyed()) );
    delete declarclient;
    declarclient = NULL;
  }

  delete p;
  p = NULL;
}

int DeclarClientList::count() const
{
  return p->m__DeclarClients.count();
}

void DeclarClientList::clear() const
{
  while ( !p->m__DeclarClients.isEmpty() )
  {
    DeclarClient *declarclient = p->m__DeclarClients.takeFirst();
    disconnect( declarclient, SIGNAL(destroyed()), this, SLOT(declarclientDestroyed()) );
    delete declarclient;
    declarclient = NULL;
  }
  emit countChanged();
}

DeclarClient * DeclarClientList::declarclient( int index ) const
{
  if ( index < 0 || index >= count() ) return NULL;

  return p->m__DeclarClients[index];
}

int DeclarClientList::declarclientIndex( DeclarClient *declarclient ) const
{
  return p->m__DeclarClients.indexOf( declarclient );
}

DeclarClient * DeclarClientList::addLink( DeclarClient *link ) const
{
  if ( p->m__DeclarClients.contains( link ) ) return link;

  DeclarClient *newDeclarClient = new DeclarClient( p->p_dptr(), link );
  p->m__DeclarClients << newDeclarClient;
  connect( newDeclarClient, SIGNAL(destroyed()), SLOT(declarclientDestroyed()) );
  emit declarclientAdded( newDeclarClient );
  emit countChanged();
  return newDeclarClient;
}

DeclarClient * DeclarClientList::find( QVariant identifier ) const
{
  foreach ( DeclarClient *seclarClient, p->m__DeclarClients )
    if ( seclarClient->identifier() == identifier ) return seclarClient;

  return NULL;
}

void DeclarClientList::receivedDeclarClientInfo( DeclarClientInfo declarclientinfo ) const
{
  DeclarClient *newDeclarClient = new DeclarClient( p->p_dptr(), declarclientinfo );
  p->m__DeclarClients << newDeclarClient;
  connect( newDeclarClient, SIGNAL(destroyed()), SLOT(declarclientDestroyed()) );
  emit declarclientAdded( newDeclarClient );
  emit countChanged();
}

void DeclarClientList::declarclientDestroyed()
{
  DeclarClient *declarclient = qobject_cast<DeclarClient *>( sender() );
  int index = p->m__DeclarClients.indexOf( declarclient );
  p->m__DeclarClients.removeAt( index );
  emit declarclientRemoved( index );
  emit countChanged();
}
