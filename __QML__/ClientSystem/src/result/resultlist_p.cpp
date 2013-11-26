#include "resultlist_p.h"


ResultList_P::ResultList_P( ResultList *parent ) :
  QObject(parent),
  m__Results(QList<Result *>())
{
}

ResultList_P::~ResultList_P()
{
}

ResultList * ResultList_P::p_dptr() const
{
  return qobject_cast<ResultList *>( parent() );
}

