#include "clientlist_p.h"


ClientList_P::ClientList_P( ClientList *parent ) :
  QObject(parent),
  m__Clients(QList<Client *>())
{
}

ClientList_P::~ClientList_P()
{
}

ClientList * ClientList_P::p_dptr() const
{
  return qobject_cast<ClientList *>( parent() );
}

