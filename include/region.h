#ifndef REGION_H
#define REGION_H

#include <QObject>
#include <QVariant>

#include "abbreviation.h"

class Region : public QObject
{
  typedef struct
  {
    QVariant m__Id;
    Abbreviation *m__Abbreviation;
    QString m__Name;
  } StructRegion;

  Q_OBJECT
public:
  explicit Region(QObject *parent = 0);

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
  StructRegion m__StructRegion;
};

#endif // REGION_H
