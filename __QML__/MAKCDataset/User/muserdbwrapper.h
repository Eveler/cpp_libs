#ifndef MUSERDBWRAPPER_H
#define MUSERDBWRAPPER_H

#include "mabstractdbwrapper.h"


class MUser : public QQuickItem
{
    Q_OBJECT
    friend class MDocument;
    Q_PROPERTY(QVariant identifier READ identifier NOTIFY identifierChanged)
    Q_PROPERTY(QVariant surname READ surname WRITE setSurname NOTIFY surnameChanged)
    Q_PROPERTY(QVariant firstname READ firstname WRITE setFirstname NOTIFY firstnameChanged)
    Q_PROPERTY(QVariant lastname READ lastname WRITE setLastname NOTIFY lastnameChanged)
    Q_PROPERTY(QVariant login READ login WRITE setLogin NOTIFY loginChanged)


  public:
    explicit MUser( QQuickItem *parent = NULL );
    ~MUser();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QVariant & surname() const;
    void setSurname( const QVariant &surname );

    const QVariant & firstname() const;
    void setFirstname( const QVariant &firstname );

    const QVariant & lastname() const;
    void setLastname( const QVariant &lastname );

    const QVariant & login() const;
    void setLogin( const QVariant &login );

    int externalLinksCount() const;


  signals:
    void identifierChanged();
    void surnameChanged();
    void firstnameChanged();
    void lastnameChanged();
    void loginChanged();
    void externalLinksCountChanged();


  private:
    QVariant m__Identifier;
    QVariant m__Surname;
    QVariant m__Firstname;
    QVariant m__Lastname;
    QVariant m__Login;
    int m__ExternalLinksCount;

    int incrementExternalLinks();
    int decrementExternalLinks();
};

QML_DECLARE_TYPE( MUser )


class MUserDBWrapper : public MAbstractDBWrapper
{
    Q_OBJECT
  public:
    explicit MUserDBWrapper( MAbstractDataSource *parent = 0 );
    ~MUserDBWrapper();

    MUser * user( QVariant identifier );
    QList<MUser *> users( QVariantList identifiers );


  protected:
    bool searching( const QString &queryText );
    bool initiating();
    bool saving( QObject *object );


  private:
    QHash<int, MUser *> m__ExistUsers;
};

#endif // MUSERDBWRAPPER_H
