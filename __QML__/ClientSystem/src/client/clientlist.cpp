#include "clientlist.h"

#include "clientlist_p.h"


ClientList::ClientList(QObject *parent):
  QObject(parent)
{
  // By default, QQuickItem does not draw anything. If you subclass
  // QQuickItem to create a visual item, you will need to uncomment the
  // following line and re-implement updatePaintNode()

  // setFlag(ItemHasContents, true);

  p = new ClientList_P( this );
}

ClientList::~ClientList()
{
  while ( !p->m__Clients.isEmpty() )
  {
    Client *client = p->m__Clients.takeFirst();
    disconnect( client, SIGNAL(destroyed()), this, SLOT(clientDestroyed()) );
    delete client;
    client = NULL;
  }

  delete p;
  p = NULL;
}

int ClientList::count() const
{
  return p->m__Clients.count();
}

void ClientList::clear() const
{
  while ( !p->m__Clients.isEmpty() )
  {
    Client *client = p->m__Clients.takeFirst();
    disconnect( client, SIGNAL(destroyed()), this, SLOT(clientDestroyed()) );
    delete client;
    client = NULL;
  }
  emit countChanged();
}

Client * ClientList::client( int index ) const
{
  if ( index < 0 || index >= count() ) return NULL;

  return p->m__Clients[index];
}

int ClientList::clientIndex( Client *client ) const
{
  return p->m__Clients.indexOf( client );
}

Client * ClientList::addLink( Client *link ) const
{
  if ( p->m__Clients.contains( link ) ) return link;

  Client *newClient = new Client( p->p_dptr(), link );
  p->m__Clients << newClient;
  connect( newClient, SIGNAL(destroyed()), SLOT(clientDestroyed()) );
  emit clientAdded( newClient );
  emit countChanged();
  return newClient;
}

const QList<Client *> & ClientList::list() const
{
  return p->m__Clients;
}

QList<QObject *> ClientList::listAsQObjects() const
{
  QList<QObject *> res;
  foreach ( Client *item, p->m__Clients )
    res << item;
  return res;
}

Client * ClientList::find( QVariant identifier ) const
{
  foreach ( Client *client, p->m__Clients )
    if ( client->identifier() == identifier ) return client;

  return NULL;
}

void ClientList::receivedClientInfo( ClientInfo clientinfo ) const
{
  Client *newClient = find( clientinfo.identifier() );
  if ( newClient != NULL ) newClient->setClientInfo( clientinfo );
  else
  {
    newClient = new Client( p->p_dptr(), clientinfo );
    p->m__Clients << newClient;
    connect( newClient, SIGNAL(destroyed()), SLOT(clientDestroyed()) );
    emit clientAdded( newClient );
    emit countChanged();
  }
}

void ClientList::clientDestroyed()
{
  Client *client = qobject_cast<Client *>( sender() );
  int index = p->m__Clients.indexOf( client );
  p->m__Clients.removeAt( index );
  emit clientRemoved( index );
  emit countChanged();
}
