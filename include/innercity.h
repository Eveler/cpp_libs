#ifndef INNERCITY_H
#define INNERCITY_H

#include <QObject>
#include <QVariant>

#include "abbreviation.h"

class InnerCity : public QObject
{
  typedef struct
  {
    QVariant m__Id;
    Abbreviation *m__Abbreviation;
    QString m__Name;
  } StructInnerCity;

  Q_OBJECT
public:
  explicit InnerCity(QObject *parent = 0);

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
  StructInnerCity m__StructInnerCity;
};

#endif // INNERCITY_H
