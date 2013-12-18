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

    QVariantList clientIdentifiers() const;
    void addClientIdentifier( QVariant clientIdentifiers );
    void removeClientIdentifier( QVariant clientIdentifiers );
    void clearClientIdentifiers();


  private:
    QVariant m__Identifier;
    QVariant m__DeclarIdentifier;
    QVariantList m__ClientIdentifiers;
};

#endif // TRUSTEEINFO_H
