#ifndef ADDRESS_H
#define ADDRESS_H

#include <QObject>
#include <QVariant>

#include "abstractsimpleobject.h"

class Address : public QObject
{
  typedef struct
  {
    QVariant m__Id;
    AbstractSimpleObject *m__Postcode;
    AbstractSimpleObject *m__Country;
  } StructAddress;

  Q_OBJECT
public:
  explicit Address(QObject *parent = 0);

  const QVariant & id() const;
  const QString & name() const;
  const int & deadline() const;
  bool active() const;

signals:

public slots:
  void setId( QVariant value );
  void setName( QString value );
  void setDeadline( int value );
  void setActive( bool value );

private:
  StructAddress m__StructAddress;
};

#endif // ADDRESS_H
