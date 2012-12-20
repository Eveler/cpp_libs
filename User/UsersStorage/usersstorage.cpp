#include "usersstorage.h"

#include "postsstorage.h"
#include "departmentsstorage.h"
#include "officesstorage.h"

UsersStorage *UsersStorage::m__Instance = NULL;

UsersStorage * UsersStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new UsersStorage;

  return m__Instance;
}

bool UsersStorage::setStorage( StorageItemModel *stor, StructUserCols cols )
{
  if ( m__Storage != NULL )
    storageDestroyed();

  if ( stor == NULL )
  {
    reset();

    return true;
  }

  if ( stor->findColumnByRealName( stor->getPropertiesView(), cols.cId ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.Surname ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.Firstname ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.Lastname ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.PostId ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.DepartmentId ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.Active ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.Dismissed ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.OfficeId ) == -1 )
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

StorageItemModel * UsersStorage::storage() const
{
  return m__Storage;
}

const QList<User *> & UsersStorage::objects() const
{
  return m__Users;
}

QList<User *> UsersStorage::findById( QList<User *> objs, QVariant value ) const
{
  QList<User *> result = QList<User *>();

  foreach ( User *user, objs )
    if ( user->id() == value ) result << user;

  return result;
}

QList<User *> UsersStorage::findByName( QList<User *> objs, StructName value ) const
{
  QList<User *> result = QList<User *>();

  foreach ( User *user, objs )
    if ( user->name().surname == value.surname &&
         user->name().firstname == value.firstname &&
         user->name().lastname == value.lastname )
      result << user;

  return result;
}

QList<User *> UsersStorage::findByPost( QList<User *> objs, AbstractSimpleObject *value ) const
{
  QList<User *> result = QList<User *>();

  foreach ( User *user, objs )
    if ( user->post() == value ) result << user;

  return result;
}

QList<User *> UsersStorage::findByDepartment( QList<User *> objs, AbstractSimpleObject *value ) const
{
  QList<User *> result = QList<User *>();

  foreach ( User *user, objs )
    if ( user->department() == value ) result << user;

  return result;
}

QList<User *> UsersStorage::findByActive( QList<User *> objs, bool value ) const
{
  QList<User *> result = QList<User *>();

  foreach ( User *user, objs )
    if ( user->active() == value ) result << user;

  return result;
}

QList<User *> UsersStorage::findByDismissed( QList<User *> objs, bool value ) const
{
  QList<User *> result = QList<User *>();

  foreach ( User *user, objs )
    if ( user->dismissed() == value ) result << user;

  return result;
}

QList<User *> UsersStorage::findByOffice( QList<User *> objs, AbstractSimpleObject *value ) const
{
  QList<User *> result = QList<User *>();

  foreach ( User *user, objs )
    if ( user->office() == value ) result << user;

  return result;
}

UsersStorage::UsersStorage(QObject *parent) :
    QObject(parent)
{
  reset();
}

UsersStorage::~UsersStorage()
{
  reset();
}

void UsersStorage::reset()
{
  m__Storage = NULL;
  m__Cols.cId.clear();
  m__Cols.Surname.clear();
  m__Cols.Firstname.clear();
  m__Cols.Lastname.clear();
  m__Cols.PostId.clear();
  m__Cols.DepartmentId.clear();
  m__Cols.Active.clear();
  m__Cols.Dismissed.clear();
  m__Cols.OfficeId.clear();
}

void UsersStorage::setObjectData( User *obj, MFCRecord *record )
{
  obj->setId( record->currentProperty( m__Cols.cId ) );

  StructName name = {record->currentProperty( m__Cols.Surname ).toString(),
                     record->currentProperty( m__Cols.Firstname ).toString(),
                     record->currentProperty( m__Cols.Lastname ).toString()};
  obj->setName( name );

  QList<AbstractSimpleObject *> posts = PostsStorage::instance()->find(
        PostsStorage::instance()->objects(),
        record->currentProperty( m__Cols.PostId ) );
  if ( posts.count() > 0 ) obj->setPost( posts.first() );
  else obj->setPost( NULL );

  QList<AbstractSimpleObject *> departments = DepartmentsStorage::instance()->find(
        DepartmentsStorage::instance()->objects(),
        record->currentProperty( m__Cols.DepartmentId ) );
  if ( departments.count() > 0 ) obj->setDepartment( departments.first() );
  else obj->setDepartment( NULL );

  obj->setActive( record->currentProperty( m__Cols.Active ).toBool() );

  obj->setDismissed( record->currentProperty( m__Cols.Dismissed ).toBool() );

  QList<AbstractSimpleObject *> offices = OfficesStorage::instance()->find(
        OfficesStorage::instance()->objects(),
        record->currentProperty( m__Cols.OfficeId ) );
  if ( offices.count() > 0 ) obj->setOffice( offices.first() );
  else obj->setOffice( NULL );
}

void UsersStorage::storageDestroyed()
{
  disconnect( this, SLOT(storageDestroyed()) );
  disconnect( this, SLOT(recordAdded(MFCRecord*,int)) );
  disconnect( this, SLOT(recordRemoved(MFCRecord*,int)) );
  disconnect( this, SLOT(propertyChanged(QString,QVariant)) );
}

void UsersStorage::recordAdded( MFCRecord *record, int index )
{
  User *user = new User( this );
  setObjectData( user, record );
  m__Users.insert( index, user );
}

void UsersStorage::recordRemoved( MFCRecord */*record*/, int index )
{
  m__Users.removeAt( index );
}

void UsersStorage::disconnectRecord( MFCRecord *record, int )
{
  disconnect( record, SIGNAL(propertyChanged(QString)),
              this, SLOT(propertyChanged(QString)) );
}

void UsersStorage::propertyChanged( QString column )
{
  if ( column != m__Cols.cId && column != m__Cols.Surname &&
       column != m__Cols.Firstname && column != m__Cols.Lastname &&
       column != m__Cols.PostId && column != m__Cols.DepartmentId &&
       column != m__Cols.Active && column != m__Cols.Dismissed &&
       column != m__Cols.OfficeId )
    return;

  MFCRecord *record = qobject_cast<MFCRecord *>( sender() );
  int index = m__Storage->availableRecords().indexOf( record );
  User *obj = objects()[index];
  setObjectData( obj, record );
}
