#ifndef ASSESSMENTLIST_P_H
#define ASSESSMENTLIST_P_H

#include <QObject>

#include "assessmentlist.h"
#include "assessment.h"


class AssessmentList_P : public QObject
{
    Q_OBJECT
    friend class AssessmentList;


  public:


  signals:


  public slots:


  private:
    QList<Assessment *> m__Assessments;

    explicit AssessmentList_P( AssessmentList *parent );
    ~AssessmentList_P();

    AssessmentList * p_dptr() const;
};

#endif // ASSESSMENTLIST_P_H
