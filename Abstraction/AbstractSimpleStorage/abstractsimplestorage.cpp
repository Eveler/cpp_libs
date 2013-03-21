#include "abstractsimplestorage.h"

AbstractSimpleStorage::AbstractSimpleStorage(QObject *parent) :
  QObject(parent)
{
}

AbstractSimpleStorage::~AbstractSimpleStorage()
{
}

AbstractSimpleObject * AbstractSimpleStorage::addObject( QVariant id )
{
  QList<AbstractSimpleObject *> objs = find( objects(), id );
  if ( !objs.isEmpty() ) return objs.first();
  else
  {
    AbstractSimpleObject *obj = new AbstractSimpleObject( id, this );
    connect( obj, SIGNAL(destroyed(QObject*)), SLOT(objectDestroyed(QObject*)) );
    m__Objects << obj;
    return obj;
  }
}

const QList<AbstractSimpleObject *> & AbstractSimpleStorage::objects() const
{
  return m__Objects;
}

QList<AbstractSimpleObject *> AbstractSimpleStorage::find(
    QList<AbstractSimpleObject *> objs, QVariant id ) const
{
  QList<AbstractSimpleObject *> result = QList<AbstractSimpleObject *>();

  foreach ( AbstractSimpleObject *obj, objs )
    if ( obj->id() == id ) result << obj;

  return result;
}

QList<AbstractSimpleObject *> AbstractSimpleStorage::find(
    QList<AbstractSimpleObject *> objs, QString name,
    Qt::MatchFlag flag, Qt::CaseSensitivity cs) const
{
  QList<AbstractSimpleObject *> result = QList<AbstractSimpleObject *>();

  if ( flag == Qt::MatchStartsWith )
  {
    foreach ( AbstractSimpleObject *obj, objs )
      if ( obj->name().startsWith( name, cs ) ) result << obj;
  }
  else if ( flag == Qt::MatchFixedString && cs == Qt::CaseSensitive )
  {
    foreach ( AbstractSimpleObject *obj, objs )
      if ( obj->name() == name ) result << obj;
  }
  else if ( flag == Qt::MatchFixedString && cs == Qt::CaseInsensitive )
  {
    foreach ( AbstractSimpleObject *obj, objs )
      if ( obj->name().toUpper() == name.toUpper() ) result << obj;
  }
  else if ( flag == Qt::MatchEndsWith )
  {
    foreach ( AbstractSimpleObject *obj, objs )
      if ( obj->name().endsWith( name, cs ) ) result << obj;
  }

  return result;
}

void AbstractSimpleStorage::objectDestroyed( QObject *obj )
{
  AbstractSimpleObject *ob = (AbstractSimpleObject *)obj;
  m__Objects.removeOne( ob );
}

