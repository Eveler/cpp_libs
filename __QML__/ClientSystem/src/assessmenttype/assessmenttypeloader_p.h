#ifndef ASSESSMENTTYPELOADER_P_H
#define ASSESSMENTTYPELOADER_P_H

#include <QThread>

#include "assessmenttypeloader.h"
#include "assessmenttypelist.h"

#include <QHash>


class AssessmenttypeLoader_P : public QThread
{
    Q_OBJECT
    friend class AssessmenttypeLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendAssessmenttypeInfo( AssessmenttypeInfo );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    int m__ErrorLastId;
    QHash<int, QString> m__Errors;
    QString m__ConnectionName;
    QString m__Filter;
    AssessmenttypeList *m__Source;

    explicit AssessmenttypeLoader_P( AssessmenttypeLoader *parent );
    ~AssessmenttypeLoader_P();

    AssessmenttypeLoader * p_dptr() const;
};

#endif // ASSESSMENTTYPELOADER_P_H
