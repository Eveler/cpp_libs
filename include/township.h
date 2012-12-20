#ifndef TOWNSHIP_H
#define TOWNSHIP_H

#include <QObject>
#include <QVariant>

#include "abbreviation.h"

class Township : public QObject
{
  typedef struct
  {
    QVariant m__Id;
    Abbreviation *m__Abbreviation;
    QString m__Name;
  } StructTownship;

  Q_OBJECT
public:
  explicit Township(QObject *parent = 0);

  const QVariant & id() const;
  Abbreviation * abbreviation() const;
  const QString & name() const;

signals:

public slots:
  void setId( QVariant value );
  void setAbbreviation( Abbreviation *value );
  void setName( QString value );

private:
  StructTownship m__StructTownship;
};

#endif // TOWNSHIP_H
