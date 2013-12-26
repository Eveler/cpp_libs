#ifndef ASSESSMENTINFO_H
#define ASSESSMENTINFO_H

#include <QObject>

#include <QtQml>


class AssessmentInfo : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AssessmentInfo)


  public:
    AssessmentInfo();
    ~AssessmentInfo();

    Q_INVOKABLE QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    Q_INVOKABLE QString name() const;
    Q_INVOKABLE void setName( QString name );


  private:
    QVariant m__Identifier;
    QString m__Name;
};

QML_DECLARE_TYPE(AssessmentInfo)

#endif // ASSESSMENTINFO_H
