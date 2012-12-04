#include "abstractsimplestorage.h"

AbstractSimpleStorage::AbstractSimpleStorage(QObject *parent) :
  QObject(parent)
{
  reset();
}

AbstractSimpleStorage::~AbstractSimpleStorage()
{
  reset();
}

bool AbstractSimpleStorage::setStorage( StorageItemModel *stor, StructASSCols cols )
{
  if ( m__Storage != NULL )
    storageDestroyed();

  if ( stor == NULL )
  {
    reset();

    return true;
  }

  if ( stor->findColumnByRealName( stor->getPropertiesView(), cols.Id ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.Name ) == -1 )
    return false;

  m__Storage = stor;
  m__Cols = cols;

  connect( stor, SIGNAL(destroyed()),
           this, SLOT(storageDestroyed()) );
  connect( stor, SIGNAL(recordAdded(MFCRecord*,int)),
           this, SLOT(recordAdded(MFCRecord*,int)) );
  connect( stor, SIGNAL(recordRemoved(MFCRecord*,int)),
           this, SLOT(recordRemoved(MFCRecord*,int)) );
  connect( stor, SIGNAL(recordRemoved(MFCRecord*,int)),
           this, SLOT(disconnectRecord(MFCRecord*,int)) );

  for ( int rIdx = 0; rIdx < stor->availableRecords().count(); rIdx++ )
  {
    MFCRecord *record = stor->availableRecords()[rIdx];
    connect( record, SIGNAL(propertyChanged(QString)),
             this, SLOT(propertyChanged(QString)) );
    recordAdded( record, rIdx );
  }

  return true;
}

StorageItemModel * AbstractSimpleStorage::storage() const
{
  return m__Storage;
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

void AbstractSimpleStorage::reset()
{
  m__Storage = NULL;
  m__Cols.Id.clear();
  m__Cols.Name.clear();
}

void AbstractSimpleStorage::setObjectData( AbstractSimpleObject *obj, MFCRecord *record )
{
  obj->setId( record->currentProperty( m__Cols.Id ) );
  obj->setName( record->currentProperty( m__Cols.Name ).toString() );
}

void AbstractSimpleStorage::storageDestroyed()
{
  disconnect( this, SLOT(storageDestroyed()) );
  disconnect( this, SLOT(recordAdded(MFCRecord*,int)) );
  disconnect( this, SLOT(recordRemoved(MFCRecord*,int)) );
  disconnect( this, SLOT(propertyChanged(QString,QVariant)) );
}


void AbstractSimpleStorage::recordAdded( MFCRecord *record, int index )
{
  AbstractSimpleObject *obj = new AbstractSimpleObject( this );
  setObjectData( obj, record );
  m__Objects.insert( index, obj );
}

void AbstractSimpleStorage::recordRemoved( MFCRecord */*record*/, int index )
{
  AbstractSimpleObject *obj = m__Objects.takeAt( index );
  delete obj;
}

void AbstractSimpleStorage::disconnectRecord( MFCRecord *record, int /*index*/ )
{
  disconnect( record, SIGNAL(propertyChanged(QString)),
              this, SLOT(propertyChanged(QString)) );
}

void AbstractSimpleStorage::propertyChanged( QString column )
{
  if ( column != m__Cols.Id && column != m__Cols.Name ) return;

  MFCRecord *record = qobject_cast<MFCRecord *>( sender() );
  int index = m__Storage->availableRecords().indexOf( record );
  AbstractSimpleObject *obj = objects()[index];
  setObjectData( obj, record );
}
