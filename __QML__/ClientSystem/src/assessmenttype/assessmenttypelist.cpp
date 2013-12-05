#include "assessmenttypelist.h"

#include "assessmenttypelist_p.h"


AssessmenttypeList::AssessmenttypeList(QObject *parent):
  QObject(parent)
{
  // By default, QQuickItem does not draw anything. If you subclass
  // QQuickItem to create a visual item, you will need to uncomment the
  // following line and re-implement updatePaintNode()

  // setFlag(ItemHasContents, true);

  p = new AssessmenttypeList_P( this );
}

AssessmenttypeList::~AssessmenttypeList()
{
  while ( !p->m__Assessmenttypes.isEmpty() )
  {
    Assessmenttype *assessmenttype = p->m__Assessmenttypes.takeFirst();
    disconnect( assessmenttype, SIGNAL(destroyed()), this, SLOT(assessmenttypeDestroyed()) );
    delete assessmenttype;
    assessmenttype = NULL;
  }

  delete p;
  p = NULL;
}

int AssessmenttypeList::count() const
{
  return p->m__Assessmenttypes.count();
}

void AssessmenttypeList::clear() const
{
  while ( !p->m__Assessmenttypes.isEmpty() )
  {
    Assessmenttype *assessmenttype = p->m__Assessmenttypes.takeFirst();
    disconnect( assessmenttype, SIGNAL(destroyed()), this, SLOT(assessmenttypeDestroyed()) );
    delete assessmenttype;
    assessmenttype = NULL;
  }
  emit countChanged();
}

Assessmenttype * AssessmenttypeList::assessmenttype( int index ) const
{
  if ( index < 0 || index >= count() ) return NULL;

  return p->m__Assessmenttypes[index];
}

int AssessmenttypeList::assessmenttypeIndex( Assessmenttype *assessmenttype ) const
{
  return p->m__Assessmenttypes.indexOf( assessmenttype );
}

Assessmenttype * AssessmenttypeList::addLink( Assessmenttype *link ) const
{
  if ( p->m__Assessmenttypes.contains( link ) ) return link;

  Assessmenttype *newAssessmenttype = new Assessmenttype( p->p_dptr(), link );
  p->m__Assessmenttypes << newAssessmenttype;
  connect( newAssessmenttype, SIGNAL(destroyed()), SLOT(assessmenttypeDestroyed()) );
  emit assessmenttypeAdded( newAssessmenttype );
  emit countChanged();
  return newAssessmenttype;
}

Assessmenttype * AssessmenttypeList::find( QVariant identifier ) const
{
  foreach ( Assessmenttype *assessmenttype, p->m__Assessmenttypes )
    if ( assessmenttype->identifier() == identifier ) return assessmenttype;

  return NULL;
}

void AssessmenttypeList::receivedAssessmenttypeInfo( AssessmenttypeInfo assessmenttypeinfo ) const
{
  Assessmenttype *newAssessmenttype = new Assessmenttype( p->p_dptr(), assessmenttypeinfo );
  p->m__Assessmenttypes << newAssessmenttype;
  connect( newAssessmenttype, SIGNAL(destroyed()), SLOT(assessmenttypeDestroyed()) );
  emit assessmenttypeAdded( newAssessmenttype );
  emit countChanged();
}

void AssessmenttypeList::assessmenttypeDestroyed()
{
  Assessmenttype *assessmenttype = qobject_cast<Assessmenttype *>( sender() );
  int index = p->m__Assessmenttypes.indexOf( assessmenttype );
  p->m__Assessmenttypes.removeAt( index );
  emit assessmenttypeRemoved( index );
  emit countChanged();
}
