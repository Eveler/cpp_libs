#ifndef TRUSTEE_H
#define TRUSTEE_H

#include <QObject>

#include "trusteeinfo.h"

#include <QtQml>


class Trustee_P;
class TrusteeList;

class Trustee : public QObject, public TrusteeInfo
{
    Q_OBJECT
    Q_DISABLE_COPY(Trustee)
    friend class TrusteeList;
    Q_PROPERTY(int index READ index NOTIFY indexChanged)
    Q_PROPERTY(QVariant identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)
    Q_PROPERTY(QVariant declarIdentifier READ declarIdentifier
               WRITE setDeclarIdentifier NOTIFY declarIdentifierChanged)
    Q_PROPERTY(QVariantList clientIdentifiers READ clientIdentifiers
               WRITE addClientIdentifier NOTIFY clientIdentifiersChanged)


  public:
    Trustee( TrusteeList *parent = 0 );
    Trustee( TrusteeList *parent, const TrusteeInfo &info );
    Trustee( TrusteeList *parent, Trustee *link );
    ~Trustee();

    Q_INVOKABLE TrusteeList * trusteeList() const;

    Q_INVOKABLE int index() const;

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    QVariant declarIdentifier() const;
    void setDeclarIdentifier( QVariant declarIdentifier );

    QVariantList clientIdentifiers() const;
    void addClientIdentifier( QVariant clientIdentifiers );
    void removeClientIdentifier( QVariant clientIdentifier );
    void clearClientIdentifiers();


  signals:
    void indexChanged();
    void identifierChanged();
    void declarIdentifierChanged();
    void clientIdentifiersChanged();
    void clientIdentifierAdded( int index );
    void clientIdentifierRemoved( int index );


  public slots:


  private:
    Trustee_P *p;
};

QML_DECLARE_TYPE(Trustee)

#endif // TRUSTEE_H
