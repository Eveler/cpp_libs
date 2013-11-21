#ifndef DOCTYPEINFO_H
#define DOCTYPEINFO_H

#include <QtCore>


class DoctypeInfo
{
  public:
    DoctypeInfo();
    DoctypeInfo( const DoctypeInfo &other );
    ~DoctypeInfo();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & name() const;
    void setName( const QString &name );


  private:
    QVariant m__Identifier;
    QString m__Name;
};

#endif // DOCTYPEINFO_H
