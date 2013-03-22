#ifndef ABSTRACTSIMPLEOBJECT_H
#define ABSTRACTSIMPLEOBJECT_H

#include <QObject>

#include "lib_export.h"

#include <QString>
#include <QVariant>


class AbstractSimpleStorage;

class EXPORT AbstractSimpleObject : public QObject
{
  typedef struct
  {
    QVariant m__Id;
    QString m__Name;
  } StructAbstractSimpleObject;
  Q_OBJECT
  friend class AbstractSimpleStorage;


public:
  ~AbstractSimpleObject();

  const QVariant & id() const;
  const QString & name() const;


signals:
  void changedName( QString value );


public slots:
  void setName( QString value );


private:
  StructAbstractSimpleObject m__Value;

  explicit AbstractSimpleObject( QVariant id, QObject *parent = 0);

  void clear();

  void setId( QVariant value );
};

#endif // ABSTRACTSIMPLEOBJECT_H
