#ifndef RESULTINFO_H
#define RESULTINFO_H

#include <QtCore>


class ResultInfo
{
  public:
    ResultInfo();
    ResultInfo( const ResultInfo &other );
    ~ResultInfo();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & name() const;
    void setName( const QString &name );


  private:
    QVariant m__Identifier;
    QString m__Name;
};

#endif // RESULTINFO_H
