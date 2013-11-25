#ifndef ASSESSMENTLIST_H
#define ASSESSMENTLIST_H

#include <QObject>

#include "assessmentinfo.h"

#include <QtQml>


class AssessmentList_P;
class AssessmentLoader;
class Assessment;

class AssessmentList : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AssessmentList)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    friend class AssessmentLoader;


  public:
    AssessmentList(QObject *parent = 0);
    ~AssessmentList();

    int count() const;
    Q_INVOKABLE void clear() const;

    Q_INVOKABLE Assessment * assessment( int index ) const;
    Q_INVOKABLE int assessmentIndex( Assessment *assessment ) const;
    Q_INVOKABLE Assessment * addLink( Assessment *link ) const;


  signals:
    void countChanged() const;
    void assessmentAdded( Assessment *assessment ) const;
    void assessmentRemoved( int index ) const;


  private:
    AssessmentList_P *p;


  private slots:
    void receivedAssessmentInfo( AssessmentInfo assessmentinfo ) const;
    void assessmentDestroyed();
};

QML_DECLARE_TYPE(AssessmentList)

#endif // ASSESSMENTLIST_H
