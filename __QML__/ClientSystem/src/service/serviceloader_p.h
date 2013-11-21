#ifndef SERVICELOADER_P_H
#define SERVICELOADER_P_H

#include <QThread>

#include "serviceloader.h"
#include "servicelist.h"

#include <QHash>


class ServiceLoader_P : public QThread
{
    Q_OBJECT
    friend class ServiceLoader;


  public:


  signals:
    void sendError( QString errorText );
    void sendServiceInfo( ServiceInfo );


  public slots:


  protected:
    void run();


  private:
    bool m__Successfully;
    int m__ErrorLastId;
    QHash<int, QString> m__Errors;
    QString m__ConnectionName;
    QString m__Filter;
    ServiceList *m__Source;

    explicit ServiceLoader_P( ServiceLoader *parent );
    ~ServiceLoader_P();

    ServiceLoader * p_dptr() const;
};

#endif // SERVICELOADER_P_H
