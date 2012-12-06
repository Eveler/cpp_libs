#include "notificationsstorage.h"

#include "usersstorage.h"

NotificationsStorage::NotificationsStorage(QObject *parent) :
  QObject(parent)
{
  reset();
}

NotificationsStorage::~NotificationsStorage()
{
  reset();
}

bool NotificationsStorage::setStorage( StorageItemModel *stor, StructNotificationCols cols )
{
  if ( m__Storage != NULL )
    storageDestroyed();

  if ( stor == NULL )
  {
    reset();

    return true;
  }

  if ( stor->findColumnByRealName( stor->getPropertiesView(), cols.Id ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.Created ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.CreatorId ) == -1 )
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

StorageItemModel * NotificationsStorage::storage() const
{
  return m__Storage;
}

const QList<Notification *> & NotificationsStorage::objects() const
{
  return m__Objects;
}

QList<Notification *> NotificationsStorage::find( QVariant id ) const
{
  return pFind( id, objects() );
}

QList<Notification *> NotificationsStorage::find(
    QString name, Qt::MatchFlag flag, Qt::CaseSensitivity cs ) const
{
  return pFind( name, flag, cs, objects() );
}

QList<Notification *> NotificationsStorage::find(
    QVariant id, QString name, Qt::MatchFlag flag, Qt::CaseSensitivity cs ) const
{
  return pFind( name, flag, cs, pFind( id, objects() ) );
}

void NotificationsStorage::reset()
{
  m__Storage = NULL;
  m__Cols.Id.clear();
  m__Cols.Created.clear();
  m__Cols.CreatorId.clear();
}

void NotificationsStorage::setObjectData( Notification *obj, MFCRecord *record )
{
  obj->setId( record->currentProperty( m__Cols.Id ) );
  obj->setCreated( record->currentProperty( m__Cols.Created ).toDateTime() );

  QList<User *> users = UsersStorage::instance()->findById(
        record->currentProperty( m__Cols.CreatorId ), objects() );
  if ( users.count() > 0 ) obj->setCreator( users.first() );
  else obj->setCreator( NULL );
}

QList<Notification *> NotificationsStorage::pFind(
    QVariant id, QList<Notification *> objs ) const
{
  QList<Notification *> result = QList<Notification *>();

  foreach ( Notification *obj, objs )
    if ( obj->id() == id ) result << obj;

  return result;
}

QList<Notification *> NotificationsStorage::pFind(
    QString name, Qt::MatchFlag flag, Qt::CaseSensitivity cs, QList<Notification *> objs ) const
{
  QList<Notification *> result = QList<Notification *>();

  if ( flag == Qt::MatchStartsWith )
  {
    foreach ( Notification *obj, objs )
      if ( obj->name().startsWith( name, cs ) ) result << obj;
  }
  else if ( flag == Qt::MatchFixedString && cs == Qt::CaseSensitive )
  {
    foreach ( Notification *obj, objects() )
      if ( obj->name() == name ) result << obj;
  }
  else if ( flag == Qt::MatchFixedString && cs == Qt::CaseInsensitive )
  {
    foreach ( Notification *obj, objects() )
      if ( obj->name().toUpper() == name.toUpper() ) result << obj;
  }
  else if ( flag == Qt::MatchEndsWith )
  {
    foreach ( Notification *obj, objects() )
      if ( obj->name().endsWith( name, cs ) ) result << obj;
  }

  return result;
}

void NotificationsStorage::storageDestroyed()
{
  disconnect( this, SLOT(storageDestroyed()) );
  disconnect( this, SLOT(recordAdded(MFCRecord*,int)) );
  disconnect( this, SLOT(recordRemoved(MFCRecord*,int)) );
  disconnect( this, SLOT(propertyChanged(QString,QVariant)) );
}


void NotificationsStorage::recordAdded( MFCRecord *record, int index )
{
  Notification *obj = new Notification( this );
  setObjectData( obj, record );
  m__Objects.insert( index, obj );
}

void NotificationsStorage::recordRemoved( MFCRecord */*record*/, int index )
{
  Notification *obj = m__Objects.takeAt( index );
  delete obj;
}

void NotificationsStorage::disconnectRecord( MFCRecord *record, int /*index*/ )
{
  disconnect( record, SIGNAL(propertyChanged(QString)),
              this, SLOT(propertyChanged(QString)) );
}

void NotificationsStorage::propertyChanged( QString column )
{
  if ( column != m__Cols.Id && column != m__Cols.Name ) return;

  MFCRecord *record = qobject_cast<MFCRecord *>( sender() );
  int index = m__Storage->availableRecords().indexOf( record );
  Notification *obj = objects()[index];
  setObjectData( obj, record );
}
