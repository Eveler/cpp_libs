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
    Q_INVOKABLE void setIdentifier( QVariant identifier );

    Q_INVOKABLE QVariant declarIdentifier() const;
    Q_INVOKABLE void setDeclarIdentifier( QVariant declarIdentifier );

    Q_INVOKABLE QVariant trusteeClientIdentifier() const;
    Q_INVOKABLE void setTrusteeClientIdentifier( QVariant trusteeClientIdentifier );

    Q_INVOKABLE QVariant clientIdentifier() const;
    Q_INVOKABLE void setClientIdentifier( QVariant clientIdentifier );


  private:
    QVariant m__Identifier;
    QVariant m__DeclarIdentifier;
    QVariant m__TrusteeClientIdentifier;
    QVariant m__ClientIdentifier;
};

QML_DECLARE_TYPE(TrusteeInfo)

#endif // TRUSTEEINFO_H
