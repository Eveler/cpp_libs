#ifndef ADDRESS_H
#define ADDRESS_H

#include <QObject>
#include <QVariant>

#include "abstractsimpleobject.h"
#include "subject.h"
#include "region.h"
#include "area.h"
#include "city.h"
#include "innercity.h"
#include "township.h"
#include "street.h"
#include "subaddress.h"

class Address : public QObject
{
  typedef struct
  {
    QVariant m__Id;
    AbstractSimpleObject *m__Country;
    Subject *m__Subject;
    Region *m__Region;
    Area *m__Area;
    City *m__City;
    InnerCity *m__InnerCity;
    Township *m__Township;
    Street *m__Street;
    Subaddress *m__Subaddress;
    AbstractSimpleObject *m__Slaveaddress;
    AbstractSimpleObject *m__Postcode;
  } StructAddress;

  Q_OBJECT
public:
  explicit Address(QObject *parent = 0);

  const QVariant & id() const;
  AbstractSimpleObject * country() const;
  Subject * subject() const;
  Region * region() const;
  Area * area() const;
  City * city() const;
  InnerCity * innerCity() const;
  Township * township() const;
  Street * street() const;
  Subaddress * subaddress() const;
  AbstractSimpleObject * slaveaddress() const;
  AbstractSimpleObject * postalcode() const;

signals:
  void changedCountry( AbstractSimpleObject *value );
  void changedSubject( Subject *value );
  void changedRegion( Region *value );
  void changedArea( Area *value );
  void changedCity( City *value );
  void changedInnerCity( InnerCity *value );
  void changedTownship( Township *value );
  void changedStreet( Street *value );
  void changedSubaddress( Subaddress *value );
  void changedSlaveaddress( AbstractSimpleObject *value );
  void changedPostcode( AbstractSimpleObject *value );

public slots:
  void setId( QVariant value );
  void setCountry( AbstractSimpleObject *value );
  void setSubject( Subject *value );
  void setRegion( Region *value );
  void setArea( Area *value );
  void setCity( City *value );
  void setInnerCity( InnerCity *value );
  void setTownship( Township *value );
  void setStreet( Street *value );
  void setSubaddress( Subaddress *value );
  void setSlaveaddress( AbstractSimpleObject *value );
  void setPostcode( AbstractSimpleObject *value );

private:
  StructAddress m__StructAddress;
};

#endif // ADDRESS_H
