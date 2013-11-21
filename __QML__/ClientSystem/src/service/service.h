#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>

#include "serviceinfo.h"

#include <QtQml>


class Service_P;
class ServiceList;

class Service : public QObject, public ServiceInfo
{
    Q_OBJECT
    Q_DISABLE_COPY(Service)
    friend class ServiceList;
    Q_PROPERTY(int index READ index NOTIFY indexChanged)
    Q_PROPERTY(QVariant identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)
    Q_PROPERTY(QVariant root READ root WRITE setRoot NOTIFY rootChanged)
    Q_PROPERTY(QString sidx READ sidx WRITE setSidx NOTIFY sidxChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int deadline READ deadline WRITE setDeadline NOTIFY deadlineChanged)
    Q_PROPERTY(bool workdays READ workdays WRITE setWorkdays NOTIFY workdaysChanged)
    Q_PROPERTY(bool isactive READ isactive WRITE setIsactive NOTIFY isactiveChanged)


  public:
    Service( ServiceList *parent = 0 );
    Service( ServiceList *parent, const ServiceInfo &info );
    Service( ServiceList *parent, Service *link );
    ~Service();

    Q_INVOKABLE ServiceList * serviceList() const;

    int index() const;

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    QVariant root() const;
    void setRoot( QVariant root );

    const QString & sidx() const;
    void setSidx( const QString &sidx );

    const QString & name() const;
    void setName( const QString &name );

    int deadline() const;
    void setDeadline( int deadline );

    bool workdays() const;
    void setWorkdays( bool workdays );

    bool isactive() const;
    void setIsactive( bool isactive );


  signals:
    void indexChanged();
    void identifierChanged();
    void rootChanged();
    void sidxChanged();
    void nameChanged();
    void deadlineChanged();
    void workdaysChanged();
    void isactiveChanged();


  public slots:


  private:
    Service_P *p;
};

QML_DECLARE_TYPE(Service)

#endif // SERVICE_H
