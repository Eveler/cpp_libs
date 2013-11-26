#ifndef ASSESSMENTTYPELIST_P_H
#define ASSESSMENTTYPELIST_P_H

#include <QObject>

#include "assessmenttypelist.h"
#include "assessmenttype.h"


class AssessmenttypeList_P : public QObject
{
    Q_OBJECT
    friend class AssessmenttypeList;


  public:


  signals:


  public slots:


  private:
    QList<Assessmenttype *> m__Assessmenttypes;

    explicit AssessmenttypeList_P( AssessmenttypeList *parent );
    ~AssessmenttypeList_P();

    AssessmenttypeList * p_dptr() const;
};

#endif // ASSESSMENTTYPELIST_P_H
