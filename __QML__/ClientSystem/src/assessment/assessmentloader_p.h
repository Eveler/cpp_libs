#ifndef ASSESSMENTLOADER_P_H
#define ASSESSMENTLOADER_P_H

#include <QThread>

#include "assessmentloader.h"
#include "assessmentinfo.h"

#include <QHash>


class AssessmentLoader_P : public QThread
{
    Q_OBJECT
    friend class AssessmentLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendInfo( AssessmentInfo * );
    void countChanged();


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    bool m__Started;
    QString m__LastError;
    QString m__ConnectionName;
    QString m__Filter;
    int m__Count;

    explicit AssessmentLoader_P( AssessmentLoader *parent );
    ~AssessmentLoader_P();

    AssessmentLoader * p_dptr() const;
};

#endif // ASSESSMENTLOADER_P_H
