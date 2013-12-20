#ifndef ASSESSMENTTYPELOADER_P_H
#define ASSESSMENTTYPELOADER_P_H

#include <QThread>

#include "assessmenttypeloader.h"
#include "assessmenttypeinfo.h"

#include <QHash>


class AssessmenttypeLoader_P : public QThread
{
    Q_OBJECT
    friend class AssessmenttypeLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendInfo( AssessmenttypeInfo * );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    QString m__LastError;
    QString m__ConnectionName;
    QString m__Filter;

    explicit AssessmenttypeLoader_P( AssessmenttypeLoader *parent );
    ~AssessmenttypeLoader_P();

    AssessmenttypeLoader * p_dptr() const;
};

#endif // ASSESSMENTTYPELOADER_P_H
