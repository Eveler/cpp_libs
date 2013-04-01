#ifndef GROUPSSTORAGE_H
#define GROUPSSTORAGE_H

#include "abstractsimplestorage.h"

#include "group.h"


class EXPORT_GROUP GroupsStorage : public AbstractSimpleStorage
{
  Q_OBJECT


public:
  static GroupsStorage * instance();

  const GroupList & groups() const;

  AbstractSimpleObjectList findByName( const AbstractSimpleObjectList &objects, QString name );
  AbstractSimpleObjectList findByParent( const AbstractSimpleObjectList &objects, Group *parentGroup );
  AbstractSimpleObjectList findByChild( const AbstractSimpleObjectList &objects, Group *childGroup );


signals:


public slots:


protected:
  AbstractSimpleObject * createObject( QVariant id );


private:
  static GroupsStorage * m__Instance;

  explicit GroupsStorage(QObject *parent = 0);
};

#endif // GROUPSSTORAGE_H
