#ifndef ASSESSMENTTYPEINFO_H
#define ASSESSMENTTYPEINFO_H

#include <QtCore>


class AssessmenttypeInfo
{
  public:
    AssessmenttypeInfo();
    AssessmenttypeInfo( const AssessmenttypeInfo &other );
    ~AssessmenttypeInfo();

    QVariant identifier() const;
    void setIdentifier( QVariant identifier );

    const QString & name() const;
    void setName( const QString &name );


  private:
    QVariant m__Identifier;
    QString m__Name;
};

#endif // ASSESSMENTTYPEINFO_H
