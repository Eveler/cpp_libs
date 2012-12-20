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
  ~AbstractSimpleObject();

  const QVariant & id() const;
  const QString & name() const;

signals:
  void changedName( QString value );

public slots:
  void clear();

  void setId( QVariant value );
  void setName( QString value );

private:
  StructAbstractSimpleObject m__Value;
};

#endif // ABSTRACTSIMPLEOBJECT_H
