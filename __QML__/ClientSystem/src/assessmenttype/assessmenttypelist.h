#ifndef ASSESSMENTTYPELIST_H
#define ASSESSMENTTYPELIST_H

#include <QObject>

#include "assessmenttypeinfo.h"

#include <QtQml>


class AssessmenttypeList_P;
class AssessmenttypeLoader;
class Assessmenttype;

class AssessmenttypeList : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AssessmenttypeList)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    friend class AssessmenttypeLoader;


  public:
    AssessmenttypeList(QObject *parent = 0);
    ~AssessmenttypeList();

    int count() const;
    Q_INVOKABLE void clear() const;

    Q_INVOKABLE Assessmenttype * assessmenttype( int index ) const;
    Q_INVOKABLE int assessmenttypeIndex( Assessmenttype *assessmenttype ) const;
    Q_INVOKABLE Assessmenttype * addLink( Assessmenttype *link ) const;


  signals:
    void countChanged() const;
    void assessmenttypeAdded( Assessmenttype *assessmenttype ) const;
    void assessmenttypeRemoved( int index ) const;


  private:
    AssessmenttypeList_P *p;


  private slots:
    void receivedAssessmenttypeInfo( AssessmenttypeInfo assessmenttypeinfo ) const;
    void assessmenttypeDestroyed();
};

QML_DECLARE_TYPE(AssessmenttypeList)

#endif // ASSESSMENTTYPELIST_H
