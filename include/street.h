#ifndef STREET_H
#define STREET_H

#include <QObject>
#include <QVariant>

#include "abbreviation.h"

class Street : public QObject
{
  typedef struct
  {
    QVariant m__Id;
    Abbreviation *m__Abbreviation;
    QString m__Name;
  } StructStreet;

  Q_OBJECT
public:
  explicit Street(QObject *parent = 0);

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
  StructStreet m__StructStreet;
};

#endif // STREET_H
