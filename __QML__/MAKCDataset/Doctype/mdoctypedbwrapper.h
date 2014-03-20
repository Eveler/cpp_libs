#ifndef MDOCTYPEDBWRAPPER_H
#define MDOCTYPEDBWRAPPER_H

#include "mabstractdbwrapper.h"


class MDoctype : public QQuickItem
{
    Q_OBJECT
    friend class MDocument;


  public:
    explicit MDoctype( QQuickItem *parent = NULL );
    ~MDoctype();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & name() const;
    void setName( const QString & name );

    int externalLinksCount() const;


  signals:
    void identifierChanged();
    void nameChanged();


  private:
    QVariant m__Identifier;
    QString m__Name;
    int m__ExternalLinksCount;

    int incrementExternalLinks();
    int decrementExternalLinks();
};

QML_DECLARE_TYPE( MDoctype )


class MDoctypeDBWrapper : public MAbstractDBWrapper
{
    Q_OBJECT


  public:
    explicit MDoctypeDBWrapper( MAbstractDataSource *parent = NULL );

    MDoctype *doctype( QVariant identifier ) const;


  protected:
    bool searching( const QString &queryText );
    bool initiating();
    bool saving( QObject *object );


  private:
    QHash<int, MDoctype *> m__ExistDoctypes;
};

#endif // MDOCTYPEDBWRAPPER_H
