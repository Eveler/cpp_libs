#ifndef SERVICELOADER_P_H
#define SERVICELOADER_P_H

#include <QThread>

#include "serviceloader.h"
#include "serviceinfo.h"

#include <QHash>


class ServiceLoader_P : public QThread
{
    Q_OBJECT
    friend class ServiceLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendInfo( ServiceInfo * );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    QString m__LastError;
    QString m__ConnectionName;
    QString m__Filter;

    explicit ServiceLoader_P( ServiceLoader *parent );
    ~ServiceLoader_P();

    ServiceLoader * p_dptr() const;
};

#endif // SERVICELOADER_P_H
