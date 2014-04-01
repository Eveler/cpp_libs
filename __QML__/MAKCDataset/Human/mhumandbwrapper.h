#ifndef MHUMANDBWRAPPER_H
#define MHUMANDBWRAPPER_H

#include "mabstractdbwrapper.h"


class MHuman : public QQuickItem
{
    Q_OBJECT
    friend class MOrganization;
    Q_PROPERTY(QVariant identifier READ identifier NOTIFY identifierChanged)
    Q_PROPERTY(QVariant surname READ surname WRITE setSurname NOTIFY surnameChanged)
    Q_PROPERTY(QVariant firstname READ firstname WRITE setFirstname NOTIFY firstnameChanged)
    Q_PROPERTY(QVariant lastname READ lastname WRITE setLastname NOTIFY lastnameChanged)
    Q_PROPERTY(QVariant phone READ phone WRITE setPhone NOTIFY phoneChanged)
    Q_PROPERTY(QVariant address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QVariant email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QVariant birthday READ birthday WRITE setBirthday NOTIFY birthdayChanged)
    Q_PROPERTY(MDataSourceModel * documents READ documents)


  public:
    explicit MHuman( QQuickItem *parent = NULL );
    ~MHuman();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QVariant & surname() const;
    void setSurname( const QVariant &surname );

    const QVariant & firstname() const;
    void setFirstname( const QVariant &firstname );

    const QVariant & lastname() const;
    void setLastname( const QVariant &lastname );

    const QVariant & phone() const;
    void setPhone( const QVariant &phone );

    const QVariant & address() const;
    void setAddress( const QVariant &address );

    const QVariant & email() const;
    void setEmail( const QVariant &email );

    const QVariant & birthday() const;
    void setBirthday( const QVariant &birthday );

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
    QVariant m__Surname;
    QVariant m__Firstname;
    QVariant m__Lastname;
    QVariant m__Phone;
    QVariant m__Address;
    QVariant m__Email;
    QVariant m__Birthday;
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
