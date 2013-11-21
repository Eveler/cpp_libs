#include "doctypelist_p.h"


DoctypeList_P::DoctypeList_P( DoctypeList *parent ) :
  QObject(parent),
  m__Doctypes(QList<Doctype *>())
{
}

DoctypeList_P::~DoctypeList_P()
{
}

DoctypeList * DoctypeList_P::p_dptr() const
{
  return qobject_cast<DoctypeList *>( parent() );
}

