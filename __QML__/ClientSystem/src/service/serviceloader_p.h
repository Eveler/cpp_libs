#ifndef SERVICELOADER_P_H
#define SERVICELOADER_P_H

#include <QThread>

#include "serviceloader.h"
#include "serviceinfo.h"

#include <QSqlQuery>


class ServiceLoader_P : public QThread
{
    Q_OBJECT
    friend class ServiceLoader;


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

    explicit ServiceLoader_P( ServiceLoader *parent );
    ~ServiceLoader_P();

    ServiceLoader * p_dptr() const;

    ServiceInfo * newInfo();
};

#endif // SERVICELOADER_P_H
