#ifndef SERVICEINFO_H
#define SERVICEINFO_H

#include <QtCore>


class ServiceInfo
{
  public:
    ServiceInfo();
    ServiceInfo( const ServiceInfo &other );
    ~ServiceInfo();

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


  private:
    QVariant m__Identifier;
    QVariant m__Root;
    QString m__Sidx;
    QString m__Name;
    int m__Deadline;
    bool m__Workdays;
    bool m__Isactive;
};

#endif // SERVICEINFO_H
