#include "trusteelist_p.h"


TrusteeList_P::TrusteeList_P( TrusteeList *parent ) :
  QObject(parent),
  m__Trustees(QList<Trustee *>())
{
}

TrusteeList_P::~TrusteeList_P()
{
}

TrusteeList * TrusteeList_P::p_dptr() const
{
  return qobject_cast<TrusteeList *>( parent() );
}

