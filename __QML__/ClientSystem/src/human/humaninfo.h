#ifndef HUMANINFO_H
#define HUMANINFO_H

#include <QObject>

#include <QtQml>


class HumanInfo : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(HumanInfo)


  public:
    HumanInfo();
    ~HumanInfo();

    Q_INVOKABLE QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    Q_INVOKABLE const QString & surname() const;
    Q_INVOKABLE void setSurname( const QString &surname );

    Q_INVOKABLE const QString & firstname() const;
    Q_INVOKABLE void setFirstname( const QString &firstname );

    Q_INVOKABLE const QString & lastname() const;
    Q_INVOKABLE void setLastname( const QString &lastname );

    Q_INVOKABLE const QString & address() const;
    Q_INVOKABLE void setAddress( const QString &address );

    Q_INVOKABLE const QString & phone() const;
    Q_INVOKABLE void setPhone( const QString &phone );

    Q_INVOKABLE const QString & email() const;
    Q_INVOKABLE void setEmail( const QString &email );


  private:
    QVariant m__Identifier;
    QString m__Surname;
    QString m__Firstname;
    QString m__Lastname;
    QString m__Address;
    QString m__Phone;
    QString m__Email;
};

QML_DECLARE_TYPE(HumanInfo)

#endif // HUMANINFO_H
