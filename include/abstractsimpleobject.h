#ifndef ABSTRACTSIMPLEOBJECT_H
#define ABSTRACTSIMPLEOBJECT_H

#include <QObject>

#include "lib_export.h"

#include <QString>
#include <QVariant>


class EXPORT AbstractSimpleObject : public QObject
{
  Q_OBJECT


public:
  explicit AbstractSimpleObject( QVariant id, QObject *parent = 0);

  const QVariant & id() const;


signals:


public slots:


private:
  QVariant m__Id;
};

#endif // ABSTRACTSIMPLEOBJECT_H
