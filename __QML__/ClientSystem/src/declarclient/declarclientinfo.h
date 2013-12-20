#ifndef declarCLIENTINFO_H
#define declarCLIENTINFO_H

#include <QObject>

#include <QtQml>


class DeclarClientInfo : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DeclarClientInfo)


  public:
    DeclarClientInfo();
    ~DeclarClientInfo();

    Q_INVOKABLE QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    Q_INVOKABLE QVariant declarIdentifier() const;
    Q_INVOKABLE void setDeclarIdentifier( QVariant declarIdentifier );

    Q_INVOKABLE QVariant clientIdentifier() const;
    Q_INVOKABLE void setClientIdentifier( QVariant clientIdentifier );


  private:
    QVariant m__Identifier;
    QVariant m__DeclarIdentifier;
    QVariant m__ClientIdentifier;
};

QML_DECLARE_TYPE(DeclarClientInfo)

#endif // declarCLIENTINFO_H
