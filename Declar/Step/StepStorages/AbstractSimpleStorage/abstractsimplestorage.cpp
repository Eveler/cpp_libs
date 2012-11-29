#include "abstractsimplestorage.h"

AbstractSimpleStorage::AbstractSimpleStorage(QObject *parent) :
  QObject(parent)
{
  m__Storage = NULL;
  m__ColName_Id = QString();
  m__ColName_Name = QString();
}

AbstractSimpleStorage::~AbstractSimpleStorage()
{
  m__Storage = NULL;
  m__ColName_Id.clear();
  m__ColName_Name.clear();
}

bool AbstractSimpleStorage::setStorage( StorageItemModel *stor, QString colName_Id, QString colName_Name )
{
  if ( m__Storage != NULL )
    storageDestroyed();

  if ( stor == NULL )
  {
    m__Storage = NULL;
    m__ColName_Id = QString();
    m__ColName_Name = QString();

    return true;
  }

  if ( stor->findColumnByRealName( stor->getPropertiesView(), colName_Id ) == -1 ||
       stor->findColumnByRealName( stor->getPropertiesView(), colName_Name ) == -1 )
    return false;

  m__Storage = stor;
  m__ColName_Id = colName_Id;
  m__ColName_Name = colName_Name;

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

StorageItemModel * AbstractSimpleStorage::storage()
{
  return m__Storage;
}

void AbstractSimpleStorage::storageDestroyed()
{
  disconnect( this, SLOT(storageDestroyed()) );
  disconnect( this, SLOT(recordAdded(MFCRecord*,int)) );
  disconnect( this, SLOT(recordRemoved(MFCRecord*,int)) );
  disconnect( this, SLOT(propertyChanged(QString,QVariant)) );
}

void AbstractSimpleStorage::disconnectRecord( MFCRecord *record, int /*index*/ )
{
  disconnect( record, SIGNAL(propertyChanged(QString)),
              this, SLOT(propertyChanged(QString)) );
}

void AbstractSimpleStorage::propertyChanged( QString column )
{
  if ( column != m__ColName_Id && column != m__ColName_Name ) return;

  MFCRecord *record = qobject_cast<MFCRecord *>( sender() );
  int index = m__Storage->availableRecords().indexOf( record );
  AbstractSimpleObject *obj = objects()[index];
  setObjectData( obj, record );
}
