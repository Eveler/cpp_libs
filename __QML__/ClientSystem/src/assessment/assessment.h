#ifndef ASSESSMENT_H
#define ASSESSMENT_H

#include <QObject>

#include "assessmentinfo.h"

#include <QtQml>


class Assessment_P;
class AssessmentList;

class Assessment : public QObject, public AssessmentInfo
{
    Q_OBJECT
    Q_DISABLE_COPY(Assessment)
    friend class AssessmentList;
    Q_PROPERTY(int index READ index NOTIFY indexChanged)
    Q_PROPERTY(QVariant identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)


  public:
    Assessment( AssessmentList *parent = 0 );
    Assessment( AssessmentList *parent, const AssessmentInfo &info );
    Assessment( AssessmentList *parent, Assessment *link );
    ~Assessment();

    Q_INVOKABLE AssessmentList * assessmentList() const;

    int index() const;

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & name() const;
    void setName(  const QString &name );


  signals:
    void indexChanged();
    void identifierChanged();
    void nameChanged();


  public slots:


  private:
    Assessment_P *p;
};

QML_DECLARE_TYPE(Assessment)

#endif // ASSESSMENT_H
