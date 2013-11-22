#ifndef declarCLIENT_H
#define declarCLIENT_H

#include <QObject>

#include "declarclientinfo.h"

#include <QtQml>


class DeclarClient_P;
class DeclarClientList;

class DeclarClient : public QObject, public DeclarClientInfo
{
    Q_OBJECT
    Q_DISABLE_COPY(DeclarClient)
    friend class DeclarClientList;
    Q_PROPERTY(int index READ index NOTIFY indexChanged)
    Q_PROPERTY(QVariant identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)
    Q_PROPERTY(QVariant declarIdentifier READ declarIdentifier
               WRITE setDeclarIdentifier NOTIFY declarIdentifierChanged)
    Q_PROPERTY(QVariant clientIdentifier READ clientIdentifier
               WRITE setClientIdentifier NOTIFY clientIdentifierChanged)


  public:
    DeclarClient( DeclarClientList *parent = 0 );
    DeclarClient( DeclarClientList *parent, const DeclarClientInfo &info );
    DeclarClient( DeclarClientList *parent, DeclarClient *link );
    ~DeclarClient();

    Q_INVOKABLE DeclarClientList * declarclientList() const;

    int index() const;

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    QVariant declarIdentifier() const;
    void setDeclarIdentifier( QVariant declarIdentifier );

    QVariant clientIdentifier() const;
    void setClientIdentifier( QVariant clientIdentifier );


  signals:
    void indexChanged();
    void identifierChanged();
    void declarIdentifierChanged();
    void clientIdentifierChanged();


  public slots:


  private:
    DeclarClient_P *p;
};

QML_DECLARE_TYPE(DeclarClient)

#endif // declarCLIENT_H
