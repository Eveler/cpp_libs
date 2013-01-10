#include "abbreviationsstorage.h"

AbbreviationsStorage *AbbreviationsStorage::m__Instance = NULL;

AbbreviationsStorage * AbbreviationsStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new AbbreviationsStorage;

  return m__Instance;
}

bool AbbreviationsStorage::setStorage( StorageItemModel *stor, StructAbbreviationCols cols )
{
  if ( m__Storage != NULL )
    storageDestroyed();

  if ( stor == NULL )
  {
    reset();

    return true;
  }

  if ( stor->findColumnByRealName( stor->getPropertiesView(), cols.Id ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.cShortName ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), cols.cFullName ) )
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

StorageItemModel * AbbreviationsStorage::storage() const
{
  return m__Storage;
}

const QList<Abbreviation *> & AbbreviationsStorage::objects() const
{
  return m__Abbreviations;
}

QList<Abbreviation *> AbbreviationsStorage::findById( QList<Abbreviation *> objs, QVariant value ) const
{
  QList<Abbreviation *> result = QList<Abbreviation *>();

  foreach ( Abbreviation *obj, objs )
    if ( obj->id() == value ) result << obj;

  return result;
}

AbbreviationsStorage::AbbreviationsStorage(QObject *parent) :
    QObject(parent)
{
  reset();
}

AbbreviationsStorage::~AbbreviationsStorage()
{
  reset();
}

void AbbreviationsStorage::reset()
{
  m__Storage = NULL;
  m__Cols.Id.clear();
  m__Cols.cShortName.clear();
  m__Cols.cFullName.clear();
}

void AbbreviationsStorage::setObjectData( Abbreviation *obj, MFCRecord *record )
{
  obj->setId( record->currentProperty( m__Cols.Id ) );
  obj->setShortName( record->currentProperty( m__Cols.cShortName ).toString() );
  obj->setFullName( record->currentProperty( m__Cols.cFullName ).toString() );
}

void AbbreviationsStorage::storageDestroyed()
{
  disconnect( this, SLOT(storageDestroyed()) );
  disconnect( this, SLOT(recordAdded(MFCRecord*,int)) );
  disconnect( this, SLOT(recordRemoved(MFCRecord*,int)) );
  disconnect( this, SLOT(propertyChanged(QString,QVariant)) );
}

void AbbreviationsStorage::recordAdded( MFCRecord *record, int index )
{
  Abbreviation *abbreviation = new Abbreviation( this );
  setObjectData( abbreviation, record );
  m__Abbreviations.insert( index, abbreviation );
  connect( abbreviation, SIGNAL(changedShortName(QString)),
           this, SLOT(changedShortName(QString)) );
  connect( abbreviation, SIGNAL(changedFullName(QString)),
           this, SLOT(changedFullName(QString)) );
}

void AbbreviationsStorage::recordRemoved( MFCRecord */*record*/, int index )
{
  m__Abbreviations.removeAt( index );
}

void AbbreviationsStorage::disconnectRecord( MFCRecord *record, int )
{
  disconnect( record, SIGNAL(propertyChanged(QString)),
              this, SLOT(propertyChanged(QString)) );
}

void AbbreviationsStorage::propertyChanged( QString column )
{
  if ( column != m__Cols.Id && column != m__Cols.cShortName &&
       column != m__Cols.cFullName )
    return;

  MFCRecord *record = qobject_cast<MFCRecord *>( sender() );
  int index = m__Storage->availableRecords().indexOf( record );
  Abbreviation *obj = objects()[index];
  setObjectData( obj, record );
}

void AbbreviationsStorage::changedShortName( QString value )
{
  Abbreviation *obj = qobject_cast<Abbreviation *>( sender() );

  m__Storage->availableRecords()[objects().indexOf( obj )]->setCurrentProperty(
        m__Cols.cShortName, value );
}

void AbbreviationsStorage::changedFullName( QString value )
{
  Abbreviation *obj = qobject_cast<Abbreviation *>( sender() );

  m__Storage->availableRecords()[objects().indexOf( obj )]->setCurrentProperty(
        m__Cols.cFullName, value );
}
