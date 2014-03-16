#ifndef MDOCUMENTDBWRAPPER_H
#define MDOCUMENTDBWRAPPER_H

#include "mabstractdbwrapper.h"

#include <QDate>


class MDocument : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QVariant identifier READ identifier NOTIFY identifierChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString series READ series WRITE setSeries NOTIFY seriesChanged)
    Q_PROPERTY(QString number READ number WRITE setNumber NOTIFY numberChanged)
    Q_PROPERTY(QDate created READ created WRITE setCreated NOTIFY createdChanged)
    Q_PROPERTY(QDate expires READ expires WRITE setExpires NOTIFY expiresChanged)
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)


  public:
    explicit MDocument( QQuickItem *parent = NULL );
    ~MDocument();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & name() const;
    void setName( QString &name );

    const QString & series() const;
    void setSeries( QString &series );

    const QString & number() const;
    void setNumber( QString &number );

    QDate created() const;
    void setCreated( QDate created );

    QDate expires() const;
    void setExpires( QDate expires );

    QUrl source() const;
    void setSource( QUrl source );


  signals:
    void identifierChanged();
    void nameChanged();
    void seriesChanged();
    void numberChanged();
    void createdChanged();
    void expiresChanged();
    void sourceChanged();


  private:
    QVariant m__Identifier;
    QString m__Name;
    QString m__Series;
    QString m__Number;
    QDate m__Created;
    QDate m__Expires;
    QUrl m__Source;
};

QML_DECLARE_TYPE( MDocument )


class MDocumentDBWrapper : public MAbstractDBWrapper
{
    Q_OBJECT
  public:
    explicit MDocumentDBWrapper( MAbstractDataSource *parent = NULL );


  protected:
    bool searching( const QString &queryText );
    bool initiating();
    bool saving( QObject *object );
};

#endif // MDOCUMENTDBWRAPPER_H
