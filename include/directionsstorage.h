#ifndef DIRECTIONSSTORAGE_H
#define DIRECTIONSSTORAGE_H

#include "abstractsimplestorage.h"

#include "direction.h"


class EXPORT_DIRECTION DirectionsStorage : public AbstractSimpleStorage
{
  Q_OBJECT


public:
  static DirectionsStorage * instance();

  const DirectionList & Directions() const;

  AbstractSimpleObjectList findByName( const AbstractSimpleObjectList &objects, QString name );
  AbstractSimpleObjectList findByParent(
      const AbstractSimpleObjectList &objects, Direction *parentDirection );
  AbstractSimpleObjectList findByChild(
      const AbstractSimpleObjectList &objects, Direction *childDirection );


signals:


public slots:


protected:
  AbstractSimpleObject * createObject( QVariant id );


private:
  static DirectionsStorage * m__Instance;

  explicit DirectionsStorage(QObject *parent = 0);
};

#endif // DIRECTIONSSTORAGE_H
