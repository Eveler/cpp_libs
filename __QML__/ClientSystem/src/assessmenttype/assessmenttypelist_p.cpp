#include "assessmenttypelist_p.h"


AssessmenttypeList_P::AssessmenttypeList_P( AssessmenttypeList *parent ) :
  QObject(parent),
  m__Assessmenttypes(QList<Assessmenttype *>())
{
}

AssessmenttypeList_P::~AssessmenttypeList_P()
{
}

AssessmenttypeList * AssessmenttypeList_P::p_dptr() const
{
  return qobject_cast<AssessmenttypeList *>( parent() );
}

