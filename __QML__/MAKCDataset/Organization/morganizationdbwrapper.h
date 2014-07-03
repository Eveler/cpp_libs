#ifndef MORGANIZATIONDBWRAPPER_H
#define MORGANIZATIONDBWRAPPER_H

#include "mabstractdbwrapper.h"


class MHuman;

class MOrganization : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QVariant identifier READ identifier NOTIFY identifierChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString phone READ phone WRITE setPhone NOTIFY phoneChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(MHuman * delegate READ delegate WRITE setDelegate NOTIFY delegateChanged)
    Q_PROPERTY(MDataSourceModel * documents READ documents)


  public:
    explicit MOrganization( QQuickItem *parent = NULL );
    ~MOrganization();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & name() const;
    void setName( const QString &name );

    const QString & phone() const;
    void setPhone( const QString &phone );

    const QString & address() const;
    void setAddress( const QString &address );

    const QString & email() const;
    void setEmail( const QString &email );

    MHuman * delegate() const;
    void setDelegate( MHuman *delegate );

    MDataSourceModel * documents() const;

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
    QString m__Name;
    QString m__Phone;
    QString m__Address;
    QString m__Email;
    MHuman *m__Delegate;
    MDataSourceModel *m__Documents;
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
