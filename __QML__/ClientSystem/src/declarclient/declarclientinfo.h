#ifndef declarCLIENTINFO_H
#define declarCLIENTINFO_H

#include <QtCore>


class DeclarClientInfo
{
  public:
    DeclarClientInfo();
    DeclarClientInfo( const DeclarClientInfo &other );
    ~DeclarClientInfo();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    QVariant declarIdentifier() const;
    void setDeclarIdentifier( QVariant declarIdentifier );

    QVariant clientIdentifier() const;
    void setClientIdentifier( QVariant clientIdentifier );


  private:
    QVariant m__Identifier;
    QVariant m__DeclarIdentifier;
    QVariant m__ClientIdentifier;
};

#endif // declarCLIENTINFO_H
