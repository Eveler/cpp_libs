#ifndef TRUSTEEINFO_H
#define TRUSTEEINFO_H

#include <QObject>

#include <QtQml>


class TrusteeInfo : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(TrusteeInfo)


  public:
    TrusteeInfo();
    ~TrusteeInfo();

    Q_INVOKABLE QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    Q_INVOKABLE QVariant declarIdentifier() const;
    Q_INVOKABLE void setDeclarIdentifier( QVariant declarIdentifier );

    Q_INVOKABLE QVariantList clientIdentifiers() const;
    Q_INVOKABLE void addClientIdentifier( QVariant clientIdentifiers );
    Q_INVOKABLE void removeClientIdentifier( QVariant clientIdentifiers );
    Q_INVOKABLE void clearClientIdentifiers();


  private:
    QVariant m__Identifier;
    QVariant m__DeclarIdentifier;
    QVariantList m__ClientIdentifiers;
};

QML_DECLARE_TYPE(TrusteeInfo)

#endif // TRUSTEEINFO_H
