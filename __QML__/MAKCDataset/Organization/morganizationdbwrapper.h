#ifndef MORGANIZATIONDBWRAPPER_H
#define MORGANIZATIONDBWRAPPER_H

#include "mabstractdbwrapper.h"


class MHuman;

class MOrganization : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QVariant identifier READ identifier NOTIFY identifierChanged)
    Q_PROPERTY(QVariant name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QVariant phone READ phone WRITE setPhone NOTIFY phoneChanged)
    Q_PROPERTY(QVariant address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QVariant email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(MHuman * delegate READ delegate WRITE setDelegate NOTIFY delegateChanged)


  public:
    explicit MOrganization( QQuickItem *parent = NULL );
    ~MOrganization();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QVariant & name() const;
    void setName( const QVariant &name );

    const QVariant & phone() const;
    void setPhone( const QVariant &phone );

    const QVariant & address() const;
    void setAddress( const QVariant &address );

    const QVariant & email() const;
    void setEmail( const QVariant &email );

    MHuman * delegate() const;
    void setDelegate( MHuman *delegate );

    int externalLinksCount() const;


  signals:
    void identifierChanged();
    void nameChanged();
    void phoneChanged();
    void addressChanged();
    void emailChanged();
    void delegateChanged();
    void externalLinksCountChanged();


  private:
    QVariant m__Identifier;
    QVariant m__Name;
    QVariant m__Phone;
    QVariant m__Address;
    QVariant m__Email;
    MHuman *m__Delegate;
    int m__ExternalLinksCount;

    int incrementExternalLinks();
    int decrementExternalLinks();
};

QML_DECLARE_TYPE( MOrganization )


class MOrganizationDBWrapper : public MAbstractDBWrapper
{
    Q_OBJECT


  public:
    explicit MOrganizationDBWrapper( MAbstractDataSource *parent = NULL );
    ~MOrganizationDBWrapper();

    MOrganization * organization( QVariant identifier );


  protected:
    bool searching( const QString &queryText );
    bool initiating();
    bool saving( QObject *object );


  private:
    QHash<int, MOrganization *> m__ExistOrganizations;
};

#endif // MORGANIZATIONDBWRAPPER_H
