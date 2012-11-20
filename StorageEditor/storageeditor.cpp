#include "storageeditor.h"

#include <QDebug>
#include <QApplication>

StorageEditor *StorageEditor::nullEditor = new StorageEditor();
QHash<QString, StorageEditor *> StorageEditor::m_Editors = QHash<QString, StorageEditor *>();


StorageEditor * StorageEditor::instance(
    const QString &alias, const QString &connectionName,
    const QString &propertiesView, QString filter, SortParams *sort )
{
  QSqlDatabase db = QSqlDatabase::database( connectionName );
  PropertiesView *pv = PropertiesView::getPropertiesView( propertiesView );
  if ( alias.simplified().isEmpty() || !db.isValid() || pv->isNull() ) return nullEditor;

  StorageEditor *editor = 0;
  if ( m_Editors.contains( alias ) ) editor = m_Editors[alias];
  else
  {
    editor = new StorageEditor(
          alias, db, pv, filter, ( sort != 0 && sort->propertiesView() == pv ? sort : 0 ) );
    m_Editors.insert( alias, editor );
  }

  return editor;
}

StorageEditor * StorageEditor::getStorage( const QString &alias )
{
  if ( m_Editors.contains( alias ) ) return m_Editors[alias];
  else return nullEditor;
}

bool StorageEditor::releaseAll()
{
  foreach ( QString alias, m_Editors.keys() )
  {
    StorageEditor *editor = m_Editors.take( alias );
    delete editor;
  }

  return true;
}

bool StorageEditor::release( StorageEditor *editor )
{
  if ( editor == NULL || editor->isNull() ) return false;

  m_Editors.remove( editor->alias() );

  delete editor;

  return true;
}

QStringList StorageEditor::notAvailableStorages( QStringList aliases )
{
  QStringList result = QStringList();

  foreach ( QString storageAlias, aliases )
    if ( StorageEditor::getStorage( storageAlias )->isNull() )
      result << storageAlias;

  return result;
}

bool StorageEditor::isNull() const
{
  return m_Alias->isEmpty();
}

const QString & StorageEditor::alias() const
{
  return (*m_Alias);
}

StorageItemModel * StorageEditor::storage() const
{
  return m_Storage;
}

void StorageEditor::showLoadLog( bool show )
{
  m_ShowLoadLog = show;
}

void StorageEditor::setSqlFilter( QString text )
{
  m_Filter = text;
}

void StorageEditor::load()
{
//  qDebug() << "m_KeyField" << m_KeyField;
  QString keyField = PropertiesSqlWorker::preparePsName( m_KeyField );
  QString p_Name = m_KeyField;
  if ( keyField.isEmpty() )
  {
    keyField = PropertiesSqlWorker::preparePsName(
          m_Storage->getPropertiesView()->root()->propertyNames().first() );
    p_Name = m_Storage->getPropertiesView()->root()->propertyNames().first();
  }
//  qDebug() << "p_Name" << p_Name;

  QStringList ids_minus = QStringList();
  foreach ( MFCRecord *record, m_Storage->availableRecords() )
    ids_minus << record->currentProperty( p_Name ).toString();

  if ( !unloadRecords( ids_minus, p_Name ) )
  {
    qDebug() << tr( "unloadRecords fail!" );
    qDebug() << tr( "PropertiesView alias [%1]" ).arg( m_Storage->getPropertiesView()->alias() );
  }

  QString filter = m_Filter;
  if ( !ids_minus.isEmpty() )
    filter += ( filter.isEmpty() ? "" : tr( " AND " ) )+
        tr( "%1 in (%2)" ).arg( keyField, ids_minus.join( "," ) );
  if ( !updateRecords( filter, p_Name ) )
  {
    qDebug() << tr( "updateRecords fail!" );
    qDebug() << tr( "PropertiesView alias [%1]" ).arg( m_Storage->getPropertiesView()->alias() );
  }

  filter = m_Filter;
  if ( !ids_minus.isEmpty() )
    filter += ( filter.isEmpty() ? "" : tr( " AND " ) )+
        tr( "NOT %1 in (%2)" ).arg( keyField, ids_minus.join( "," ) );
  if ( !loadRecords( m_Storage, filter ) )
  {
    qDebug() << tr( "loadRecords fail!" );
    qDebug() << tr( "PropertiesView alias [%1]" ).arg( m_Storage->getPropertiesView()->alias() );
  }

//  qDebug() << tr( "In %1 records count: [%2]" ).arg(
//            alias(), QString::number( m_Storage->rowCount() ) );
}

bool StorageEditor::setUnique( QStringList p_Names )
{
  foreach ( QString p_Name, p_Names )
    if ( !m_Storage->getPropertiesView()->root()->propertyNames().contains( p_Name ) ) return false;

  m_UniqueProperties.clear();
  m_UniqueProperties = p_Names;

  return true;
}

void StorageEditor::beginChanges()
{
  checkChanges = false;
}

QList<MFCRecord *> StorageEditor::changedRecords()
{
  return m_ChangedProperies.keys();
}

QList<MFCRecord *> StorageEditor::endChanges()
{
  QList<MFCRecord *> result = QList<MFCRecord *>();
  foreach ( MFCRecord *record, m_ChangedProperies.keys() )
  {
    ParamFilters filter;
    QStringList uFs = m_UniqueProperties;
    foreach ( QString p_Name, m_ChangedProperies[record] )
    {
      filter.setParam( record->propertiesView(), p_Name,
                       m_ChangedValues[qMakePair( record, p_Name )].second );
      uFs.removeOne( p_Name );
    }
    foreach ( QString p_Name,uFs )
      filter.setParam( record->propertiesView(), p_Name,
                       record->currentProperty( p_Name ) );

    QList<MFCRecord *> ret = m_Storage->findRecords( filter );
    bool hasItself = ret.contains( record );
//    qDebug() << hasItself << ret.count();
    if ( ( hasItself && ret.count() > 1 ) || ( !hasItself && ret.count() > 0 ) )
    {
      revert = record;
      foreach ( QString p_Name, m_ChangedProperies[record] )
        record->setCurrentProperty( p_Name, m_ChangedValues[qMakePair( record, p_Name )].first );
      qApp->processEvents();
      revert = 0;
    }
    else
    {
      result << record;
      if ( !m_PSW->saveChanges( record ).isValid() )
      {
        record->dataSync();
        m_ChangedRecords.removeOne( record );
      }
    }
  }

  m_ChangedProperies.clear();
  m_ChangedValues.clear();

  checkChanges = true;

  m_Storage->resort();

  return result;
}

void StorageEditor::setAutosaveOnAdd( bool enable )
{
  m_Autosave = enable;
}

bool StorageEditor::addRecord( MFCRecord *rootRecord )
{
  return addRecord( rootRecord, m_PSW, m_Autosave );
}

bool StorageEditor::addRecord( MFCRecord *rootRecord, PropertiesSqlWorker *psw, bool autoSave )
{
  if ( rootRecord == 0 || m_Storage->getPropertiesView()->root() != rootRecord->properties() ||
       psw == NULL || !psw->isValid() ) return false;
  bool canAdd = true;
  if ( !m_UniqueProperties.isEmpty() && !m_Storage->availableRecords().contains( rootRecord ) )
  {
    foreach ( MFCRecord *record, m_Storage->availableRecords() )
    {
      bool success = true;
      foreach ( QString p_Name, m_UniqueProperties )
        if ( record->currentProperty( p_Name ) != rootRecord->currentProperty( p_Name ) )
        {
          success = false;
          break;
        }
      if ( success )
      {
        canAdd = false;
        break;
      }
    }
  }

  if ( canAdd )
  {
    QSqlError err;
    nextVal( rootRecord, psw );
    if ( autoSave ) err = psw->saveRecord( rootRecord, true, false );
    if ( err.isValid() )
    {
      qDebug() << err.text() << err.type();
      return false;
    }
    else if ( m_Storage->appendRecord( rootRecord, !autoSave ) )
    {
      m_Storage->resort();
      return true;
    }
  }

  return false;
}

bool StorageEditor::setKeyField( QString keyField )
{
  if ( !m_Storage->getPropertiesView()->root()->propertyNames().contains( keyField ) )
    return false;

  m_KeyField = keyField;

  return true;
}

bool StorageEditor::save()
{
  return save( m_PSW );
}

bool StorageEditor::save( PropertiesSqlWorker *sqlWorker )
{
  if ( sqlWorker == NULL || !sqlWorker->isValid() )
  {
    qDebug() << "Saver is null or is not valid!";
    return false;
  }
  qDebug() << "StorageEditor::save BEGIN" << m_Storage->getPropertiesView()->alias();

//  return false;
  int changes = 0;
  int additions = 0;
  foreach ( MFCRecord *record, m_Storage->oldRecords() )
  {
    QSqlError err = sqlWorker->saveChanges( record );
    if ( err.isValid() )
    {
      qDebug() << err.text() << err.type();
      return false;
    }
    changes++;
  }

  while ( !m_Storage->newRecords().isEmpty() )
  {
    MFCRecord *record = m_Storage->newRecords().first();
    QSqlError err = sqlWorker->saveRecord( record, true, false );
    if ( err.isValid() )
    {
      qDebug() << err.text() << err.type();
      return false;
    }
    m_Storage->changeRecordMark( record, false );
    additions++;
  }

  qDebug() << tr( "StorageEditor::save END [changes=%1; additions=%2]" ).arg(
            QString::number( changes ), QString::number( additions ) );
  return true;
}

//StorageEditor::StorageEditor() :
//  QObject( 0 )
//{
//  m_Alias = new QString();
//  m_PSW = 0;
//  m_Storage = 0;

//  checkChanges = true;
//  m_ChangedProperies = QHash<MFCRecord *, QStringList>();
//  m_ChangedValues = QHash<QPair<MFCRecord *, QString>, QPair<QVariant, QVariant> >();
//  revert = 0;

//  error = QString();

//  m_Records = QHash<Properties *, QList<MFCRecord *> >();
//  m_UniqueProperties = QStringList();
//}

//StorageEditor::StorageEditor( const QString &alias, QSqlDatabase &db,
//                              PropertiesView *propertiesView , SortParams *sort ) :
//  QObject( 0 )
//{
//  m_Alias = new QString( alias );
//  m_DB = db;
//  m_PSW = &PropertiesSqlWorker::instance(
//        tr( "%1___%2" ).arg( metaObject()->className(),
//                             QDateTime::currentDateTime().toString(
//                               tr( "dd_MM_yy___hh_mm_ss_zzz" ) ) ), m_DB );
//  m_Storage = new StorageItemModel( propertiesView, this );
//  m_Storage->setSort( sort );
//  connect( m_Storage, SIGNAL(destroyed()), this, SLOT(storageDestroyed()) );
//  connect( m_Storage, SIGNAL(recordAdded(MFCRecord*)), this, SLOT(recordAdded(MFCRecord*)) );

//  checkChanges = true;
//  m_ChangedProperies = QHash<MFCRecord *, QStringList>();
//  m_ChangedValues = QHash<QPair<MFCRecord *, QString>, QPair<QVariant, QVariant> >();
//  revert = 0;

//  error = QString();

//  m_Records = QHash<Properties *, QList<MFCRecord *> >();
//  m_UniqueProperties = QStringList();

//  load();
//}

StorageEditor::StorageEditor() :
  QObject( 0 )
{
  m_Alias = new QString();
  m_PSW = 0;
  m_Storage = 0;

  checkChanges = true;
  m_ChangedProperies = QHash<MFCRecord *, QStringList>();
  m_ChangedValues = QHash<QPair<MFCRecord *, QString>, QPair<QVariant, QVariant> >();
  revert = 0;

  error = QString();

  m_Records = QHash<PropertiesView *, QList<MFCRecord *> >();
  m_UniqueProperties = QStringList();

  m_ShowLoadLog = false;
}

StorageEditor::StorageEditor( const QString &alias, QSqlDatabase &db,
                              PropertiesView *propertiesView, QString filter, SortParams *sort ) :
  QObject( 0 ),
  m_Filter( filter )
{
  m_Alias = new QString( alias );
  m_DB = db;
  m_PSW = &PropertiesSqlWorker::instance(
        tr( "%1___%2" ).arg( metaObject()->className(), alias ), m_DB );
  m_Storage = new StorageItemModel( propertiesView, this );
  m_Storage->setSort( sort );
  connect( m_Storage, SIGNAL(destroyed()), this, SLOT(storageDestroyed()) );
  connect( m_Storage, SIGNAL(recordAdded(MFCRecord*)), this, SLOT(recordAdded(MFCRecord*)) );

  checkChanges = true;
  m_ChangedRecords = QList<MFCRecord *>();
  m_ChangedProperies = QHash<MFCRecord *, QStringList>();
  m_ChangedValues = QHash<QPair<MFCRecord *, QString>, QPair<QVariant, QVariant> >();
  revert = 0;

  setAutosaveOnAdd( false );

  error = QString();

  m_Records = QHash<PropertiesView *, QList<MFCRecord *> >();
  m_UniqueProperties = QStringList();

  m_ShowLoadLog = false;
}

StorageEditor::~StorageEditor()
{
//  qDebug() << tr( "~StorageEditor [%1]" ).arg( (*m_Alias) ) << m_Storage;
  emit destroyed( (*m_Alias) );
  delete m_Alias;
  m_Alias = 0;

  m__AutoClearedStorage.clear();

  if ( m_Storage != 0 )
  {
    m_Storage->deleteContent();
    disconnect( m_Storage, SIGNAL(destroyed()), this, SLOT(storageDestroyed()) );
    disconnect( m_Storage, SIGNAL(recordAdded(MFCRecord*)), this, SLOT(recordAdded(MFCRecord*)) );
    delete m_Storage;
    m_Storage = 0;
  }

  PropertiesSqlWorker::remove( m_PSW->alias() );
  m_PSW = 0;
}

QString StorageEditor::releaseError()
{
  QString result = error;
  error.clear();
  return result;
}

//void StorageEditor::load()
//{
//  Properties *ps = m_Storage->getPropertiesView()->root();
//  loadRecords( ps, QString() );

//  int count = 0;
//  foreach ( MFCRecord *record, m_Records.value( ps, QList<MFCRecord *>() ) )
//  {
//    count++;
//    m_Storage->appendRecord( record, false );
//    if ( count%1000 == 0 ) qApp->processEvents();
//  }
//  m_Storage->resort();
//  foreach ( Properties *properties, m_Records.keys() )
//    m_Records[properties].clear();
//  m_Records.clear();
//}

//bool StorageEditor::loadRecords( Properties *ps, QString filter )
//{
//  SqlResult *sql_result = m_PSW->load( ps, filter );
//  if ( sql_result->sqlError().isValid() )
//  {
//    delete sql_result;
//    sql_result = 0;
//    error = QString( "Ошибка запроса!\n==>Текст ошибки: %1" ).arg( sql_result->sqlError().text() );
//    qDebug() << error;
//    return false;
//  }

//  if ( !m_Records.contains( ps ) )
//    m_Records.insert( ps, QList<MFCRecord *>() );

//  PropertiesView *pv = m_Storage->getPropertiesView();
//  PropertiesLink *pl = pv->findPropertiesLink( ps );

//  QSqlQuery &qry = sql_result->sqlQuery();
//  while ( qry->next() )
//  {
//    MFCRecord *record = new MFCRecord( pl );
//    for ( int cIdx = 0; cIdx < qry->record().count(); cIdx++ )
//    {
//      record->setDefaultProperty( qry->record().fieldName( cIdx ), qry->record().value( cIdx ) );
//      record->setCurrentProperty( qry->record().fieldName( cIdx ), qry->record().value( cIdx ) );
//    }

//    m_Records[ps] << record;
//  }

//  QList<QPair<QString, LinkOptions *> > links = pl->availableLinks();
//  for ( int lIdx = 0; lIdx < links.count(); lIdx++ )
//  {
//    Properties *child = links[lIdx].second->child();
//    QStringList ids_minus = QStringList();
//    foreach ( MFCRecord *record, m_Records.value( child, QList<MFCRecord *>() ) )
//      ids_minus << record->currentProperty( links[lIdx].second->propertyName() ).toString();
//    QStringList ids_plus = QStringList();
//    foreach ( MFCRecord *record, m_Records.value( ps, QList<MFCRecord *>() ) )
//      ids_plus << record->currentProperty( links[lIdx].first ).toString();
//    QString filter = QString();
//    if ( ids_minus.count() > 0 )
//      filter = ( filter.isEmpty() ? "" : " AND " )+
//          tr( "NOT %1 in (%2)" ).arg( links[lIdx].second->propertyName(), ids_minus.join( ", " ) );
//    if ( ids_plus.count() > 0 )
//      filter = ( filter.isEmpty() ? "" : " AND " )+
//          tr( "%1 in (%2)" ).arg( links[lIdx].second->propertyName(), ids_plus.join( ", " ) );
//    if ( !loadRecords( child, filter ) ) return false;

//    foreach ( MFCRecord *record, m_Records.value( ps, QList<MFCRecord *>() ) )
//    {
//      ids_plus << record->currentProperty( links[lIdx].second->propertyName() ).toString();
//      foreach ( MFCRecord *sub_record, m_Records.value( child, QList<MFCRecord *>() ) )
//      {
//        if ( record->currentProperty( links[lIdx].first ) ==
//             sub_record->currentProperty( links[lIdx].second->propertyName() ) )
//        {
//          record->addChildRecord( sub_record );
//          break;
//        }
//      }
//    }
//  }

//  return true;
//}

//bool StorageEditor::loadRecords( PropertiesView *pv, QString filter )
//{
//  SqlResult *sql_result = m_PSW->load( pv->root(), filter );
//  if ( sql_result->sqlError().isValid() )
//  {
//    error = QString( "Ошибка запроса!\n==>Текст ошибки: %1" ).arg( sql_result->sqlError().text() );
//    delete sql_result;
//    sql_result = 0;
//    qDebug() << error;
//    return false;
//  }

//  if ( !m_Records.contains( pv ) )
//    m_Records.insert( pv, QList<MFCRecord *>() );

//  PropertiesView *rootPV = m_Storage->getPropertiesView();
//  PropertiesLink *pl = rootPV->findPropertiesLink( pv );

//  QSqlQuery &qry = sql_result->sqlQuery();
//  while ( qry->next() )
//  {
//    MFCRecord *record = new MFCRecord( pl );
//    for ( int cIdx = 0; cIdx < qry->record().count(); cIdx++ )
//    {
//      record->setDefaultProperty( qry->record().fieldName( cIdx ), qry->record().value( cIdx ) );
//      record->setCurrentProperty( qry->record().fieldName( cIdx ), qry->record().value( cIdx ) );
//    }

//    m_Records[pv] << record;
//  }

////  QList<QPair<QString, LinkOptions *> > links = pl->availableLinks();
////  for ( int lIdx = 0; lIdx < links.count(); lIdx++ )
////  {
////    PropertiesView *child = PropertiesView::getPropertiesView(
////          links[lIdx].second->propertiesViewAlias() );
////    QStringList ids_minus = QStringList();
////    foreach ( MFCRecord *record, m_Records.value( child, QList<MFCRecord *>() ) )
////      ids_minus << record->currentProperty( links[lIdx].second->propertyName() ).toString();
////    QStringList ids_plus = QStringList();
////    foreach ( MFCRecord *record, m_Records.value( pv, QList<MFCRecord *>() ) )
////      ids_plus << record->currentProperty( links[lIdx].first ).toString();
////    QString filter = QString();
////    if ( ids_minus.count() > 0 )
////      filter = ( filter.isEmpty() ? "" : " AND " )+
////          tr( "NOT %1 in (%2)" ).arg( links[lIdx].second->propertyName(), ids_minus.join( ", " ) );
////    if ( ids_plus.count() > 0 )
////      filter = ( filter.isEmpty() ? "" : " AND " )+
////          tr( "%1 in (%2)" ).arg( links[lIdx].second->propertyName(), ids_plus.join( ", " ) );
////    if ( !loadRecords( child, filter ) ) return false;

////    foreach ( MFCRecord *record, m_Records.value( pv, QList<MFCRecord *>() ) )
////    {
////      ids_plus << record->currentProperty( links[lIdx].second->propertyName() ).toString();
////      foreach ( MFCRecord *sub_record, m_Records.value( child, QList<MFCRecord *>() ) )
////      {
////        if ( record->currentProperty( links[lIdx].first ) ==
////             sub_record->currentProperty( links[lIdx].second->propertyName() ) )
////        {
////          record->addChildRecord( sub_record );
////          break;
////        }
////      }
////    }
////  }

//  return true;
//}

bool StorageEditor::unloadRecords( QStringList &recordKeys, const QString &keyField )
{
  emit progress( 0 );
  emit address( QString( "[%1]" ).arg( m_Storage->getPropertiesView()->root()->name() ) );
  qApp->processEvents();

  SqlResult *sql_result = m_PSW->notExists( m_Storage->getPropertiesView()->root(),
                                            recordKeys, keyField );
  if ( sql_result->sqlError().isValid() )
  {
    error = QString( "Ошибка запроса!\n==>Текст ошибки: %1" ).arg( sql_result->sqlError().text() );
    delete sql_result;
    sql_result = 0;
    qDebug() << error;
    return false;
  }

  QSqlQuery *qry = sql_result->sqlQuery();
  int count = qry->size();
  int current = 0;
  while ( qry->next() )
  {
    current++;
    QVariant value = qry->record().value( keyField );
    MFCRecord *record = m_Storage->findByIndex( keyField, value );
    if ( record != NULL )
    {
      m_Storage->removeRecord( record );
      delete record;
      record = NULL;

      recordKeys.removeOne( value.toString() );
    }
    emit progress( (int)((double)current/(double)count*100.) );
    if ( current%500 == 0 ) qApp->processEvents();
  }
  if ( current == 0 )
  {
    emit progress( 100 );
    qApp->processEvents();
  }

  return true;
}

bool StorageEditor::updateRecords( const QString &filter, const QString &keyField )
{
  emit progress( 0 );
  emit address( QString( "[%1]" ).arg( m_Storage->getPropertiesView()->root()->name() ) );
  qApp->processEvents();

  SqlResult *sql_result = m_PSW->load( m_Storage->getPropertiesView()->root(), filter );
  if ( sql_result->sqlError().isValid() )
  {
    error = QString( "Ошибка запроса!\n==>Текст ошибки: %1" ).arg( sql_result->sqlError().text() );
    delete sql_result;
    sql_result = 0;
    qDebug() << error;
    return false;
  }

  QSqlQuery *qry = sql_result->sqlQuery();
  int count = qry->size();
  int current = 0;
  while ( qry->next() )
  {
    current++;
    QVariant value = qry->record().value( keyField );
    MFCRecord *record = m_Storage->findByIndex( keyField, value );
    if ( record != NULL )
      for ( int cIdx = 0; cIdx < qry->record().count(); cIdx++ )
      {
        record->setDefaultProperty( qry->record().fieldName( cIdx ),
                                    qry->record().value( cIdx ) );
        record->setCurrentProperty( qry->record().fieldName( cIdx ),
                                    qry->record().value( cIdx ) );
      }
    emit progress( (int)((double)current/(double)count*100.) );
    if ( current%500 == 0 ) qApp->processEvents();
  }
  if ( current == 0 )
  {
    emit progress( 100 );
    qApp->processEvents();
  }

  return true;
}

bool StorageEditor::loadRecords( StorageItemModel *currentStorage, QString filter )
{
  PropertiesView *pv = currentStorage->getPropertiesView();
  m_Address << tr( "[%1]" ).arg( pv->root()->name() );
  QString text = m_Address.join( "." );
  if ( m_ShowLoadLog ) qDebug() << tr( "Loading... %1" ).arg( text );
  emit progress( 0 );
  emit address( text );
  qApp->processEvents();
  SqlResult *sql_result = m_PSW->load( pv->root(), filter );
  if ( sql_result->sqlError().isValid() )
  {
    error = QString( "Ошибка запроса!\n==>Текст ошибки: %1" ).arg( sql_result->sqlError().text() );
    delete sql_result;
    sql_result = 0;
    qDebug() << error;
    return false;
  }

  if ( !m_Records.contains( pv ) )
    m_Records.insert( pv, QList<MFCRecord *>() );

  PropertiesLink *pl = pv->propertiesLink();

  QSqlQuery *qry = sql_result->sqlQuery();
  while ( qry->next() )
  {
    MFCRecord *record = new MFCRecord( pl );
    for ( int cIdx = 0; cIdx < qry->record().count(); cIdx++ )
    {
      record->setDefaultProperty( qry->record().fieldName( cIdx ), qry->record().value( cIdx ) );
      record->setCurrentProperty( qry->record().fieldName( cIdx ), qry->record().value( cIdx ) );
    }

    m_Records[pv] << record;
  }
  delete sql_result;
  sql_result = NULL;

  QList<QPair<QString, LinkOptions *> > links = pl->availableLinks();
  for ( int lIdx = 0; lIdx < links.count(); lIdx++ )
  {
    PropertiesView *child = PropertiesView::getPropertiesView(
          links[lIdx].second->propertiesViewAlias() );
    StorageItemModel *extStorage = currentStorage->externalStorage( child );
    if ( extStorage == 0 )
    {
//      qDebug() << tr( "External storage is NULL" );
//      qDebug() << tr( "PropertiesView alias [%1]" ).arg( child->alias() );
      if ( child->isNull() ) return false;
      extStorage = new StorageItemModel( child );
      bool res = currentStorage->addExternalStorage( extStorage, true );
      if ( res ) addAutoClearStorage( currentStorage, extStorage );
//      qDebug() << "currentStorage->addExternalStorage" << res;
    }
    QStringList ids_plus = QStringList();
    foreach ( MFCRecord *record, m_Records.value( pv, QList<MFCRecord *>() ) )
      if ( extStorage->findByIndex( links[lIdx].second->propertyName(),
                                    record->currentProperty( links[lIdx].first ) ) == 0 )
        ids_plus << record->currentProperty( links[lIdx].first ).toString();
    QString filter = QString();
    if ( ids_plus.count() > 0 )
      filter = ( filter.isEmpty() ? "" : " AND " )+
          tr( "%1 in (%2)" ).arg( PropertiesSqlWorker::preparePsName(
                                    links[lIdx].second->propertyName() ),
                                  ids_plus.join( ", " ) );

    if ( filter.isEmpty() ) continue;
    if ( !loadRecords( extStorage, filter ) )
    {
      qDebug() << tr( "loadRecords fail!" );
      qDebug() << tr( "PropertiesView alias [%1]" ).arg( child->alias() );
      return false;
    }
  }

  QList<MFCRecord *> records = m_Records.value( pv, QList<MFCRecord *>() );
  if ( pv == m_Storage->getPropertiesView() )
    foreach ( MFCRecord *record, records )
    {
      if ( !currentStorage->appendRecord( record, false ) ) delete record;
      emit progress( (int)((double)currentStorage->rowCount()/(double)records.count()*100) );
      if ( currentStorage->rowCount()%500 == 0 ) qApp->processEvents();
    }
  else
    foreach ( MFCRecord *record, records ){
      if ( !currentStorage->appendRecord( record, false ) ) delete record;
   }
  currentStorage->resort();

  m_Records[pv].clear();
  m_Records.remove( pv );
  m_Address.removeLast();

  return true;
}

bool StorageEditor::nextVal( MFCRecord *rootRecord, PropertiesSqlWorker *psw )
{
  SqlResult *sql_result = psw->nextVal( rootRecord->properties() );
  if ( sql_result->sqlError().isValid() )
  {
    error = QString( "Ошибка запроса!\n==>Текст ошибки: %1" ).arg( sql_result->sqlError().text() );
    delete sql_result;
    sql_result = 0;
    qDebug() << error;
    return false;
  }

  QSqlQuery *qry = sql_result->sqlQuery();
  if ( qry->isValid() )
  {
    for ( int fIdx = 0; fIdx < qry->record().count(); fIdx++ )
      rootRecord->setCurrentProperty( qry->record().fieldName( fIdx ),
                                      qry->record().value( fIdx ) );
    delete sql_result;
    sql_result = 0;
    return true;
  }
  delete sql_result;
  sql_result = 0;
  return false;
}

void StorageEditor::addAutoClearStorage( StorageItemModel *parentStorage, StorageItemModel *childStorage )
{
  if ( !m__AutoClearedStorage.contains( parentStorage ) )
    m__AutoClearedStorage[parentStorage] << QList<StorageItemModel *>();

  if ( !m__AutoClearedStorage[parentStorage].contains( childStorage ) )
  {
    m__AutoClearedStorage[parentStorage].append( childStorage );
    connect( parentStorage, SIGNAL(contentDeleted()), childStorage, SLOT(deleteContent()) );
  }
}

void StorageEditor::storageDestroyed()
{
  m_Storage = 0;
  m_Editors.remove( alias() );
  deleteLater();
}

void StorageEditor::recordAdded( MFCRecord *rootRecord )
{
  connect( rootRecord, SIGNAL(propertyChanged(QString,QVariant,QVariant)),
           this, SLOT(propertyChanged(QString,QVariant,QVariant)) );
}

void StorageEditor::propertyChanged( QString p_Name, QVariant oldValue, QVariant newValue )
{
  MFCRecord *record = qobject_cast<MFCRecord *>( sender() );
  if ( !m_ChangedRecords.contains( record ) &&
       !m_Storage->newRecords().contains( record ) )
    m_ChangedRecords << record;
  if ( record == revert || !m_UniqueProperties.contains( p_Name ) ) return;
  if ( !checkChanges )
  {
    if ( !m_ChangedProperies.contains( record ) )
      m_ChangedProperies[record] = QStringList();
    if ( !m_ChangedProperies[record].contains( p_Name ) )
      m_ChangedProperies[record] << p_Name;
    QPair<MFCRecord *, QString> pair = qMakePair( record, p_Name );
    if ( !m_ChangedValues.contains( pair ) )
      m_ChangedValues[pair] = qMakePair( oldValue, QVariant() );
    m_ChangedValues[pair].second = newValue;
    if ( m_ChangedValues[pair].first == m_ChangedValues[pair].second )
    {
      m_ChangedValues.remove( pair );
      m_ChangedProperies[record].removeOne( p_Name );
      if ( m_ChangedProperies[record].count() == 0 ) m_ChangedProperies.remove( record );
    }
  }
}
