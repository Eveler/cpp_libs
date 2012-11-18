#include "storageitemmodel.h"

#include <QBitArray>
#include <QBitmap>
#include <QEasingCurve>
#include <QMatrix4x4>
#include <QPen>
#include <QTextFormat>
#include <QTextLength>
#include <QUrl>
#include <QVector2D>
#include <QListIterator>
#include <QDateTime>

#include <QDebug>
#include <QApplication>

const QList<QVariant::Type> StorageItemModel::indexedTypes =
    QList<QVariant::Type>() << QVariant::Int << QVariant::UInt <<
                               QVariant::Double << QVariant::LongLong << QVariant::ULongLong <<
                               QVariant::String << QVariant::Date << QVariant::DateTime <<
                               QVariant::Time << QVariant::ByteArray;


ParamFilters::ParamFilters() :
  QObject( 0 )
{
  m_PropertiesViews = QList<PropertiesView *>();
  m_ParamNames = QList<QPair<PropertiesView *, QStringList> >();
  m_ParamValues = QHash<PropertiesView *, QHash<QString, QVariant> >();
  m_ParamFlags = QHash<PropertiesView *, QHash<QString, Qt::MatchFlag> >();

  m_PNsNull = QStringList();
}

ParamFilters::~ParamFilters()
{
  clear();
}

void ParamFilters::clear()
{
  m_PropertiesViews.clear();
  m_ParamNames.clear();
  m_ParamValues.clear();
  m_ParamFlags.clear();
  m_PNsNull.clear();}

bool ParamFilters::setParam( PropertiesView *pv, const QString &p_Name,
                             QVariant p_Value, Qt::MatchFlag p_Flag )
{
  if ( !pv->root()->propertyNames().contains( p_Name ) ) return false;

  if ( !m_PropertiesViews.contains( pv ) ) m_PropertiesViews << pv;
  QStringList &pns = paramNamesStorage( pv );
  if ( pns.isEmpty() )
  {
    m_ParamNames << qMakePair( pv, QStringList() << p_Name );
    QHash<QString, QVariant> pVal = QHash<QString, QVariant>();
    pVal.insert( p_Name, p_Value );
    m_ParamValues.insert( pv, pVal );
    QHash<QString, Qt::MatchFlag> pFlag = QHash<QString, Qt::MatchFlag>();
    pFlag.insert( p_Name, p_Flag );
    m_ParamFlags.insert( pv, pFlag );
  }
  else
  {
    pns << p_Name;
    m_ParamValues[pv].insert( p_Name, p_Value );
    m_ParamFlags[pv].insert( p_Name, p_Flag );
  }

  return true;
}

bool ParamFilters::removeParam( PropertiesView *pv )
{
  if ( !m_PropertiesViews.contains( pv ) ) return false;

  m_PropertiesViews.removeOne( pv );
  for ( int pairIdx = m_ParamNames.count()-1; pairIdx > -1; pairIdx-- )
    if ( m_ParamNames[pairIdx].first == pv )
      m_ParamNames.removeAt( pairIdx );
  m_ParamValues.remove( pv );
  m_ParamFlags.remove( pv );

  return true;
}

bool ParamFilters::removeParam( PropertiesView *pv, const QString &p_Name )
{
  QStringList &pNs = paramNamesStorage( pv );
  if ( pNs.isEmpty() || !pNs.contains( p_Name ) ) return false;

  pNs.removeOne( p_Name );
  m_ParamValues[pv].remove( p_Name );
  m_ParamFlags[pv].remove( p_Name );

  if ( pNs.isEmpty() )
  {
    m_PropertiesViews.removeOne( pv );
    for ( int pairIdx = m_ParamNames.count()-1; pairIdx > -1; pairIdx-- )
      if ( m_ParamNames[pairIdx].first == pv )
        m_ParamNames.removeAt( pairIdx );
    m_ParamValues.remove( pv );
    m_ParamFlags.remove( pv );
  }

  return true;
}

const QList<PropertiesView *> & ParamFilters::propertiesViews() const
{
  return m_PropertiesViews;
}

const QStringList & ParamFilters::paramNames( PropertiesView *pv ) const
{
  for ( int pv_idx = 0; pv_idx < m_ParamNames.count(); pv_idx++ )
    if ( m_ParamNames[pv_idx].first == pv ) return m_ParamNames[pv_idx].second;

  return m_PNsNull;
}

QVariant ParamFilters::paramValue( PropertiesView *pv, const QString &p_Name ) const
{
  if ( !paramNames( pv ).contains( p_Name ) ) return QVariant();

  return (m_ParamValues[pv])[p_Name];
}

Qt::MatchFlag ParamFilters::paramFlag( PropertiesView *pv, const QString &p_Name ) const
{
  return (m_ParamFlags[pv])[p_Name];
}

QStringList & ParamFilters::paramNamesStorage( PropertiesView *pv )
{
  for ( int pv_idx = 0; pv_idx < m_ParamNames.count(); pv_idx++ )
    if ( m_ParamNames[pv_idx].first == pv ) return m_ParamNames[pv_idx].second;

  return m_PNsNull;
}
/******************************************************/
/*END-------------------------------------ParamFilters*/
/******************************************************/
/******************************************************/



SortParams::SortParams() :
  QObject( 0 )
{
  m_PV = 0;
  m_PropertiesViews = QList<PropertiesView *>();
  m_ParamNames = QList<QPair<PropertiesView *, QStringList> >();
  m_SortFlags = QHash<PropertiesView *, QHash<QString, Qt::SortOrder> >();

  m_PNsNull = QStringList();
}

SortParams::~SortParams()
{
  m_PV = 0;
  clear();
}

bool SortParams::setPropertiesView( const QString &alias )
{
  PropertiesView *pv = PropertiesView::getPropertiesView( alias );
  if ( m_PV != 0 || pv->isNull() ) return false;

  m_PV = pv;

  return true;
}

bool SortParams::isNull() const
{
  return ( m_PV == 0 );
}

bool SortParams::isValid() const
{
  return ( m_PropertiesViews.count() != 0 );
}

bool SortParams::setSort( PropertiesView *pv, const QString &p_Name, Qt::SortOrder sort_Flag )
{
  if ( m_PV == 0 || m_PV->findPropertiesLink( pv ) == 0 ||
       !pv->root()->propertyNames().contains( p_Name ) ) return false;

//  if ( m_Properties == 0 ) m_Properties = ps;
//  if ( !m_ParamNames.contains( p_Name ) ) m_ParamNames << p_Name;
//  m_SortFlags[p_Name] = sort_Flag;

  if ( !m_PropertiesViews.contains( pv ) ) m_PropertiesViews << pv;
  QStringList &pns = paramNamesStorage( pv );
  if ( pns.isEmpty() )
  {
    m_ParamNames << qMakePair( pv, QStringList() << p_Name );
    QHash<QString, Qt::SortOrder> sFlag = QHash<QString, Qt::SortOrder>();
    sFlag.insert( p_Name, sort_Flag );
    m_SortFlags.insert( pv, sFlag );
  }
  else
  {
    pns << p_Name;
    m_SortFlags[pv].insert( p_Name, sort_Flag );
  }

  emit changed();

  return true;
}

bool SortParams::removeSort( PropertiesView *pv )
{
  if ( !m_PropertiesViews.contains( pv ) ) return false;

  m_PropertiesViews.removeOne( pv );
  for ( int pairIdx = m_ParamNames.count()-1; pairIdx > -1; pairIdx-- )
    if ( m_ParamNames[pairIdx].first == pv )
      m_ParamNames.removeAt( pairIdx );
  m_SortFlags.remove( pv );

  emit changed();

  return true;
}

bool SortParams::removeSort( PropertiesView *pv, const QString &p_Name )
{
  QStringList &pNs = paramNamesStorage( pv );
  if ( pNs.isEmpty() || !pNs.contains( p_Name ) ) return false;

  pNs.removeOne( p_Name );
  m_SortFlags[pv].remove( p_Name );

  if ( pNs.isEmpty() )
  {
    m_PropertiesViews.removeOne( pv );
    for ( int pairIdx = m_ParamNames.count()-1; pairIdx > -1; pairIdx-- )
      if ( m_ParamNames[pairIdx].first == pv )
        m_ParamNames.removeAt( pairIdx );
    m_SortFlags.remove( pv );
  }

  emit changed();

  return true;
}

void SortParams::clear(){
  m_PropertiesViews.clear();
  m_ParamNames.clear();
  m_SortFlags.clear();
}

PropertiesView * SortParams::propertiesView() const
{
  return m_PV;
}

const QList<PropertiesView *> & SortParams::propertiesViews() const
{
  return m_PropertiesViews;
}

const QStringList & SortParams::paramNames( PropertiesView *pv ) const
{
  for ( int pv_idx = 0; pv_idx < m_ParamNames.count(); pv_idx++ )
    if ( m_ParamNames[pv_idx].first == pv ) return m_ParamNames[pv_idx].second;

  return m_PNsNull;
}

Qt::SortOrder SortParams::sortFlag( PropertiesView *pv, const QString &p_Name ) const
{
  if(!m_SortFlags.contains(pv) || !m_SortFlags[pv].contains(p_Name)) return Qt::AscendingOrder;
  return (m_SortFlags[pv])[p_Name];
}

bool SortParams::comparison( MFCRecord *record_1, MFCRecord *record_2 ) const
{
  bool result = false;
  if ( isNull() || record_1 == 0 || record_2 == 0 ||
       m_PV->propertiesLink() != record_1->propertiesLink() ||
       record_1->propertiesLink() != record_2->propertiesLink() )
  {
    qDebug() << isNull() << ( record_1 == 0 ) << ( record_2 == 0 ) <<
            ( m_PV->propertiesLink() != record_1->propertiesLink() ) <<
            ( record_1->propertiesLink() != record_2->propertiesLink() );
    return result;
  }

  foreach ( PropertiesView *pv, propertiesViews() )
  {
    foreach ( QString p_Name, paramNames( pv ) )
    {
      bool next = false;
      Qt::SortOrder sort = sortFlag( pv, p_Name );
      const QVariant &val_1 = record_1->getCurrentValue( pv, p_Name );
      const QVariant &val_2 = record_2->getCurrentValue( pv, p_Name );
      switch ( pv->root()->propertyType( p_Name ) )
      {
      case QVariant::Bool:
        if ( val_1.toBool() == val_2.toBool() )
          next = true;
        else
          result = ( ( sort == Qt::AscendingOrder && val_1.toBool() > val_2.toBool() ) ||
                     ( sort == Qt::DescendingOrder && val_1.toBool() < val_2.toBool() ) );
        break;
      case QVariant::ByteArray:
        if ( val_1.toByteArray() == val_2.toByteArray() )
          next = true;
        else
        result = ( ( sort == Qt::AscendingOrder && val_1.toByteArray() > val_2.toByteArray() ) ||
                   ( sort == Qt::DescendingOrder && val_1.toByteArray() < val_2.toByteArray() ) );
        break;
      case QVariant::Char:
        if ( val_1.toChar() == val_2.toChar() )
          next = true;
        else
        result = ( ( sort == Qt::AscendingOrder && val_1.toChar() > val_2.toChar() ) ||
                   ( sort == Qt::DescendingOrder && val_1.toChar() < val_2.toChar() ) );
        break;
      case QVariant::Date:
        if ( val_1.toDate() == val_2.toDate() )
          next = true;
        else
        result = ( ( sort == Qt::AscendingOrder && val_1.toDate() > val_2.toDate() ) ||
                   ( sort == Qt::DescendingOrder && val_1.toDate() < val_2.toDate() ) );
        break;
      case QVariant::DateTime:
        if ( val_1.toDateTime() == val_2.toDateTime() )
          next = true;
        else
        result = ( ( sort == Qt::AscendingOrder && val_1.toDateTime() > val_2.toDateTime() ) ||
                   ( sort == Qt::DescendingOrder && val_1.toDateTime() < val_2.toDateTime() ) );
        break;
      case QVariant::Double:
        if ( val_1.toDouble() == val_2.toDouble() )
          next = true;
        else
        result = ( ( sort == Qt::AscendingOrder && val_1.toDouble() > val_2.toDouble() ) ||
                   ( sort == Qt::DescendingOrder && val_1.toDouble() < val_2.toDouble() ) );
        break;
      case QVariant::Int:
        if ( val_1.toInt() == val_2.toInt() )
          next = true;
        else
        result = ( ( sort == Qt::AscendingOrder && val_1.toInt() > val_2.toInt() ) ||
                   ( sort == Qt::DescendingOrder && val_1.toInt() < val_2.toInt() ) );
        break;
      case QVariant::LongLong:
        if ( val_1.toLongLong() == val_2.toLongLong() )
          next = true;
        else
        result = ( ( sort == Qt::AscendingOrder && val_1.toLongLong() > val_2.toLongLong() ) ||
                   ( sort == Qt::DescendingOrder && val_1.toLongLong() < val_2.toLongLong() ) );
        break;
      case QVariant::String:
        if ( val_1.toString() == val_2.toString() )
          next = true;
        else
        result = ( ( sort == Qt::AscendingOrder && /*val_1.toString() > val_2.toString()*/
                     val_1.toString().localeAwareCompare(val_2.toString())>0) ||
                   ( sort == Qt::DescendingOrder && /*val_1.toString() < val_2.toString()*/
                     val_1.toString().localeAwareCompare(val_2.toString())<0) );
        break;
      case QVariant::Time:
        if ( val_1.toTime() == val_2.toTime() )
          next = true;
        else
        result = ( ( sort == Qt::AscendingOrder && val_1.toTime() > val_2.toTime() ) ||
                   ( sort == Qt::DescendingOrder && val_1.toTime() < val_2.toTime() ) );
        break;
      case QVariant::UInt:
        if ( val_1.toUInt() == val_2.toUInt() )
          next = true;
        else
        result = ( ( sort == Qt::AscendingOrder && val_1.toUInt() > val_2.toUInt() ) ||
                   ( sort == Qt::DescendingOrder && val_1.toUInt() < val_2.toUInt() ) );
        break;
      case QVariant::ULongLong:
        if ( val_1.toULongLong() == val_2.toULongLong() )
          next = true;
        else
        result = ( ( sort == Qt::AscendingOrder && val_1.toULongLong() > val_2.toULongLong() ) ||
                   ( sort == Qt::DescendingOrder && val_1.toULongLong() < val_2.toULongLong() ) );
        break;
      case QVariant::Url:
        if ( val_1.toString() == val_2.toString() )
          next = true;
        else
        result = ( ( sort == Qt::AscendingOrder && /*val_1.toString() > val_2.toString()*/
                     val_1.toString().localeAwareCompare(val_2.toString())>0) ||
                   ( sort == Qt::DescendingOrder && /*val_1.toString() < val_2.toString()*/
                     val_1.toString().localeAwareCompare(val_2.toString())<0) );
        break;
      default:
        break;
      }
      if ( result || !next ) return result;
    }
  }

  return result;
}

QStringList & SortParams::paramNamesStorage( PropertiesView *pv )
{
  for ( int pv_idx = 0; pv_idx < m_ParamNames.count(); pv_idx++ )
    if ( m_ParamNames[pv_idx].first == pv ) return m_ParamNames[pv_idx].second;

  return m_PNsNull;
}
/******************************************************/
/*END---------------------------------------SortParams*/
/******************************************************/
/******************************************************/


StorageItemModel::StorageItemModel( PropertiesView *propertiesView, QObject *parent ) :
  QStandardItemModel( parent ),
  m_CanStartSearch( true ),
  m_AvailableRecords(),
  m_VisibleRecords(),
  m_NewRecords()
{
  if ( QMetaType::type( tr( "QUuid" ).toLocal8Bit() ) == 0 )
    qRegisterMetaType<QUuid>( tr( "QUuid" ).toLocal8Bit() );

  m_PropertiesView = propertiesView;
  if ( m_PropertiesView != 0 ) m_PropertiesViewAlias = m_PropertiesView->alias();
  else m_PropertiesViewAlias = QString();

  m__ExternalStorages = QList<StorageItemModel *>();
  m__ExtStgs_PV = QHash<PropertiesView *, StorageItemModel *>();
  m__ExtStgs_Alias = QHash<QString, StorageItemModel *>();

  m_IndexedRecords = QHash<QString, QHash<QString, MFCRecord *> >();

  if ( !isNull() ) propertiesModified();

  blockEdit = true;

  m_Filter = NULL;
  m_Sort = 0;
}

StorageItemModel::~StorageItemModel()
{
//  qDebug() << tr( "~StorageItemModel" ) << this;;
  m_RecordsUuid.clear();
  m_VisibleRecords.clear();
  m_NewRecords.clear();
  m_NotSorted.clear();
  m_AvailableRecords.clear();
  if ( m_Filter != NULL )
  {
    disconnect( m_Filter, SIGNAL(destroyed()), this, SLOT(filterDestroyed()) );
    delete m_Filter;
    m_Filter = NULL;
  }
  if ( m_Sort != 0 )
  {
    disconnect( m_Sort, SIGNAL(destroyed()), this, SLOT(sortDestroyed()) );
    delete m_Sort;
    m_Sort = 0;
  }

  m__ExternalStorages.clear();
  m__ExtStgs_PV.clear();
  m__ExtStgs_Alias.clear();
  while ( !m__DeletableStorages.isEmpty() )
  {
    StorageItemModel *storage = m__DeletableStorages.takeFirst();
    disconnect( storage, SIGNAL(destroyed(QObject*)),
                this, SLOT(externalStorageDestroyed(QObject*)) );
    delete storage;
  }
}

bool StorageItemModel::isNull() const
{
  return m_PropertiesViewAlias.isEmpty();
}

StorageItemModel * StorageItemModel::externalStorage_Recursively( PropertiesView *pv )
{
  foreach ( StorageItemModel *extStorage, externalStorages() )
    if ( pv == extStorage->getPropertiesView() ) return extStorage;
    else
    {
      StorageItemModel *res = extStorage->externalStorage_Recursively( pv );
      if ( res != 0 ) return res;
    }
  return 0;
}

bool StorageItemModel::addExternalStorage( StorageItemModel *storage, bool autoDelete )
{
  bool hasLink = ( m_PropertiesView->findPropertiesLink( storage->getPropertiesView() ) != 0 );
  if ( isNull()  )
  {
    qDebug() << tr( "StorageItemModel is null!" );;
    return false;
  }
  if ( rowCount() > 0 )
  {
    qDebug() << tr( "Row count > 0!" );;
    return false;
  }
  if ( m__ExternalStorages.contains( storage ) )
  {
    qDebug() << tr( "External starage already exists!" );;
    return false;
  }
  if ( !hasLink )
  {
    qDebug() << tr( "Link is not exists!" );;
    return false;
  }
  if ( m_PropertiesView->findPropertiesLink( storage->getPropertiesView() ) )

  foreach ( StorageItemModel *extStorage, m__ExternalStorages )
    if ( extStorage->getPropertiesView() == storage->getPropertiesView() )
      m__ExternalStorages.removeOne( extStorage );

  m__ExternalStorages << storage;
  m__ExtStgs_PV.insert( storage->getPropertiesView(), storage );
  m__ExtStgs_Alias.insert( storage->getPropertiesView()->alias(), storage );
  if ( autoDelete ) m__DeletableStorages << storage;

  connect( storage, SIGNAL(destroyed(QObject*)),
           this, SLOT(externalStorageDestroyed(QObject*)) );

  return true;
}

StorageItemModel * StorageItemModel::externalStorage( PropertiesView *pv ) const
{
  return m__ExtStgs_PV.value( pv, 0 );
}

StorageItemModel * StorageItemModel::externalStorage( const QString &pv_alias ) const
{
  return m__ExtStgs_Alias.value( pv_alias, 0 );
}

QList<StorageItemModel *> StorageItemModel::externalStorages() const
{
  return m__ExtStgs_PV.values();
}

bool StorageItemModel::appendRecord( MFCRecord *rootRecord, bool markAsNew )
{
  bool showLog = false;
//  showLog = ( m_PropertiesView->alias().contains( tr( "pv_declar_documents" ) ) );

  if ( isNull() || m_PropertiesView != rootRecord->propertiesView() ||
       m_PropertiesView->root() != rootRecord->properties() )
  {
    qDebug() << isNull() << ( m_PropertiesView != rootRecord->propertiesView() ) <<
            ( m_PropertiesView->root() != rootRecord->properties() );;
    return false;
  }

  if ( rootRecord->childrenRecord().count() == 0 )
  {

    QList<QPair<QString, LinkOptions *> > links = m_PropertiesView->propertiesLink()->availableLinks();
    QList<MFCRecord *> records = QList<MFCRecord *>();
    for ( int pairIdx = 0; pairIdx < links.count(); pairIdx++ )
    {
      StorageItemModel *storage = externalStorage( links[pairIdx].second->propertiesViewAlias() );
      if ( storage == 0 )
      {
        qDebug() << storage << links[pairIdx].second->propertiesViewAlias() <<
                PropertiesView::getPropertiesView(
                  links[pairIdx].second->propertiesViewAlias() )->alias() ;;
        qDebug() << m__ExternalStorages.count();;
      }
//      ParamFilters filter;
//      filter.setParam( storage->getPropertiesView(),
//                       links[pairIdx].second->propertyName(),
//                       rootRecord->currentProperty( links[pairIdx].first ) );
//      QList<MFCRecord *> result = storage->findRecords( filter );
//      if ( result.count() == 0 )
//      {
//        qDebug() << tr( "storage->findRecords fail\t[%1:%2]" ).arg(
//                  rootRecord->properties()->name(),
//                  storage->getPropertiesView()->root()->name() );;
//        qDebug() << tr( "\t\t>>>>>>> value:\t[%1]" ).arg(
//                  rootRecord->currentProperty( links[pairIdx].first ).toString() );;
//        return false;
//      }
//      records << result.first();
      MFCRecord *result = storage->findByIndex( links[pairIdx].second->propertyName(),
                                                rootRecord->currentProperty( links[pairIdx].first ) );
//      if ( showLog )
//      {
//        qDebug() << "parent_PName:" << links[pairIdx].first;;
//        qDebug() << "child_PName:" << links[pairIdx].second->propertyName();;
//        qDebug() << "key value:" << rootRecord->currentProperty( links[pairIdx].first );;
//        qDebug() << "result record: " << result;;
//      }
      if ( showLog )
        qDebug() << "parent_PName:" << links[pairIdx].first <<
                "child_PName:" << links[pairIdx].second->propertyName() <<
                "key value:" << rootRecord->currentProperty( links[pairIdx].first ) <<
                "result record: " << result;;
//      if ( rootRecord->propertiesView()->alias().contains( tr( "docpaths" ) ) )
//        qDebug() << "propertyName" << links[pairIdx].first <<
//                "value" << rootRecord->currentProperty( links[pairIdx].first ) <<
//                "result" << result;;
      if ( result == 0 &&
           rootRecord->currentProperty( links[pairIdx].first ).isValid() &&
           rootRecord->currentProperty( links[pairIdx].first ).toInt() != 0 )
      {
        qDebug() << tr( "storage->findRecords fail\t[%1:%2]" ).arg(
                  rootRecord->properties()->name(),
                  storage->getPropertiesView()->root()->name() );;
        qDebug() << tr( "\t\t>>>>>>> value:\t[%1]" ).arg(
                  rootRecord->currentProperty( links[pairIdx].first ).toString() );;
        return false;
      }
      if ( result != 0 ) records << result;
    }
    foreach ( MFCRecord *childRecord, records ){
      if ( !rootRecord->addChildRecord( childRecord ) )
      {
        qDebug() << "rootRecord->addChildRecord fail";;
        qDebug() << tr( "parent [%1] : child [%2]" ).arg( rootRecord->properties()->name(),
                                                      childRecord->properties()->name() );;
        return false;
      }
    }
  }

  int row = m_VisibleRecords.count();
  insertRowU( row );
  m_AvailableRecords << rootRecord;
  emit availableRecords_Changed();
  m_RecordsUuid << m_AvailableRecords.last()->uuid();
  m_VisibleRecords << m_AvailableRecords.last();
  emit visibleRecords_Changed();
  if ( markAsNew )
  {
    m_NewRecords << m_AvailableRecords.last();
    emit newRecords_Changed();
  }
  m_NotSorted << m_AvailableRecords.last();
//  drawRecord( row, m_AvailableRecords.last() );
  createConnect( m_AvailableRecords.last() );

  reindexRecord( row );

  emit recordAdded( m_AvailableRecords.last() );
  emit recordDisplayChanged( m_VisibleRecords.last(), m_VisibleRecords.count()-1 );

  return true;
}

void StorageItemModel::reindexRecord( int row )
{
  if ( row < 0 || row >= m_VisibleRecords.count() ) return;

  MFCRecord *record = m_VisibleRecords[row];
  drawRecord( row, 0, record );

  QMapIterator<int, QList<int> > i = linked_columns;
  i.toBack();
  while ( i.hasPrevious() )
  {
    i.previous();
    QStandardItemModel::setData( index( row, i.key() ),
                                 getVisibleData( row, i.value() ), Qt::DisplayRole );
  }
}

bool StorageItemModel::setRecordVisible( MFCRecord *rootRecord, bool visible )
{
  int idx = m_AvailableRecords.indexOf( rootRecord );
  if ( idx == -1 ) return false;

  int visiblePos = m_VisibleRecords.indexOf( rootRecord );
  if ( visible && visiblePos == -1 )
  {
    if ( idx == 0 )
    {
      insertRowU( idx );
      m_VisibleRecords.insert( idx, rootRecord );
      reindexRecord( idx );
      visiblePos = idx;
    }
    else
    {
      int prevRecIdx = -1;
      for ( int rIdx = idx+1; rIdx < m_AvailableRecords.count(); rIdx++ )
      {
        prevRecIdx = m_VisibleRecords.indexOf( m_AvailableRecords.at( rIdx ) );
        if ( prevRecIdx != -1 ) break;
      }
      if ( prevRecIdx == -1 ) prevRecIdx = m_VisibleRecords.count();
      insertRowU( prevRecIdx );
      m_VisibleRecords.insert( prevRecIdx, rootRecord );
      reindexRecord( prevRecIdx );
      visiblePos = prevRecIdx;
    }
  }
  else if ( !visible )
  {
    idx = m_VisibleRecords.indexOf( rootRecord );
    if ( idx != -1 )
    {
      m_VisibleRecords.removeOne( rootRecord );
      removeRowU( idx );
    }
    visiblePos = idx;
  }
  else visiblePos = -1;
  if ( visiblePos > -1 ) emit recordDisplayChanged( rootRecord, visiblePos );

  return true;
}

bool StorageItemModel::removeRecord( MFCRecord *rootRecord )
{
  int idx = m_AvailableRecords.indexOf( rootRecord );
  if ( idx == -1 ) return false;

  removeIndex( rootRecord );
  removeConnect( rootRecord );
  removeRowU( m_VisibleRecords.indexOf( rootRecord ) );
  m_AvailableRecords.removeAt( idx );
  emit availableRecords_Changed();
  m_RecordsUuid.removeAt( idx );
  idx = m_VisibleRecords.indexOf( rootRecord );
  m_VisibleRecords.removeOne( rootRecord );
  emit visibleRecords_Changed();
  m_NewRecords.removeOne( rootRecord );
  emit newRecords_Changed();
  //  deleteRecord( rootRecord );
//  delete rootRecord;
  if ( idx > -1 ) emit visibleRecordRemoved( idx );

  return true;
}

bool StorageItemModel::removeVisibleRecord( MFCRecord *rootRecord )
{
  int idx = m_VisibleRecords.indexOf( rootRecord );
  if ( idx == -1 ) return false;

  removeIndex( rootRecord );
  removeConnect( rootRecord );
  removeRowU( idx );
  int avIdx = m_AvailableRecords.indexOf( rootRecord );
  m_AvailableRecords.removeAt( avIdx );
  emit availableRecords_Changed();
  m_RecordsUuid.removeAt( avIdx );
  m_VisibleRecords.removeAt( idx );
  emit visibleRecords_Changed();
  m_NewRecords.removeOne( rootRecord );
  emit newRecords_Changed();
  //  deleteRecord( rootRecord );
//  delete rootRecord;
  emit visibleRecordRemoved( idx );

  return true;
}

bool StorageItemModel::removeVisibleRecord( int row )
{
  if ( row < 0 || row >= m_VisibleRecords.count() ) return false;
  MFCRecord *rootRecord = m_VisibleRecords.at( row );

  removeIndex( rootRecord );
  removeConnect( rootRecord );
  removeRowU( row );
  int avIdx = m_AvailableRecords.indexOf( rootRecord );
  m_AvailableRecords.removeAt( avIdx );
  emit availableRecords_Changed();
  m_RecordsUuid.removeAt( avIdx );
  m_VisibleRecords.removeAt( row );
  emit visibleRecords_Changed();
  m_NewRecords.removeOne( rootRecord );
  emit newRecords_Changed();
  //  deleteRecord( rootRecord );
//  delete rootRecord;
  emit visibleRecordRemoved( row );

  return true;
}

void StorageItemModel::clear()
{
  foreach ( MFCRecord *record, m_AvailableRecords ) removeRecord( record );
}

const QList<MFCRecord *> & StorageItemModel::availableRecords() const
{
  return m_AvailableRecords;
}

const QList<MFCRecord *> & StorageItemModel::visibleRecords() const
{
  return m_VisibleRecords;
}

bool StorageItemModel::changeRecordMark( MFCRecord *rootRecord, bool isNew )
{
  int idx = m_AvailableRecords.indexOf( rootRecord );
  if ( idx == -1 ) return false;

  if ( isNew && !m_NewRecords.contains( rootRecord ) )
    m_NewRecords << rootRecord;
  else m_NewRecords.removeOne( rootRecord );
  emit newRecords_Changed();

  return true;
}

const QList<MFCRecord *> & StorageItemModel::newRecords() const
{
  return m_NewRecords;
}

QList<MFCRecord *> StorageItemModel::oldRecords() const
{
  QList<MFCRecord *> result = m_AvailableRecords;
  foreach ( MFCRecord *record, m_NewRecords )
    result.removeOne( record );
  return result;
}

bool StorageItemModel::renameColumn( PropertiesView *childPV, QString childPName, QString newName,
                                     PropertiesView *parentPV, QString parentPName )
{
  bool res = false;

  int linkIndex = -1;
  if ( childPV != m_PropertiesView && parentPV != 0 )
    linkIndex = links.indexOf( qMakePair( parentPV, parentPName ) );
  QPair<int, PropertiesView *> pair_Link = qMakePair( linkIndex, childPV );
  QPair<QPair<int, PropertiesView *>, QString> pair_1 = qMakePair( pair_Link, childPName );
  QPair<QPair<int, PropertiesView *>, QString> pair_2 = qMakePair( pair_Link, newName );
  int p_Index = childPV->root()->propertyNames().indexOf( childPName );
  if ( p_Index != -1 && renamedColumns.contains( pair_1 ) )
  {
    if ( !renamedColumns.values().contains( pair_2 ) )
    {
      renamedColumns[pair_1].second = newName;
      int column = properties_columns_1[pair_Link].value( p_Index, -1 );
      res = setHeaderData( column, Qt::Horizontal, newName );
    }
  }

  return res;
}

PropertiesView * StorageItemModel::getPropertiesView() const
{
  return m_PropertiesView;
}

int StorageItemModel::findColumnByRealName( PropertiesView *childPV, QString childPName,
                                            PropertiesView *parentPV, QString parentPName ) const
{
  int linkIndex = -1;
  if ( childPV != m_PropertiesView && parentPV != 0 )
    linkIndex = links.indexOf( qMakePair( parentPV, parentPName ) );
  QPair<int, PropertiesView *> pair_Link = qMakePair( linkIndex, childPV );
  int p_Index = childPV->root()->propertyNames().indexOf( childPName );
  int column = properties_columns_1[pair_Link].value( p_Index, -1 );

  return column;
}

PropertiesView * StorageItemModel::columnPropertiesView( int col ) const
{
  QHashIterator<QPair<int, PropertiesView *>, QList<int> > iterator( properties_columns_1 );
  while ( iterator.hasNext() )
  {
    iterator.next();
    if ( iterator.value().contains( col ) )
      return iterator.key().second;
  }

  return NULL;
}

QString StorageItemModel::realHeaderName( int col ) const
{
  QHashIterator<QPair<int, PropertiesView *>, QList<int> > iterator( properties_columns_1 );
  while ( iterator.hasNext() )
  {
    iterator.next();
    if ( iterator.value().contains( col ) )
      return iterator.key().second->root()->propertyNames()[iterator.value().indexOf( col )];
  }

  return QString();
}

QList<int> StorageItemModel::linkedColumns( int col ) const
{
  QList<int> result = QList<int>();
  QList<int> columns = linked_columns[col];

  if(!linked_columns.contains(col)) result<<col;
  else
    foreach ( int subCol, columns )
      if ( linked_columns.contains( subCol ) )
        result << linkedColumns( col );
      else result << subCol;

  return result;
}

QList<MFCRecord *> StorageItemModel::findRecords( const ParamFilters &filter )
{
  QList<MFCRecord *> result = QList<MFCRecord *>();

  foreach ( PropertiesView *pv, filter.propertiesViews() )
    if ( m_PropertiesView->findPropertiesLink( pv ) == 0 )
      return result;

  foreach ( MFCRecord *rootRecord, m_AvailableRecords )
  {
    bool match = true;

    foreach ( PropertiesView *pv, filter.propertiesViews() )
    {
      foreach ( QString p_Name, filter.paramNames( pv ) )
        if ( filter.paramFlag( pv, p_Name ) == Qt::MatchExactly )
        {
          if ( rootRecord->getCurrentValue( pv, p_Name ) != filter.paramValue( pv, p_Name ) )
          {
            match = false;
            break;
          }
        }
        else if ( filter.paramFlag( pv, p_Name ) == Qt::MatchFixedString )
        {
          if ( ( pv->root()->propertyType( p_Name ) != QVariant::String &&
                 rootRecord->getCurrentValue( pv, p_Name ) != filter.paramValue( pv, p_Name ) ) ||
               ( pv->root()->propertyType( p_Name ) == QVariant::String &&
                 rootRecord->getCurrentValue( pv, p_Name ).toString().toUpper() !=
                 filter.paramValue( pv, p_Name ).toString().toUpper() ) )
          {
            match = false;
            break;
          }
        }
        else if ( filter.paramFlag( pv, p_Name ) == Qt::MatchCaseSensitive )
        {
          if ( ( pv->root()->propertyType( p_Name ) != QVariant::String &&
                 rootRecord->getCurrentValue( pv, p_Name ) != filter.paramValue( pv, p_Name ) ) ||
               ( pv->root()->propertyType( p_Name ) == QVariant::String &&
                 rootRecord->getCurrentValue( pv, p_Name ).toString() !=
                 filter.paramValue( pv, p_Name ).toString() ) )
          {
            match = false;
            break;
          }
        }
        else if ( filter.paramFlag( pv, p_Name ) == Qt::MatchContains )
        {
          if ( ( pv->root()->propertyType( p_Name ) != QVariant::String &&
                 rootRecord->getCurrentValue( pv, p_Name ) != filter.paramValue( pv, p_Name ) ) ||
               ( pv->root()->propertyType( p_Name ) == QVariant::String &&
                 !rootRecord->getCurrentValue( pv, p_Name ).toString().contains(
                   filter.paramValue( pv, p_Name ).toString() ) ) )
          {
            match = false;
            break;
          }
        }
        else if ( filter.paramFlag( pv, p_Name ) == Qt::MatchStartsWith )
        {
          if ( ( pv->root()->propertyType( p_Name ) != QVariant::String &&
                 rootRecord->getCurrentValue( pv, p_Name ) != filter.paramValue( pv, p_Name ) ) ||
               ( pv->root()->propertyType( p_Name ) == QVariant::String &&
                 rootRecord->getCurrentValue( pv, p_Name ).toString().toUpper().indexOf(
                   filter.paramValue( pv, p_Name ).toString().toUpper() ) != 0 ) )
          {
            match = false;
            break;
          }
        }
        else if ( filter.paramFlag( pv, p_Name ) == Qt::MatchEndsWith )
        {
          if ( ( pv->root()->propertyType( p_Name ) != QVariant::String &&
                 rootRecord->getCurrentValue( pv, p_Name ) != filter.paramValue( pv, p_Name ) ) ||
               ( pv->root()->propertyType( p_Name ) == QVariant::String &&
                 ( rootRecord->getCurrentValue( pv, p_Name ).toString().toUpper().lastIndexOf(
                     filter.paramValue( pv, p_Name ).toString().toUpper() ) == -1 ||
                   rootRecord->getCurrentValue( pv, p_Name ).toString().toUpper().lastIndexOf(
                                        filter.paramValue( pv, p_Name ).toString().toUpper() ) !=
                   (rootRecord->getCurrentValue( pv, p_Name ).toString().length()-
                    filter.paramValue( pv, p_Name ).toString().length()) ) ) )
          {
            match = false;
            break;
          }
        }

      if ( !match ) break;
    }

    if ( match ) result << rootRecord;
  }

  return result;
}

QList<MFCRecord *> StorageItemModel::rootRecordFor( MFCRecord *record )
{
  QList<MFCRecord *> result = QList<MFCRecord *>();

  if ( m_PropertiesView == record->propertiesView() ) return result;

  foreach ( MFCRecord *rootRecord, m_AvailableRecords )
    if ( rootRecord->getRecordByPropertiesView( record->propertiesView() ) == record )
      result << rootRecord;

  return result;
}

bool StorageItemModel::setFilter( ParamFilters *filter )
{
  if ( filter == 0 ) return false;

  foreach ( PropertiesView *pv, filter->propertiesViews() )
    if ( m_PropertiesView->findPropertiesLink( pv ) == 0 )
      return false;

  if ( m_Filter != NULL )
  {
    disconnect( m_Filter, SIGNAL(destroyed()), this, SLOT(filterDestroyed()) );
    delete m_Filter;
    m_Filter = NULL;
  }
  m_Filter = filter;
  connect( m_Filter, SIGNAL(destroyed()), this, SLOT(filterDestroyed()) );

  int curr = 0;
  foreach ( MFCRecord *rootRecord, m_AvailableRecords )
  {
    curr++;
    bool match = true;

    foreach ( PropertiesView *pv, filter->propertiesViews() )
    {
      foreach ( QString p_Name, filter->paramNames( pv ) )
        if ( filter->paramFlag( pv, p_Name ) == Qt::MatchExactly )
        {
          if ( rootRecord->getCurrentValue( pv, p_Name ) != filter->paramValue( pv, p_Name ) )
          {
            match = false;
            break;
          }
        }
        else if ( filter->paramFlag( pv, p_Name ) == Qt::MatchFixedString )
        {
          if ( ( pv->root()->propertyType( p_Name ) != QVariant::String &&
                 rootRecord->getCurrentValue( pv, p_Name ) != filter->paramValue( pv, p_Name ) ) ||
               ( pv->root()->propertyType( p_Name ) == QVariant::String &&
                 rootRecord->getCurrentValue( pv, p_Name ).toString().toUpper() !=
                 filter->paramValue( pv, p_Name ).toString().toUpper() ) )
          {
            match = false;
            break;
          }
        }
        else if ( filter->paramFlag( pv, p_Name ) == Qt::MatchCaseSensitive )
        {
          if ( ( pv->root()->propertyType( p_Name ) != QVariant::String &&
                 rootRecord->getCurrentValue( pv, p_Name ) != filter->paramValue( pv, p_Name ) ) ||
               ( pv->root()->propertyType( p_Name ) == QVariant::String &&
                 rootRecord->getCurrentValue( pv, p_Name ).toString() !=
                 filter->paramValue( pv, p_Name ).toString() ) )
          {
            match = false;
            break;
          }
        }
        else if ( filter->paramFlag( pv, p_Name ) == Qt::MatchContains )
        {
          if ( pv->root()->propertyType( p_Name ) == QVariant::String &&
               filter->paramValue( pv, p_Name ).type() == QVariant::StringList )
          {
            foreach ( QString val, filter->paramValue( pv, p_Name ).toStringList() )
              if ( !rootRecord->getCurrentValue( pv, p_Name ).toString().toUpper().contains(
                     val.toUpper() ) )
              {
                match = false;
                break;
              }
            if ( !match ) break;
          }
          else if ( ( pv->root()->propertyType( p_Name ) != QVariant::String &&
                      rootRecord->getCurrentValue( pv, p_Name ) != filter->paramValue( pv, p_Name ) ) ||
                    ( pv->root()->propertyType( p_Name ) == QVariant::String &&
                      !rootRecord->getCurrentValue( pv, p_Name ).toString().toUpper().contains(
                        filter->paramValue( pv, p_Name ).toString().toUpper() ) ) )
          {
            match = false;
            break;
          }
        }
        else if ( filter->paramFlag( pv, p_Name ) == Qt::MatchStartsWith )
        {
          if ( ( pv->root()->propertyType( p_Name ) != QVariant::String &&
                 rootRecord->getCurrentValue( pv, p_Name ) != filter->paramValue( pv, p_Name ) ) ||
               ( pv->root()->propertyType( p_Name ) == QVariant::String &&
                 rootRecord->getCurrentValue( pv, p_Name ).toString().toUpper().indexOf(
                   filter->paramValue( pv, p_Name ).toString().toUpper() ) != 0 ) )
          {
            match = false;
            break;
          }
        }
        else if ( filter->paramFlag( pv, p_Name ) == Qt::MatchEndsWith )
        {
          if ( ( pv->root()->propertyType( p_Name ) != QVariant::String &&
                 rootRecord->getCurrentValue( pv, p_Name ) != filter->paramValue( pv, p_Name ) ) ||
               ( pv->root()->propertyType( p_Name ) == QVariant::String &&
                 ( rootRecord->getCurrentValue( pv, p_Name ).toString().toUpper().lastIndexOf(
                     filter->paramValue( pv, p_Name ).toString().toUpper() ) == -1 ||
                   rootRecord->getCurrentValue( pv, p_Name ).toString().toUpper().lastIndexOf(
                                        filter->paramValue( pv, p_Name ).toString().toUpper() ) !=
                   (rootRecord->getCurrentValue( pv, p_Name ).toString().length()-
                    filter->paramValue( pv, p_Name ).toString().length()) ) ) )
          {
            match = false;
            break;
          }
        }

      if ( !match ) break;
    }

    if ( match && !visibleRecords().contains( rootRecord ) )
      setRecordVisible( rootRecord, match );
    else if ( !match && visibleRecords().contains( rootRecord ) )
      setRecordVisible( rootRecord, match );

    if ( curr%300 == 0 ) qApp->processEvents();
  }

  return true;
}

const ParamFilters * StorageItemModel::filter() const
{
  return m_Filter;
}

void StorageItemModel::clearFilter()
{
  if ( m_Filter == 0 || m_Filter->propertiesViews().count() == 0 ) return;

  delete m_Filter;
  m_Filter = 0;

  foreach ( MFCRecord *rootRecord, m_AvailableRecords )
    setRecordVisible( rootRecord );
}

bool StorageItemModel::setSort( SortParams *sort )
{
  if ( sort == 0 || m_PropertiesView != sort->propertiesView() ) return false;

  if(m_Sort==sort) return true;
  if ( m_Sort != 0 ) delete m_Sort;
  m_Sort = sort;
  connect( m_Sort, SIGNAL(changed()), this, SLOT(resort()) );
  connect( m_Sort, SIGNAL(destroyed()), this, SLOT(sortDestroyed()) );

  return resort();
}

SortParams * StorageItemModel::sort() const
{
  return m_Sort;
}

bool StorageItemModel::setChild( MFCRecord *rootRecord, QString p_Name, MFCRecord *child )
{
  if ( !m_AvailableRecords.contains( rootRecord ) || child == 0 )
    return false;
  StorageItemModel *extStorage = externalStorage( child->propertiesView() );
  if ( extStorage == 0 || !extStorage->availableRecords().contains( child ) )
    return false;

  QList<QPair<QString, LinkOptions*> > links = m_PropertiesView->propertiesLink()->links(
        child->propertiesView()->alias() );
  LinkOptions *linkOptions = 0;
  for ( int linkIdx = 0; linkIdx < links.count(); linkIdx++ )
    if ( links[linkIdx].first == p_Name ) linkOptions = links[linkIdx].second;

  if ( linkOptions == 0 ) return false;

  if ( links.count() == 1 )
  {
    MFCRecord *oldChild = rootRecord->getRecordByPropertiesView( child->propertiesView() );
    if ( oldChild != 0 )
      rootRecord->replaceChildRecord( oldChild, child );
  }
  else rootRecord->addChildRecord( child );
  rootRecord->setCurrentProperty(
        p_Name, child->currentProperty( linkOptions->propertyName() ) );

  return true;
}

MFCRecord * StorageItemModel::findByIndex( const QString &p_Name, QVariant val )
{
  return m_IndexedRecords.value( p_Name, QHash<QString, MFCRecord *>() ).value( val.toString(), NULL );
}

bool StorageItemModel::resort()
{
//  qDebug() << m_Sort;;
  if ( m_Sort == 0 ) return false;
//  qDebug() << ( m_PropertiesView != m_Sort->propertiesView() );;
  if ( m_PropertiesView != m_Sort->propertiesView() )
  {
    delete m_Sort;
    return false;
  }

  if ( m_AvailableRecords.count() == 1 ) m_NotSorted.clear();
//  qDebug() << m_NotSorted.count();;
  QList<MFCRecord *> old_VisibleRecords = m_VisibleRecords;
  QList<MFCRecord *> old_NewRecords =  m_NewRecords;
  if ( !m_NotSorted.isEmpty() )
  {
    m_VisibleRecords.clear();
    m_NewRecords.clear();
  }
  else return false;

//  qDebug() << "m_AvailableRecords.count()" << m_AvailableRecords.count();;
//  qDebug() << "m_VisibleRecords.count()" << m_VisibleRecords.count();;
//  qDebug() << "m_NewRecords.count()" << m_NewRecords.count();;

//  QList<MFCRecord *> sortedRecords = QList<MFCRecord *>();

//  qDebug() << tr( "ֲûחמג quicksort [%1:%2]" ).arg( stackCall ).arg( maxCall );;
  if ( m_NotSorted.count() > 50 )
  {
    quicksort( 0, m_AvailableRecords.count()-1 );
    m_NotSorted.clear();
  }
  else smallsort();

  foreach ( MFCRecord *rootRecord, m_AvailableRecords )
  {
    int old_idx = old_VisibleRecords.indexOf( rootRecord );
    if ( old_idx != -1 )
    {
      m_VisibleRecords << rootRecord;
      reindexRecord( m_VisibleRecords.count()-1 );
//      if ( sortedRecords.contains( rootRecord ) )
      if ( m_VisibleRecords.count()-1 != old_idx )
        emit recordMoved( rootRecord, old_idx );
    }
    if ( old_NewRecords.contains( rootRecord ) )
      m_NewRecords << rootRecord;
  }

//  qDebug() << "m_AvailableRecords.count()" << m_AvailableRecords.count();;
//  qDebug() << "m_VisibleRecords.count()" << m_VisibleRecords.count();;
//  qDebug() << "m_NewRecords.count()" << m_NewRecords.count();;
  return true;
}

bool StorageItemModel::resortAll()
{
  m_NotSorted = m_AvailableRecords;
  return resort();
}

void StorageItemModel::deleteContent()
{
//  m_IndexedRecords.clear();
//  m_RecordsUuid.clear();
//  m_VisibleRecords.clear();
//  m_NewRecords.clear();
//  m_NotSorted.clear();

//  DPRINT("HERE",qApp);
  QList<MFCRecord *> records = m_AvailableRecords;
//  DPRINT("HERE",qApp);
//  m_AvailableRecords.clear();
  while ( !records.isEmpty() )
  {
    MFCRecord *record = records.takeFirst();
    removeRecord( record );
    delete record;
  }

  emit contentDeleted();
}

//==============================================================================
//PRIVATE=======================================================================
//==============================================================================

void StorageItemModel::insertRowU( int row )
{
  blockEdit = false;
  insertRow( row );
  blockEdit = true;
}

void StorageItemModel::insertColumnU( int column )
{
  blockEdit = false;
  insertColumn( column );
  blockEdit = true;
}

bool StorageItemModel::removeRowU( int row )
{
  blockEdit = false;
  bool result = removeRow( row );
  blockEdit = true;
  return result;
}

bool StorageItemModel::removeRowsU( int row, int count )
{
  blockEdit = false;
  bool result = removeRows( row, count );
  blockEdit = true;
  return result;
}

bool StorageItemModel::removeColumnU( int column )
{
  blockEdit = false;
  bool result = removeColumn( column );
  blockEdit = true;
  return result;
}

bool StorageItemModel::removeColumnsU( int column, int count )
{
  blockEdit = false;
  bool result = removeColumns( column, count );
  blockEdit = true;
  return result;
}

void StorageItemModel::appendRow( const QList<QStandardItem *> &items )
{
  if ( blockEdit ) return;
  QStandardItemModel::appendRow( items );
}

void StorageItemModel::appendColumn( const QList<QStandardItem *> &items )
{
  if ( blockEdit ) return;
  QStandardItemModel::appendColumn( items );
}

void StorageItemModel::insertRow( int row, const QModelIndex &parent )
{
  if ( blockEdit ) return;
  QStandardItemModel::insertRow( row, parent );
}

bool StorageItemModel::insertRows( int row, int count, const QModelIndex &parent )
{
  if ( blockEdit ) return false;
  return QStandardItemModel::insertRows( row, count, parent );
}

void StorageItemModel::insertColumn( int column, const QModelIndex &parent )
{
  if ( blockEdit ) return;
  QStandardItemModel::insertColumn( column, parent );
}

bool StorageItemModel::insertColumns( int column, int count, const QModelIndex &parent )
{
  if ( blockEdit ) return false;
  return QStandardItemModel::insertColumns( column, count, parent );
}

bool StorageItemModel::removeRow( int row, const QModelIndex &parent )
{
  if ( blockEdit ) return false;
  return QStandardItemModel::removeRow( row, parent );
}

bool StorageItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
  if ( blockEdit ) return false;
  return QStandardItemModel::removeRows( row, count, parent );
}

bool StorageItemModel::removeColumn( int column, const QModelIndex &parent )
{
  if ( blockEdit ) return false;
  return QStandardItemModel::removeColumn( column, parent );
}

bool StorageItemModel::removeColumns(int column, int count, const QModelIndex &parent)
{
  if ( blockEdit ) return false;
  return QStandardItemModel::removeColumns( column, count, parent );
}

bool StorageItemModel::setHeaderData( const int section, const Qt::Orientation orientation,
                                      const QVariant &value, const int role )
{
  //  if ( blockEdit ) return false;
  return QStandardItemModel::setHeaderData( section, orientation, value, role );
}

bool StorageItemModel::setData( const QModelIndex &/*index*/, const QVariant &/*value*/, const int /*role*/ )
{
  //  return QStandardItemModel::setData( index, value, role );
  return false;
}

bool StorageItemModel::setItemData( const QModelIndex &/*index*/, const QMap<int, QVariant> &/*roles*/ )
{
  //  return QStandardItemModel::setItemData( index, roles );
  return false;
}

void StorageItemModel::setItem( int row, int column, QStandardItem *item )
{
  if ( blockEdit ) return;
  QStandardItemModel::setItem( row, column, item );
}

void StorageItemModel::setItemPrototype( const QStandardItem *item )
{
  if ( blockEdit ) return;
  QStandardItemModel::setItemPrototype( item );
}

void StorageItemModel::drawColumns()
{
  links.clear();
  properties_columns_1.clear();
  properties_columns_2.clear();
//  col_pv.clear();
//  col_name.clear();
  linked_columns.clear();
  renamedColumns.clear();
  removeRowsU( 0, rowCount() );
  removeColumnsU( 0, columnCount() );

  QPair<int, PropertiesView *> linked_1 = qMakePair( -1, m_PropertiesView );
  properties_columns_1.insert( linked_1, QList<int>() );
  foreach( QString propertyName, m_PropertiesView->root()->propertyNames() )
  {
    int column = columnCount();
    insertColumnU( column );
    setHeaderData( column, Qt::Horizontal,
                   propertyName, Qt::DisplayRole );
    properties_columns_1[linked_1] << column;
//    col_pv[column] = m_PropertiesView;
//    col_name[column] = propertyName;

    QPair<PropertiesView*, QString> linked_2 = qMakePair( m_PropertiesView, propertyName );
    if ( !properties_columns_2.contains( linked_2 ) )
      properties_columns_2.insert( linked_2, QList<int>() );
    properties_columns_2[linked_2] << -1;

    renamedColumns[qMakePair( linked_1, propertyName )] = qMakePair( linked_1, propertyName );
  }

  foreach( PropertiesLink *link, m_PropertiesView->availableLinks() )
  {
    PropertiesView *parentPV = PropertiesView::getPropertiesView( link->propertiesViewAlias() );
    const QList<QPair<QString, LinkOptions *> > avLinks = link->availableLinks();
    for ( int lIdx = 0; lIdx < avLinks.count(); lIdx++ )
    {
      links << qMakePair( parentPV, avLinks[lIdx].first );
      PropertiesView *childPV = PropertiesView::getPropertiesView(
            avLinks[lIdx].second->propertiesViewAlias() );
      QPair<int, PropertiesView *> linked_1 = qMakePair( links.count()-1, childPV );
      properties_columns_1.insert( linked_1, QList<int>() );
      foreach( QString propertyName, childPV->root()->propertyNames() )
      {
        int column = columnCount();
        insertColumnU( column );
        setHeaderData( column, Qt::Horizontal,
                       tr( "[%1].[%2]" ).arg( avLinks[lIdx].first, propertyName ), Qt::DisplayRole );
        properties_columns_1[linked_1] << column;
//        col_pv[column] = childPV;
//        col_name[column] = propertyName;

        QPair<PropertiesView*, QString> linked_2 = qMakePair( childPV, propertyName );
        if ( !properties_columns_2.contains( linked_2 ) )
          properties_columns_2.insert( linked_2, QList<int>() );
        properties_columns_2[linked_2] << links.count()-1;

        renamedColumns[qMakePair( linked_1, propertyName )] = qMakePair( linked_1, propertyName );
      }
    }
  }

  for ( int cIdx = 0; cIdx < columnCount(); cIdx++ )
  {
    QHashIterator<QPair<int, PropertiesView *>, QList<int> > i = properties_columns_1;
    while( i.hasNext() )
    {
      i.next();
      if ( i.value().contains( cIdx ) )
      {
        PropertiesView *parentPV = i.key().second;
        QString propertyName = i.key().second->root()->propertyNames()[i.value().indexOf( cIdx )];
        int linkIndex = links.indexOf( qMakePair( parentPV, propertyName ) );
        QList<LinkOptions *> options = parentPV->propertiesLink()->linksByParentProperty( propertyName );
        foreach ( LinkOptions *option, options )
        {
          PropertiesView *childPV = PropertiesView::getPropertiesView( option->propertiesViewAlias() );
          QList<int> columns = properties_columns_1[qMakePair( linkIndex, childPV )];
          QList<int> linkedColumns = QList<int>();

          foreach ( QString visiblePName, option->visiblePropertyNames() )
            linkedColumns << columns[childPV->root()->propertyNames().indexOf( visiblePName )];

          linked_columns.insert( cIdx, linkedColumns );
        }
      }
    }
  }
}

void StorageItemModel::drawRecord( int row, MFCRecord *parent, MFCRecord *record )
{
  if ( m_VisibleRecords[row] == record )
    for ( int cIdx = 0; cIdx < columnCount(); cIdx++ )
      QStandardItemModel::setData( index( row, cIdx ), QString(), Qt::DisplayRole );

  if ( record->propertiesView() == m_PropertiesView )
  {
    QList<int> columns = properties_columns_1[qMakePair( -1, m_PropertiesView )];

    for ( int pIdx = 0; pIdx < record->properties()->propertyNames().count(); pIdx++ )
    {
      QString propertyName = record->properties()->propertyNames()[pIdx];
      QVariant val = record->currentProperty( propertyName );
      QStandardItemModel::setData( index( row, columns[pIdx] ), val, Qt::DisplayRole );
      if ( indexedTypes.contains( record->properties()->propertyType( propertyName ) ) )
      {
        if ( !m_IndexedRecords.contains( propertyName ) )
          m_IndexedRecords.insert( propertyName, QHash<QString, MFCRecord *>() );
        m_IndexedRecords[propertyName].insert( val.toString(), record );
      }
    }
  }
  else
  {
    QList<QPair<PropertiesView *, QString> > confirmedLinks =
        QList<QPair<PropertiesView *, QString> >();
    foreach ( QString parentPName, parent->keyFieldForChild( record ) )
        confirmedLinks << qMakePair( parent->propertiesView(), parentPName );

    for ( int lIdx = 0; lIdx < confirmedLinks.count(); lIdx++ )
    {
      QList<int> columns = properties_columns_1[qMakePair(
            links.indexOf( confirmedLinks[lIdx] ), record->propertiesView() )];

      for ( int pIdx = 0; pIdx < record->properties()->propertyNames().count(); pIdx++ )
      {
        QString propertyName = record->properties()->propertyNames()[pIdx];
        QVariant val = record->currentProperty( propertyName );
        QStandardItemModel::setData( index( row, columns[pIdx] ), val, Qt::DisplayRole );
      }
    }
  }

  foreach ( MFCRecord *child, record->childrenRecord() ) drawRecord( row, record, child );
}

QString StorageItemModel::getVisibleData( int row, QList<int> columns )
{
  QStringList result = QStringList();
  foreach ( int column, columns )
  {
    QVariant val = index( row, column ).data();
    QString value = QString();
    switch ( val.type() )
    {
    case QVariant::DateTime:
    {
      value = val.toDateTime().toString( "dd.MM.yyyy hh:mm" );
      break;
    }
    case QVariant::Date:
    {
      value = val.toDateTime().toString( "dd.MM.yyyy" );
      break;
    }
    case QVariant::Time:
    {
      value = val.toDateTime().toString( "hh:mm" );
      break;
    }
    default:
    {
      value = val.toString();
      break;
    }
    }

    result << value;
  }

  return result.join( tr( " " ) ).simplified();
}

void StorageItemModel::createConnect( MFCRecord *rootRecord )
{
  foreach( MFCRecord *child, rootRecord->childrenRecord() )
    createConnect( child );

  connectSingleRecord( rootRecord );
}

void StorageItemModel::removeConnect( MFCRecord *rootRecord )
{
  foreach( MFCRecord *child, rootRecord->childrenRecord() )
    removeConnect( child );

  disconnectSingleRecord( rootRecord );
}

void StorageItemModel::removeIndex( MFCRecord *rootRecord )
{
  QString nullKey = QUuid::createUuid().toString();
  QHashIterator<QString, QHash<QString, MFCRecord *> > i( m_IndexedRecords );
  while ( i.hasNext() )
  {
    i.next();
    QString key = i.value().key( rootRecord, nullKey );
    if ( key != nullKey ) m_IndexedRecords[i.key()].remove( key );
  }
}

void StorageItemModel::quicksort(int l, int r)
{
  int i = l-1, j = r, p = l-1, q = r;
  if (r <= l) return;
  MFCRecord *v = m_AvailableRecords[r];
  for (;;)
    {
      while (!m_Sort->comparison(m_AvailableRecords[++i], v)/*m_AvailableRecords[++i] < v*/)
      {
        if (i == r) break;
      }
      while (!m_Sort->comparison(v, m_AvailableRecords[--j]))
      {
        if (j == l) break;
      }
      if (i >= j) break;
      m_AvailableRecords.swap(i,j);
      if (m_Sort->comparison(m_AvailableRecords[i], v)) {
        p++;
        m_AvailableRecords.swap(p, i);
      }
      if (m_Sort->comparison(v, m_AvailableRecords[j])) {
        q--;
        m_AvailableRecords.swap(j, q);
      }
    }
  m_AvailableRecords.swap(i, r);
  j = i-1;
  i = i+1;
  for (int k = l; k < p; k++, j--){
    m_AvailableRecords.swap(k, j);
  }
  for (int k = r-1; k > q; k--, i++){
    m_AvailableRecords.swap(i, k);
  }
  quicksort(l, j);
  quicksort(i, r);
}

void StorageItemModel::smallsort()
{
  while ( !m_NotSorted.isEmpty() )
  {
    MFCRecord *rootRecord = m_NotSorted.takeFirst();
    int index = m_AvailableRecords.indexOf( rootRecord );
//    qDebug() << "smallsort UP============";;
    for ( int rIdx = index; rIdx > 0; rIdx-- )
    {
      int prevRecord = rIdx-1;
      MFCRecord *record_1 = m_AvailableRecords[prevRecord];
      MFCRecord *record_2 = m_AvailableRecords[rIdx];
      if ( m_Sort->comparison( record_1, record_2 ) )
      {
        index = prevRecord;
        //        m_AvailableRecords.removeAt( rIdx );
        //        m_AvailableRecords.insert( prevRecord, record_2 );
        //        QUuid uuid = m_RecordsUuid.takeAt( rIdx );
        //        m_RecordsUuid.insert( prevRecord, uuid );
        m_AvailableRecords.swap( rIdx, prevRecord );
        m_RecordsUuid.swap( rIdx, prevRecord );
      }
      else break;
    }
//    qDebug() << "smallsort DOWN==========";;
    for ( int rIdx = index; rIdx < m_AvailableRecords.count()-1; rIdx++ )
    {
      int nextRecord = rIdx+1;
      MFCRecord *record_1 = m_AvailableRecords[rIdx];
      MFCRecord *record_2 = m_AvailableRecords[nextRecord];
      if ( m_Sort->comparison( record_1, record_2 ) )
      {
        index = nextRecord;
        //        m_AvailableRecords.removeAt( nextRecord );
        //        m_AvailableRecords.insert( rIdx, record_2 );
        //        QUuid uuid = m_RecordsUuid.takeAt( nextRecord );
        //        m_RecordsUuid.insert( rIdx, uuid );
        m_AvailableRecords.swap( rIdx, nextRecord );
        m_RecordsUuid.swap( rIdx, nextRecord );
      }
      else break;
    }
  }
}

void StorageItemModel::propertiesModified()
{
  drawColumns();
  for ( int rIdx = 0; rIdx < m_VisibleRecords.count(); rIdx++ )
  {
    insertRowU( rIdx );
    drawRecord( rIdx, 0, m_VisibleRecords[rIdx] );
  }
}

void StorageItemModel::valueChanged( QString p_Name, QVariant old_Value, QVariant new_Value )
{
  MFCRecord *record = qobject_cast<MFCRecord *>( sender() );
  if ( record->propertiesView() == m_PropertiesView  )
  {
    QPair<int, PropertiesView *> link = qMakePair( -1, m_PropertiesView );
    int p_Index = record->propertiesView()->root()->propertyNames().indexOf( p_Name );

    int row = m_VisibleRecords.indexOf( record );
    int column = properties_columns_1.value( link, QList<int>() ).value( p_Index, -1 );
    /*bool res = */QStandardItemModel::setData(
        index( row, column ), record->currentProperty( p_Name ) );

    if ( m_IndexedRecords.contains( p_Name ) )
      if ( m_IndexedRecords[p_Name].values().contains( record ) )
      {
        m_IndexedRecords[p_Name].remove( m_IndexedRecords[p_Name].key( record ) );
        m_IndexedRecords[p_Name].insert( record->currentProperty( p_Name ).toString(), record );
      }

    QList<LinkOptions *> avLinks = m_PropertiesView->propertiesLink()->linksByParentProperty( p_Name );
    foreach ( LinkOptions *avLink, avLinks )
    {
      MFCRecord *oldChild = 0;

      foreach ( MFCRecord *child, record->childrenRecord() )
        if ( child->propertiesView()->alias() == avLink->propertiesViewAlias() &&
             child->currentProperty( avLink->propertyName() ) == old_Value )
          oldChild = child;

      StorageItemModel *extStorage = externalStorage( avLink->propertiesViewAlias() );
      if ( extStorage != NULL )
      {
        MFCRecord *newChild = extStorage->findByIndex(
              avLink->propertyName(), new_Value );

        if ( oldChild != 0 )
          if ( record->keyFieldForChild( oldChild ).count() == 1 )
            record->removeChildRecord( oldChild );

        record->addChildRecord( newChild );
      }
    }

    if ( m_Sort != 0 && m_Sort->paramNames( record->propertiesView() ).contains( p_Name ) )
      m_NotSorted << record;
    reindexRecord( row );
  }
  else
  {
    QList<int> linkIndexes = properties_columns_2[qMakePair( record->propertiesView(), p_Name )];
    QList<PropertiesView *> confirmedPV = QList<PropertiesView *>();
    QList<QPair<PropertiesView *, QString> > confirmedLinks = QList<QPair<PropertiesView *, QString> >();
    foreach ( MFCRecord *parentRecord, record->parentRecords() )
    {
      MFCRecord *confirmedParent = 0;
      if ( !confirmedPV.contains( parentRecord->propertiesView() ) )
      {
        if ( m_PropertiesView->findPropertiesLink( parentRecord->propertiesView() ) != 0 )
        {
          confirmedPV << parentRecord->propertiesView();
          confirmedParent = parentRecord;
        }
      }
      else confirmedParent = parentRecord;
      if ( confirmedParent != 0 )
      {
        QList<QPair<QString, LinkOptions *> > fLinks =
            confirmedParent->propertiesLink()->links( record->propertiesView()->alias() );
        for ( int lIdx = 0; lIdx < fLinks.count(); lIdx++ )
          if ( fLinks[lIdx].second->propertyName() == p_Name )
          {
            if ( confirmedParent->currentProperty( fLinks[lIdx].first ) == old_Value )
              confirmedLinks << qMakePair( record->propertiesView(), fLinks[lIdx].second->propertyName() );
          }
          else if ( confirmedParent->currentProperty(
                      fLinks[lIdx].first ) == record->currentProperty(
                      fLinks[lIdx].second->propertyName() ) )
            confirmedLinks << qMakePair( record->propertiesView(), fLinks[lIdx].second->propertyName() );
      }
    }

    QList<int> confirmedIndexes = QList<int>();
    foreach( int lIndex, linkIndexes )
      if ( confirmedLinks.contains( links[lIndex] ) )
        confirmedIndexes << lIndex;

    foreach ( MFCRecord *rootRecord, record->getRootRecords( m_PropertiesView ) )
    {
      int row = m_VisibleRecords.indexOf( rootRecord );
      foreach( int lIndex, confirmedIndexes )
      {
        int p_Index = record->propertiesView()->root()->propertyNames().indexOf( p_Name );
        QList<int> columns = properties_columns_1.value(
              qMakePair( lIndex, record->propertiesView() ), QList<int>() );
        int column = columns.value( p_Index, -1 );
        /*bool res = */QStandardItemModel::setData(
            index( row, column ), record->currentProperty( p_Name ) );
      }
      if ( m_Sort != 0 && m_Sort->paramNames( record->propertiesView() ).contains( p_Name ) )
        m_NotSorted << rootRecord;
      reindexRecord( row );
    }
  }
}

void StorageItemModel::dataReversed()
{
  MFCRecord *record = qobject_cast<MFCRecord *>( sender() );
  reindexRecord( m_VisibleRecords.indexOf( record ) );
}

void StorageItemModel::recordDestroyed( QUuid uuid )
{
  int idx = m_RecordsUuid.indexOf( uuid );
  if ( idx != -1 )
  {
    MFCRecord *rootRecord = (MFCRecord *)sender();
    if ( rootRecord != NULL ) removeRecord( rootRecord );

    m_AvailableRecords.takeAt( idx );
    for ( int recIdx = m_NotSorted.count()-1; recIdx > -1; recIdx-- )
      if ( m_NotSorted[recIdx] == 0 ) m_NotSorted.removeAt( recIdx );
    m_RecordsUuid.removeAt( idx );
    for ( int recIdx = m_VisibleRecords.count()-1; recIdx > -1; recIdx-- )
    {
      if ( m_VisibleRecords[recIdx]->uuid() == uuid )
      {
        m_VisibleRecords.removeAt( recIdx );
        removeRowU( recIdx );
      }
    }
    for ( int recIdx = m_NewRecords.count()-1; recIdx > -1; recIdx-- )
      if ( m_NewRecords[recIdx]->uuid() == uuid )
        m_NewRecords.removeAt( recIdx );
  }
}

void StorageItemModel::connectSingleRecord( MFCRecord *record )
{
//  connect( record, SIGNAL(propertyChanged(QString)), this, SLOT(valueChanged(QString)) );
  connect( record, SIGNAL(propertyChanged(QString,QVariant,QVariant)),
           this, SLOT(valueChanged(QString,QVariant,QVariant)) );
  connect( record, SIGNAL(dataReversed()), this, SLOT(dataReversed()) );
  if ( record->propertiesView() == m_PropertiesView )
    connect( record, SIGNAL(recordDestroyed(QUuid)), this, SLOT(recordDestroyed(QUuid)) );
  connect( record, SIGNAL(childAdded(MFCRecord*)), this, SLOT(connectSingleRecord(MFCRecord*)) );
  connect( record, SIGNAL(childReplaced(MFCRecord*,MFCRecord*)),
           this, SLOT(childReplaced(MFCRecord*,MFCRecord*)) );
}

void StorageItemModel::disconnectSingleRecord( MFCRecord *record )
{
//  disconnect( record, SIGNAL(propertyChanged(QString)), this, SLOT(valueChanged(QString)) );
  disconnect( record, SIGNAL(propertyChanged(QString,QVariant,QVariant)),
              this, SLOT(valueChanged(QString,QVariant,QVariant)) );
  disconnect( record, SIGNAL(dataReversed()), this, SLOT(dataReversed()) );
  if ( record->propertiesView() == m_PropertiesView )
    disconnect( record, SIGNAL(recordDestroyed(QUuid)), this, SLOT(recordDestroyed(QUuid)) );
  disconnect( record, SIGNAL(childAdded(MFCRecord*)), this, SLOT(connectSingleRecord(MFCRecord*)) );
  disconnect( record, SIGNAL(childReplaced(MFCRecord*,MFCRecord*)),
              this, SLOT(childReplaced(MFCRecord*,MFCRecord*)) );
}

void StorageItemModel::childReplaced( MFCRecord *old_record, MFCRecord *new_record )
{
  if ( old_record->parentRecords().count() == 0 )
    disconnectSingleRecord( old_record );

  connectSingleRecord( new_record );
}

void StorageItemModel::filterDestroyed()
{
  m_Filter = NULL;

  foreach ( MFCRecord *record, m_AvailableRecords ) setRecordVisible( record );
}

void StorageItemModel::sortDestroyed()
{
  m_Sort = 0;
}

void StorageItemModel::externalStorageDestroyed( QObject *obj )
{
  StorageItemModel *extStorage = (StorageItemModel *)obj;

  PropertiesView *pv_ExtStorage = extStorage->getPropertiesView();

  m__ExternalStorages.removeOne( extStorage );
  m__ExtStgs_PV.remove( pv_ExtStorage );
  m__ExtStgs_Alias.remove( pv_ExtStorage->alias() );
  m__DeletableStorages.removeOne( extStorage );
}
