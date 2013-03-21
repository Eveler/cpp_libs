#ifndef ABSTRACTSIMPLESTORAGE_H
#define ABSTRACTSIMPLESTORAGE_H

#include "abstractsimpleobject.h"


class EXPORT AbstractSimpleStorage : public QObject
{
  Q_OBJECT


public:
  explicit AbstractSimpleStorage(QObject *parent = 0);
  ~AbstractSimpleStorage();

  AbstractSimpleObject * addObject( QVariant id );

  const QList<AbstractSimpleObject *> & objects() const;

  QList<AbstractSimpleObject *> find(
      QList<AbstractSimpleObject *> objs, QVariant id ) const;
  QList<AbstractSimpleObject *> find(
      QList<AbstractSimpleObject *> objs, QString name,
      Qt::MatchFlag flag = Qt::MatchFixedString,
      Qt::CaseSensitivity cs = Qt::CaseSensitive ) const;


signals:


public slots:


private:
  QList<AbstractSimpleObject *> m__Objects;


private slots:
  void objectDestroyed( QObject *obj );
};

#endif // ABSTRACTSIMPLESTORAGE_H
