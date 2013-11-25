#include "resultwaylist_p.h"


ResultwayList_P::ResultwayList_P( ResultwayList *parent ) :
  QObject(parent),
  m__Resultways(QList<Resultway *>())
{
}

ResultwayList_P::~ResultwayList_P()
{
}

ResultwayList * ResultwayList_P::p_dptr() const
{
  return qobject_cast<ResultwayList *>( parent() );
}

