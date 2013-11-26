#ifndef ASSESSMENTLOADER_P_H
#define ASSESSMENTLOADER_P_H

#include <QThread>

#include "assessmentloader.h"
#include "assessmentlist.h"

#include <QHash>


class AssessmentLoader_P : public QThread
{
    Q_OBJECT
    friend class AssessmentLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendAssessmentInfo( AssessmentInfo );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    int m__ErrorLastId;
    QHash<int, QString> m__Errors;
    QString m__ConnectionName;
    QString m__Filter;
    AssessmentList *m__Source;

    explicit AssessmentLoader_P( AssessmentLoader *parent );
    ~AssessmentLoader_P();

    AssessmentLoader * p_dptr() const;
};

#endif // ASSESSMENTLOADER_P_H
