#include "declarclientlist_p.h"


DeclarClientList_P::DeclarClientList_P( DeclarClientList *parent ) :
  QObject(parent),
  m__DeclarClients(QList<DeclarClient *>())
{
}

DeclarClientList_P::~DeclarClientList_P()
{
}

DeclarClientList * DeclarClientList_P::p_dptr() const
{
  return qobject_cast<DeclarClientList *>( parent() );
}

