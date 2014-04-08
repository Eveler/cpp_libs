#ifndef MSERVICEDBWRAPPER_H
#define MSERVICEDBWRAPPER_H

#include "mabstractdbwrapper.h"


class MService : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QVariant identifier READ identifier NOTIFY identifierChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString index READ index WRITE setIndex NOTIFY indexChanged)
    Q_PROPERTY(int deadline READ deadline WRITE setDeadline NOTIFY deadlineChanged)
    Q_PROPERTY(bool workdays READ workdays WRITE setWorkdays NOTIFY workdaysChanged)
    Q_PROPERTY(bool isactive READ isactive WRITE setIsactive NOTIFY isactiveChanged)
    Q_PROPERTY(MDataSourceModel * subservices READ subservices)


  public:
    explicit MService( QQuickItem *parent = NULL );
    ~MService();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & index() const;
    void setIndex( const QString &index );

    const QString & name() const;
    void setName( const QString &name );

    int deadline() const;
    void setDeadline( int deadline );

    bool workdays() const;
    void setWorkdays( bool workdays );

    bool isactive() const;
    void setIsactive( bool isactive );

    MDataSourceModel * subservices() const;

    int externalLinksCount() const;


  signals:
    void identifierChanged();
    void indexChanged();
    void nameChanged();
    void deadlineChanged();
    void workdaysChanged();
    void isactiveChanged();
    void externalLinksCountChanged();


  private:
    QVariant m__Identifier;
    QString m__Index;
    QString m__Name;
    int m__Deadline;
    bool m__Workdays;
    bool m__Isactive;
    MDataSourceModel *m__Subservices;
    int m__ExternalLinksCount;

    int incrementExternalLinks();
    int decrementExternalLinks();
};

QML_DECLARE_TYPE( MService )


class MServiceDBWrapper : public MAbstractDBWrapper
{
    Q_OBJECT
  public:
    explicit MServiceDBWrapper( MAbstractDataSource *parent = NULL );
    ~MServiceDBWrapper();

    MService *service( QVariant identifier );
    QList<MService *> services( QVariantList identifiers );


  protected:
    bool searching( const QString &queryText );
    bool initiating();
    bool saving( QObject *object );


  private:
    QHash<int, MService *> m__ExistServices;

    void pSearching( QString queryText );
};

#endif // MSERVICEDBWRAPPER_H
