#ifndef AREA_H
#define AREA_H

#include <QObject>
#include <QVariant>

#include "abbreviation.h"

class Area : public QObject
{
  typedef struct
  {
    QVariant m__Id;
    Abbreviation *m__Abbreviation;
    QString m__Name;
  } StructArea;

  Q_OBJECT
public:
  explicit Area(QObject *parent = 0);

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
  StructArea m__StructArea;
};

#endif // AREA_H
