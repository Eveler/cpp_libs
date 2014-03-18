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
    void setName( const QString & name );

    const QString & series() const;
    void setSeries( const QString &series );

    const QString & number() const;
    void setNumber( const QString & number );

    QDate created() const;
    void setCreated( QDate created );

    QDate expires() const;
    void setExpires( QDate expires );

    QUrl source() const;
    void setSource( QUrl source );

    const QObjectList & externalLinks() const;
    void addExternalLink( QObject *externalLink );
    void removeExternalLink( QObject *externalLink );


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
    QObjectList m__ExternalLinks;
};

QML_DECLARE_TYPE( MDocument )


class MHuman;

class MDocumentDBWrapper : public MAbstractDBWrapper
{
    Q_OBJECT


  public:
    enum DocumentWrapperJobType {
      HumanDocuments = Saving+1
    };

    explicit MDocumentDBWrapper( MAbstractDataSource *parent = NULL );

    bool find( const QString &filter );
    bool find( MHuman *human );

    QObject * searched();


  protected:
    void job( int objectiveType, const QVariant &objectiveValue );
    bool searching( const QString &queryText );
    bool searching( MHuman *human );
    bool initiating();
    bool saving( QObject *object );


  private:
    QList<QObject *> m__Searched;
    QHash<int, MDocument *> m__ExistDocuments;
};

#endif // MDOCUMENTDBWRAPPER_H
