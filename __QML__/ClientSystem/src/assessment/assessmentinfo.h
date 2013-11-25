#ifndef ASSESSMENTINFO_H
#define ASSESSMENTINFO_H

#include <QtCore>


class AssessmentInfo
{
  public:
    AssessmentInfo();
    AssessmentInfo( const AssessmentInfo &other );
    ~AssessmentInfo();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & name() const;
    void setName( const QString &name );


  private:
    QVariant m__Identifier;
    QString m__Name;
};

#endif // ASSESSMENTINFO_H
