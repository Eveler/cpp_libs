#ifndef TRUSTEEINFO_H
#define TRUSTEEINFO_H

#include <QtCore>


class TrusteeInfo
{
  public:
    TrusteeInfo();
    TrusteeInfo( const TrusteeInfo &other );
    ~TrusteeInfo();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    QVariant declarIdentifier() const;
    void setDeclarIdentifier( QVariant declarIdentifier );

    QVariant trusteeClientIdentifier() const;
    void setTrusteeClientIdentifier( QVariant trusteeClientIdentifier );

    QVariant clientIdentifier() const;
    void setClientIdentifier( QVariant clientIdentifier );


  private:
    QVariant m__Identifier;
    QVariant m__DeclarIdentifier;
    QVariant m__TrusteeClientIdentifier;
    QVariant m__ClientIdentifier;
};

#endif // TRUSTEEINFO_H
