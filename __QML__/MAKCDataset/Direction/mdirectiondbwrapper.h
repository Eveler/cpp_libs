#ifndef MDIRECTIONDBWRAPPER_H
#define MDIRECTIONDBWRAPPER_H

#include "mabstractdbwrapper.h"


class MDirection : public QQuickItem
{
    Q_OBJECT
    friend class MDocument;
    Q_PROPERTY(QVariant identifier READ identifier NOTIFY identifierChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)


  public:
    explicit MDirection( QQuickItem *parent = NULL );
    ~MDirection();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & name() const;
    void setName( const QString & name );

    int externalLinksCount() const;


  signals:
    void identifierChanged();
    void nameChanged();
    void externalLinksCountChanged();


  private:
    QVariant m__Identifier;
    QString m__Name;
    int m__ExternalLinksCount;

    int incrementExternalLinks();
    int decrementExternalLinks();
};

QML_DECLARE_TYPE( MDirection )


class MDirectionDBWrapper : public MAbstractDBWrapper
{
    Q_OBJECT
  public:
    explicit MDirectionDBWrapper( MAbstractDataSource *parent = NULL );
    ~MDirectionDBWrapper();

    MDirection *direction( QVariant identifier );
    QList<MDirection *> directions( QVariantList identifiers );


  protected:
    bool searching( const QString &queryText );
    bool initiating();
    bool saving( QObject *object );


  private:
    QHash<int, MDirection *> m__ExistDirections;
};

#endif // MDIRECTIONDBWRAPPER_H
