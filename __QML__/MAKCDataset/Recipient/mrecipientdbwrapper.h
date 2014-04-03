#ifndef MRECIPIENTDBWRAPPER_H
#define MRECIPIENTDBWRAPPER_H

#include "mabstractdbwrapper.h"


class MRecipient : public QQuickItem
{
    Q_OBJECT
    friend class MDocument;
    Q_PROPERTY(QVariant identifier READ identifier NOTIFY identifierChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)


  public:
    explicit MRecipient( QQuickItem *parent = NULL );
    ~MRecipient();

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

QML_DECLARE_TYPE( MRecipient )


class MRecipientDBWrapper : public MAbstractDBWrapper
{
    Q_OBJECT


  public:
    explicit MRecipientDBWrapper( MAbstractDataSource *parent = NULL );
    ~MRecipientDBWrapper();

    MRecipient *recipient( QVariant identifier );
    QList<MRecipient *> recipients( QVariantList identifiers );


  protected:
    bool searching( const QString &queryText );
    bool initiating();
    bool saving( QObject *object );


  private:
    QHash<int, MRecipient *> m__ExistRecipients;
};

#endif // MRECIPIENTDBWRAPPER_H
