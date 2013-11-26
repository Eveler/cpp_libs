#include "resultwaylist.h"

#include "resultwaylist_p.h"


ResultwayList::ResultwayList(QObject *parent):
  QObject(parent)
{
  // By default, QQuickItem does not draw anything. If you subclass
  // QQuickItem to create a visual item, you will need to uncomment the
  // following line and re-implement updatePaintNode()

  // setFlag(ItemHasContents, true);

  p = new ResultwayList_P( this );
}

ResultwayList::~ResultwayList()
{
  while ( !p->m__Resultways.isEmpty() )
  {
    Resultway *resultway = p->m__Resultways.takeFirst();
    disconnect( resultway, SIGNAL(destroyed()), this, SLOT(resultwayDestroyed()) );
    delete resultway;
    resultway = NULL;
  }

  delete p;
  p = NULL;
}

int ResultwayList::count() const
{
  return p->m__Resultways.count();
}

void ResultwayList::clear() const
{
  while ( !p->m__Resultways.isEmpty() )
  {
    Resultway *resultway = p->m__Resultways.takeFirst();
    disconnect( resultway, SIGNAL(destroyed()), this, SLOT(resultwayDestroyed()) );
    delete resultway;
    resultway = NULL;
  }
  emit countChanged();
}

Resultway * ResultwayList::resultway( int index ) const
{
  if ( index < 0 || index >= count() ) return NULL;

  return p->m__Resultways[index];
}

int ResultwayList::resultwayIndex( Resultway *resultway ) const
{
  return p->m__Resultways.indexOf( resultway );
}

Resultway * ResultwayList::addLink( Resultway *link ) const
{
  if ( p->m__Resultways.contains( link ) ) return link;

  Resultway *newResultway = new Resultway( p->p_dptr(), link );
  p->m__Resultways << newResultway;
  connect( newResultway, SIGNAL(destroyed()), SLOT(resultwayDestroyed()) );
  emit resultwayAdded( newResultway );
  emit countChanged();
  return newResultway;
}

void ResultwayList::receivedResultwayInfo( ResultwayInfo resultwayinfo ) const
{
  Resultway *newResultway = new Resultway( p->p_dptr(), resultwayinfo );
  p->m__Resultways << newResultway;
  connect( newResultway, SIGNAL(destroyed()), SLOT(resultwayDestroyed()) );
  emit resultwayAdded( newResultway );
  emit countChanged();
}

void ResultwayList::resultwayDestroyed()
{
  Resultway *resultway = qobject_cast<Resultway *>( sender() );
  int index = p->m__Resultways.indexOf( resultway );
  p->m__Resultways.removeAt( index );
  emit resultwayRemoved( index );
  emit countChanged();
}
