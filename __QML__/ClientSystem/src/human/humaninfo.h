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

    Q_INVOKABLE QString surname() const;
    Q_INVOKABLE void setSurname( QString surname );

    Q_INVOKABLE QString firstname() const;
    Q_INVOKABLE void setFirstname( QString firstname );

    Q_INVOKABLE QString lastname() const;
    Q_INVOKABLE void setLastname( QString lastname );

    Q_INVOKABLE QString address() const;
    Q_INVOKABLE void setAddress( QString address );

    Q_INVOKABLE QString phone() const;
    Q_INVOKABLE void setPhone( QString phone );

    Q_INVOKABLE QString email() const;
    Q_INVOKABLE void setEmail( QString email );


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
