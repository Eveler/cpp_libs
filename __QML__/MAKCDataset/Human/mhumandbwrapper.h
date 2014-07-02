#ifndef MHUMANDBWRAPPER_H
#define MHUMANDBWRAPPER_H

#include "mabstractdbwrapper.h"

#include <QDate>


class MHuman : public QQuickItem
{
    Q_OBJECT
    friend class MOrganization;
    Q_PROPERTY(QVariant identifier READ identifier NOTIFY identifierChanged)
    Q_PROPERTY(QString surname READ surname WRITE setSurname NOTIFY surnameChanged)
    Q_PROPERTY(QString firstname READ firstname WRITE setFirstname NOTIFY firstnameChanged)
    Q_PROPERTY(QString lastname READ lastname WRITE setLastname NOTIFY lastnameChanged)
    Q_PROPERTY(QString phone READ phone WRITE setPhone NOTIFY phoneChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QDate birthday READ birthday WRITE setBirthday NOTIFY birthdayChanged)
    Q_PROPERTY(MDataSourceModel * documents READ documents)


  public:
    explicit MHuman( QQuickItem *parent = NULL );
    ~MHuman();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & surname() const;
    void setSurname( const QString &surname );

    const QString & firstname() const;
    void setFirstname( const QString &firstname );

    const QString & lastname() const;
    void setLastname( const QString &lastname );

    const QString & phone() const;
    void setPhone( const QString &phone );

    const QString & address() const;
    void setAddress( const QString &address );

    const QString & email() const;
    void setEmail( const QString &email );

    QDate birthday() const;
    void setBirthday( QDate birthday );

    MDataSourceModel * documents() const;

    int externalLinksCount() const;


  signals:
    void identifierChanged();
    void surnameChanged();
    void firstnameChanged();
    void lastnameChanged();
    void phoneChanged();
    void addressChanged();
    void emailChanged();
    void birthdayChanged();
    void externalLinksCountChanged();


  private:
    QVariant m__Identifier;
    QString m__Surname;
    QString m__Firstname;
    QString m__Lastname;
    QString m__Phone;
    QString m__Address;
    QString m__Email;
    QDate m__Birthday;
    MDataSourceModel *m__Documents;
    int m__ExternalLinksCount;

    int incrementExternalLinks();
    int decrementExternalLinks();
};

QML_DECLARE_TYPE( MHuman )


class MHumanDBWrapper : public MAbstractDBWrapper
{
    Q_OBJECT


  public:
    explicit MHumanDBWrapper( MAbstractDataSource *parent = NULL );
    ~MHumanDBWrapper();

    MHuman * human( QVariant identifier );
    QList<MHuman *> humans( QVariantList identifiers );


  protected:
    bool searching( const QString &queryText );
    bool initiating();
    bool saving( QObject *object );


  private:
    QHash<int, MHuman *> m__ExistHumans;
};

#endif // MHUMANDBWRAPPER_H
