#ifndef ASSESSMENTLOADER_P_H
#define ASSESSMENTLOADER_P_H

#include <QThread>

#include "assessmentloader.h"
#include "assessmentinfo.h"

#include <QSqlQuery>


class AssessmentLoader_P : public QThread
{
    Q_OBJECT
    friend class AssessmentLoader;


  public:


  signals:
    void sendError( QString errorText );
    void availableCountChanged();


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    bool m__Started;
    QString m__LastError;
    QString m__ConnectionName;
    QString m__Filter;
    QSqlQuery *m__Query;
    int m__AvailableCount;
    int m__ReceivedCount;

    explicit AssessmentLoader_P( AssessmentLoader *parent );
    ~AssessmentLoader_P();

    AssessmentLoader * p_dptr() const;

    AssessmentInfo * newInfo();
};

#endif // ASSESSMENTLOADER_P_H
