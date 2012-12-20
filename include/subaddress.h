#ifndef Subaddress_H
#define Subaddress_H

#include <QObject>
#include <QVariant>

#include "abstractsimpleobject.h"
#include "structurestatus.h"

class Subaddress : public QObject
{
  typedef struct
  {
    QVariant m__Id;
    AbstractSimpleObject *m__Postcode;
    QString m__HouseNumber;
    QString m__BuildNumber;
    QString m__StructNumber;
    StructureStatus *m__StructureStatus;
  } StructSubaddress;

  Q_OBJECT
public:
  explicit Subaddress(QObject *parent = 0);

  const QVariant & id() const;
  AbstractSimpleObject * postcode() const;
  const QString & houseNumber() const;
  const QString & buildNumber() const;
  const QString & structNumber() const;
  StructureStatus * structureStatus() const;

signals:

public slots:
  void setId( QVariant value );
  void setPostcode( AbstractSimpleObject * value );
  void setHouseNumber( QString value );
  void setBuildNumber( QString value );
  void setStructNumber( QString value );
  void setStructureStatus( StructureStatus * value );

private:
  StructSubaddress m__StructSubaddress;
};

#endif // Subaddress_H
