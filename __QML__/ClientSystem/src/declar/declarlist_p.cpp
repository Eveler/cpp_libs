#include "declarlist_p.h"


DeclarList_P::DeclarList_P( DeclarList *parent ) :
  QObject(parent),
  m__Declars(QList<Declar *>())
{
}

DeclarList_P::~DeclarList_P()
{
}

DeclarList * DeclarList_P::p_dptr() const
{
  return qobject_cast<DeclarList *>( parent() );
}

