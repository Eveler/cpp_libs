#ifndef CITY_H
#define CITY_H

#include <QObject>
#include <QVariant>

#include "abbreviation.h"

class City : public QObject
{
  typedef struct
  {
    QVariant m__Id;
    Abbreviation *m__Abbreviation;
    QString m__Name;
  } StructCity;

  Q_OBJECT
public:
  explicit City(QObject *parent = 0);

  const QVariant & id() const;
  Abbreviation * abbreviation() const;
  const QString & name() const;

signals:
  void changedAbbreviation( Abbreviation *value );
  void changedName( QString value );

public slots:
  void setId( QVariant value );
  void setAbbreviation( Abbreviation *value );
  void setName( QString value );

private:
  StructCity m__StructCity;
};

#endif // CITY_H
