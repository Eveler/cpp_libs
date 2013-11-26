#include "resultlist.h"

#include "resultlist_p.h"


ResultList::ResultList(QObject *parent):
  QObject(parent)
{
  // By default, QQuickItem does not draw anything. If you subclass
  // QQuickItem to create a visual item, you will need to uncomment the
  // following line and re-implement updatePaintNode()

  // setFlag(ItemHasContents, true);

  p = new ResultList_P( this );
}

ResultList::~ResultList()
{
  while ( !p->m__Results.isEmpty() )
  {
    Result *result = p->m__Results.takeFirst();
    disconnect( result, SIGNAL(destroyed()), this, SLOT(resultDestroyed()) );
    delete result;
    result = NULL;
  }

  delete p;
  p = NULL;
}

int ResultList::count() const
{
  return p->m__Results.count();
}

void ResultList::clear() const
{
  while ( !p->m__Results.isEmpty() )
  {
    Result *result = p->m__Results.takeFirst();
    disconnect( result, SIGNAL(destroyed()), this, SLOT(resultDestroyed()) );
    delete result;
    result = NULL;
  }
  emit countChanged();
}

Result * ResultList::result( int index ) const
{
  if ( index < 0 || index >= count() ) return NULL;

  return p->m__Results[index];
}

int ResultList::resultIndex( Result *result ) const
{
  return p->m__Results.indexOf( result );
}

Result * ResultList::addLink( Result *link ) const
{
  if ( p->m__Results.contains( link ) ) return link;

  Result *newResult = new Result( p->p_dptr(), link );
  p->m__Results << newResult;
  connect( newResult, SIGNAL(destroyed()), SLOT(resultDestroyed()) );
  emit resultAdded( newResult );
  emit countChanged();
  return newResult;
}

void ResultList::receivedResultInfo( ResultInfo resultinfo ) const
{
  Result *newResult = new Result( p->p_dptr(), resultinfo );
  p->m__Results << newResult;
  connect( newResult, SIGNAL(destroyed()), SLOT(resultDestroyed()) );
  emit resultAdded( newResult );
  emit countChanged();
}

void ResultList::resultDestroyed()
{
  Result *result = qobject_cast<Result *>( sender() );
  int index = p->m__Results.indexOf( result );
  p->m__Results.removeAt( index );
  emit resultRemoved( index );
  emit countChanged();
}
