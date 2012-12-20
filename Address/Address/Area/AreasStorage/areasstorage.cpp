#include "areasstorage.h"

#include "abbreviationsstorage.h"

AreasStorage *AreasStorage::m__Instance = NULL;

AreasStorage * AreasStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new AreasStorage;

  return m__Instance;
}

bool AreasStorage::setStorage( StorageItemModel *stor, StructAreaCols cols )
{
  if ( m__Storage != NULL )
    storageDestroyed();

  if ( stor == NULL )
  {
    reset();

    return true;
  }

  if ( stor->findColumnByRealName( stor->getPropertiesView(), cols.cId ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.cAbbreviation ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.cName ) == -1 )
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

StorageItemModel * AreasStorage::storage() const
{
  return m__Storage;
}

const QList<Area *> & AreasStorage::objects() const
{
  return m__Areas;
}

QList<Area *> AreasStorage::findById( QList<Area *> objs, QVariant value ) const
{
  QList<Area *> result = QList<Area *>();

  foreach ( Area *obj, objs )
    if ( obj->id() == value ) result << obj;

  return result;
}

AreasStorage::AreasStorage(QObject *parent) :
    QObject(parent)
{
  reset();
}

AreasStorage::~AreasStorage()
{
  reset();
}

void AreasStorage::reset()
{
  m__Storage = NULL;
  m__Cols.cId.clear();
  m__Cols.cAbbreviation.clear();
  m__Cols.cName.clear();
}

void AreasStorage::setObjectData( Area *obj, MFCRecord *record )
{
  obj->setId( record->currentProperty( m__Cols.cId ) );
  AbbreviationsStorage *abbreviationsStorage = AbbreviationsStorage::instance();
  QList<Abbreviation *> abbreviations = abbreviationsStorage->findById(
        abbreviationsStorage->objects(), record->currentProperty( m__Cols.cAbbreviation ) );
  if ( !abbreviations.isEmpty() ) obj->setAbbreviation( abbreviations.first() );
  obj->setName( record->currentProperty( m__Cols.cName ).toString() );
}

void AreasStorage::storageDestroyed()
{
  disconnect( this, SLOT(storageDestroyed()) );
  disconnect( this, SLOT(recordAdded(MFCRecord*,int)) );
  disconnect( this, SLOT(recordRemoved(MFCRecord*,int)) );
  disconnect( this, SLOT(propertyChanged(QString,QVariant)) );
}

void AreasStorage::recordAdded( MFCRecord *record, int index )
{
  Area *area = new Area( this );
  setObjectData( area, record );
  m__Areas.insert( index, area );
  connect( area, SIGNAL(changedAbbreviation(Abbreviation*)),
           this, SLOT(changedAbbreviation(Abbreviation*)) );
  connect( area, SIGNAL(changedName(QString)), this, SLOT(changedName(QString)) );
}

void AreasStorage::recordRemoved( MFCRecord */*record*/, int index )
{
  m__Areas.removeAt( index );
}

void AreasStorage::disconnectRecord( MFCRecord *record, int )
{
  disconnect( record, SIGNAL(propertyChanged(QString)),
              this, SLOT(propertyChanged(QString)) );
}

void AreasStorage::propertyChanged( QString column )
{
  if ( column != m__Cols.cId && column != m__Cols.cAbbreviation &&
       column != m__Cols.cName )
    return;

  MFCRecord *record = qobject_cast<MFCRecord *>( sender() );
  int index = m__Storage->availableRecords().indexOf( record );
  Area *obj = objects()[index];
  setObjectData( obj, record );
}

void AreasStorage::changedAbbreviation( Abbreviation *value )
{
  Area *obj = qobject_cast<Area *>( sender() );

  m__Storage->availableRecords()[objects().indexOf( obj )]->setCurrentProperty(
        m__Cols.cAbbreviation, value->id() );
}

void AreasStorage::changedName( QString value )
{
  Area *obj = qobject_cast<Area *>( sender() );

  m__Storage->availableRecords()[objects().indexOf( obj )]->setCurrentProperty(
        m__Cols.cName, value );
}
