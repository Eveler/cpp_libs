#ifndef RESULTWAYINFO_H
#define RESULTWAYINFO_H

#include <QtCore>


class ResultwayInfo
{
  public:
    ResultwayInfo();
    ResultwayInfo( const ResultwayInfo &other );
    ~ResultwayInfo();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & name() const;
    void setName( const QString &name );


  private:
    QVariant m__Identifier;
    QString m__Name;
};

#endif // RESULTWAYINFO_H
