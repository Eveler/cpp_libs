#ifndef MPROCEDUREDBWRAPPER_H
#define MPROCEDUREDBWRAPPER_H

#include "mabstractdbwrapper.h"


class MProcedure : public QQuickItem
{
    Q_OBJECT
    friend class MDocument;
    Q_PROPERTY(QVariant identifier READ identifier NOTIFY identifierChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)


  public:
    explicit MProcedure( QQuickItem *parent = NULL );
    ~MProcedure();

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

QML_DECLARE_TYPE( MProcedure )


class MProcedureDBWrapper : public MAbstractDBWrapper
{
    Q_OBJECT
  public:
    explicit MProcedureDBWrapper( MAbstractDataSource *parent = NULL );
    ~MProcedureDBWrapper();

    MProcedure *procedure( QVariant identifier );
    QList<MProcedure *> procedures( QVariantList identifiers );


  protected:
    bool searching( const QString &queryText );
    bool initiating();
    bool saving( QObject *object );


  private:
    QHash<int, MProcedure *> m__ExistProcedures;
};

#endif // MPROCEDUREDBWRAPPER_H
