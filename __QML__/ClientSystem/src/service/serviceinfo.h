#ifndef SERVICEINFO_H
#define SERVICEINFO_H

#include <QObject>

#include <QtQml>


class ServiceInfo : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ServiceInfo)


  public:
    ServiceInfo();
    ~ServiceInfo();

    Q_INVOKABLE QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    Q_INVOKABLE QVariant root() const;
    Q_INVOKABLE void setRoot( QVariant root );

    Q_INVOKABLE const QString & sidx() const;
    Q_INVOKABLE void setSidx( const QString &sidx );

    Q_INVOKABLE const QString & name() const;
    Q_INVOKABLE void setName( const QString &name );

    Q_INVOKABLE int deadline() const;
    Q_INVOKABLE void setDeadline( int deadline );

    Q_INVOKABLE bool workdays() const;
    Q_INVOKABLE void setWorkdays( bool workdays );

    Q_INVOKABLE bool isactive() const;
    Q_INVOKABLE void setIsactive( bool isactive );


  private:
    QVariant m__Identifier;
    QVariant m__Root;
    QString m__Sidx;
    QString m__Name;
    int m__Deadline;
    bool m__Workdays;
    bool m__Isactive;
};

QML_DECLARE_TYPE(ServiceInfo)

#endif // SERVICEINFO_H
