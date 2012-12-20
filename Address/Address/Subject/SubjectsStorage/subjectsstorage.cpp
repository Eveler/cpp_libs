#include "subjectsstorage.h"

#include "abbreviationsstorage.h"

SubjectsStorage *SubjectsStorage::m__Instance = NULL;

SubjectsStorage * SubjectsStorage::instance()
{
  if ( m__Instance == NULL ) m__Instance = new SubjectsStorage;

  return m__Instance;
}

bool SubjectsStorage::setStorage( StorageItemModel *stor, StructSubjectCols cols )
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

StorageItemModel * SubjectsStorage::storage() const
{
  return m__Storage;
}

const QList<Subject *> & SubjectsStorage::objects() const
{
  return m__Subjects;
}

QList<Subject *> SubjectsStorage::findById( QList<Subject *> objs, QVariant value ) const
{
  QList<Subject *> result = QList<Subject *>();

  foreach ( Subject *obj, objs )
    if ( obj->id() == value ) result << obj;

  return result;
}

SubjectsStorage::SubjectsStorage(QObject *parent) :
    QObject(parent)
{
  reset();
}

SubjectsStorage::~SubjectsStorage()
{
  reset();
}

void SubjectsStorage::reset()
{
  m__Storage = NULL;
  m__Cols.cId.clear();
  m__Cols.cAbbreviation.clear();
  m__Cols.cName.clear();
}

void SubjectsStorage::setObjectData( Subject *obj, MFCRecord *record )
{
  obj->setId( record->currentProperty( m__Cols.cId ) );
  AbbreviationsStorage *abbreviationsStorage = AbbreviationsStorage::instance();
  QList<Abbreviation *> abbreviations = abbreviationsStorage->findById(
        abbreviationsStorage->objects(), record->currentProperty( m__Cols.cAbbreviation ) );
  if ( !abbreviations.isEmpty() ) obj->setAbbreviation( abbreviations.first() );
  obj->setName( record->currentProperty( m__Cols.cName ).toString() );
}

void SubjectsStorage::storageDestroyed()
{
  disconnect( this, SLOT(storageDestroyed()) );
  disconnect( this, SLOT(recordAdded(MFCRecord*,int)) );
  disconnect( this, SLOT(recordRemoved(MFCRecord*,int)) );
  disconnect( this, SLOT(propertyChanged(QString,QVariant)) );
}

void SubjectsStorage::recordAdded( MFCRecord *record, int index )
{
  Subject *subject = new Subject( this );
  setObjectData( subject, record );
  m__Subjects.insert( index, subject );
  connect( subject, SIGNAL(changedAbbreviation(Abbreviation*)),
           this, SLOT(changedAbbreviation(Abbreviation*)) );
  connect( subject, SIGNAL(changedName(QString)), this, SLOT(changedName(QString)) );
}

void SubjectsStorage::recordRemoved( MFCRecord */*record*/, int index )
{
  m__Subjects.removeAt( index );
}

void SubjectsStorage::disconnectRecord( MFCRecord *record, int )
{
  disconnect( record, SIGNAL(propertyChanged(QString)),
              this, SLOT(propertyChanged(QString)) );
}

void SubjectsStorage::propertyChanged( QString column )
{
  if ( column != m__Cols.cId && column != m__Cols.cAbbreviation &&
       column != m__Cols.cName )
    return;

  MFCRecord *record = qobject_cast<MFCRecord *>( sender() );
  int index = m__Storage->availableRecords().indexOf( record );
  Subject *obj = objects()[index];
  setObjectData( obj, record );
}

void SubjectsStorage::changedAbbreviation( Abbreviation *value )
{
  Subject *obj = qobject_cast<Subject *>( sender() );

  m__Storage->availableRecords()[objects().indexOf( obj )]->setCurrentProperty(
        m__Cols.cAbbreviation, value->id() );
}

void SubjectsStorage::changedName( QString value )
{
  Subject *obj = qobject_cast<Subject *>( sender() );

  m__Storage->availableRecords()[objects().indexOf( obj )]->setCurrentProperty(
        m__Cols.cName, value );
}
