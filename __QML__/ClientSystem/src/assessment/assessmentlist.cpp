#include "assessmentlist.h"

#include "assessmentlist_p.h"


AssessmentList::AssessmentList(QObject *parent):
  QObject(parent)
{
  // By default, QQuickItem does not draw anything. If you subclass
  // QQuickItem to create a visual item, you will need to uncomment the
  // following line and re-implement updatePaintNode()

  // setFlag(ItemHasContents, true);

  p = new AssessmentList_P( this );
}

AssessmentList::~AssessmentList()
{
  while ( !p->m__Assessments.isEmpty() )
  {
    Assessment *assessment = p->m__Assessments.takeFirst();
    disconnect( assessment, SIGNAL(destroyed()), this, SLOT(assessmentDestroyed()) );
    delete assessment;
    assessment = NULL;
  }

  delete p;
  p = NULL;
}

int AssessmentList::count() const
{
  return p->m__Assessments.count();
}

void AssessmentList::clear() const
{
  while ( !p->m__Assessments.isEmpty() )
  {
    Assessment *assessment = p->m__Assessments.takeFirst();
    disconnect( assessment, SIGNAL(destroyed()), this, SLOT(assessmentDestroyed()) );
    delete assessment;
    assessment = NULL;
  }
  emit countChanged();
}

Assessment * AssessmentList::assessment( int index ) const
{
  if ( index < 0 || index >= count() ) return NULL;

  return p->m__Assessments[index];
}

int AssessmentList::assessmentIndex( Assessment *assessment ) const
{
  return p->m__Assessments.indexOf( assessment );
}

Assessment * AssessmentList::addLink( Assessment *link ) const
{
  if ( p->m__Assessments.contains( link ) ) return link;

  Assessment *newAssessment = new Assessment( p->p_dptr(), link );
  p->m__Assessments << newAssessment;
  connect( newAssessment, SIGNAL(destroyed()), SLOT(assessmentDestroyed()) );
  emit assessmentAdded( newAssessment );
  emit countChanged();
  return newAssessment;
}

Assessment * AssessmentList::find( QVariant identifier ) const
{
  foreach ( Assessment *assessment, p->m__Assessments )
    if ( assessment->identifier() == identifier ) return assessment;

  return NULL;
}

void AssessmentList::receivedAssessmentInfo( AssessmentInfo assessmentinfo ) const
{
  Assessment *newAssessment = new Assessment( p->p_dptr(), assessmentinfo );
  p->m__Assessments << newAssessment;
  connect( newAssessment, SIGNAL(destroyed()), SLOT(assessmentDestroyed()) );
  emit assessmentAdded( newAssessment );
  emit countChanged();
}

void AssessmentList::assessmentDestroyed()
{
  Assessment *assessment = qobject_cast<Assessment *>( sender() );
  int index = p->m__Assessments.indexOf( assessment );
  p->m__Assessments.removeAt( index );
  emit assessmentRemoved( index );
  emit countChanged();
}
