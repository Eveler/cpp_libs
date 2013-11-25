#include "assessmentlist_p.h"


AssessmentList_P::AssessmentList_P( AssessmentList *parent ) :
  QObject(parent),
  m__Assessments(QList<Assessment *>())
{
}

AssessmentList_P::~AssessmentList_P()
{
}

AssessmentList * AssessmentList_P::p_dptr() const
{
  return qobject_cast<AssessmentList *>( parent() );
}

