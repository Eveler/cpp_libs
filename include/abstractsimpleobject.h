#ifndef ABSTRACTSIMPLEOBJECT_H
#define ABSTRACTSIMPLEOBJECT_H

#include <QObject>
#include <QString>
#include <QVariant>

class AbstractSimpleObject : public QObject
{
  typedef struct
  {
    QVariant m__Id;
    QString m__Name;
  } StructAbstractSimpleObject;

  Q_OBJECT
public:
  explicit AbstractSimpleObject(QObject *parent = 0);

  const QVariant & id() const;

  const QString & name() const;

signals:

public slots:
  void setId( QVariant value );

  void setName( QString value );

private:
  StructAbstractSimpleObject m__StructAbstractSimpleObject;
};

#endif // ABSTRACTSIMPLEOBJECT_H
