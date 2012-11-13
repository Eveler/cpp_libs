#include "propertiessqlworker.h"
#include <QSqlRecord>
#include <QSqlField>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlIndex>
#include <QDateTime>

QHash<QString, PropertiesSqlWorker *> PropertiesSqlWorker::m_PSW = QHash<QString, PropertiesSqlWorker *>();
PropertiesSqlWorker *PropertiesSqlWorker::null_PSW = new PropertiesSqlWorker();

SqlResult::SqlResult( QSqlError error, QSqlQuery *query )
{
  m_SqlError = error;
  m_SqlQuery = query;
}

SqlResult::~SqlResult()
{
  delete m_SqlQuery;
  m_SqlQuery = NULL;
}

QSqlError SqlResult::sqlError() const
{
  return m_SqlError;
}

QSqlQuery * SqlResult::sqlQuery() const
{
  return m_SqlQuery;
}

PropertiesSqlWorker & PropertiesSqlWorker::instance( QString alias, QSqlDatabase &db )
{
  if ( alias.simplified().isEmpty() || !db.isValid() ) return *null_PSW;
  if ( !m_PSW.contains( alias ) ) m_PSW.insert( alias, new PropertiesSqlWorker( alias, db ) );

  return *m_PSW[alias];
}

void PropertiesSqlWorker::remove( QString alias )
{
  if ( !m_PSW.contains( alias ) ) return;
  PropertiesSqlWorker *psw = m_PSW.take( alias );
  delete psw;
}

QString PropertiesSqlWorker::preparePsName( const QString &ps_Name )
{
  if ( ps_Name.simplified().isEmpty() ) return QString( "" );

  bool quote = false;
  if ( ps_Name == QObject::tr( "operator" ) || ps_Name == QObject::tr( "name" ) )
    quote = true;
  else foreach( QChar c, ps_Name )
    if ( ( c.isLetter() && c.isUpper() ) ||
         c == QObject::tr( " " ).at( 0 ) || c == QObject::tr( "-" ).at( 0 ) ) quote = true;
  return QString( quote ? QObject::tr( "\"%1\"" ).arg( ps_Name ) : ps_Name );
}

const QString & PropertiesSqlWorker::alias() const
{
  return (*m_Alias);
}

bool PropertiesSqlWorker::isValid()
{
  return m_DB.isValid();
}

QSqlDatabase PropertiesSqlWorker::database() const
{
  return m_DB;
}

Properties * PropertiesSqlWorker::prepareProperties( QString ps_Name )
{
  if ( !m_DB.isValid() )
  {
    qDebug() <<"m_DB.isValid()" << m_DB.isValid();
    return 0;
  }
  Properties * ps = Properties::addProperties( ps_Name );

  SqlResult *result = PropertiesSqlWorker::loadProperties( ps );
//  qDebug() <<QObject::tr( "ps_Name" ) << ps_Name <<
//          QObject::tr( "result->sqlError().isValid()" ) << result->sqlError().isValid();
  QSqlIndex sIdx=m_DB.primaryIndex(ps_Name);
  for(int i=0;i<sIdx.count();i++)
    ps->addPrimaryKey(sIdx.field(i).name(),sIdx.field(i).type());
  QSqlRecord rec = result->sqlQuery()->record();
  for ( int cIdx = 0; cIdx < rec.count(); cIdx++ )
    ps->addProperty( rec.field( cIdx ).name(), rec.field( cIdx ).type() );
  delete result;

  return ps;
}

SqlResult * PropertiesSqlWorker::loadProperties( Properties *properties )
{
  if ( !m_DB.isValid() ) return new SqlResult( QSqlError( QString(), QObject::tr( "DB is not valid" ),
                                                          QSqlError::UnknownError ),
                                               new QSqlQuery( m_DB ) );
  if ( m_DB.isOpenError() ) return new SqlResult( m_DB.lastError(), new QSqlQuery( m_DB ) );
  if ( properties == 0 )
    return new SqlResult( QSqlError( QString(), QObject::tr( "Storage = 0" ), QSqlError::UnknownError ),
                          new QSqlQuery( m_DB ) );
  if ( properties->isNull() )
    return new SqlResult( QSqlError( QString(), QObject::tr( "Storage is null" ), QSqlError::UnknownError ),
                          new QSqlQuery( m_DB ) );

  QString query_text = QObject::tr( "SELECT * FROM %1 LIMIT 0" ).arg( properties->name() );

  if ( !m_DB.isOpen() ) m_DB.open();

  QSqlQuery *qry = new QSqlQuery( query_text, m_DB );
//  qDebug() <<QObject::tr( "qry.isSelect()" ) << qry.isSelect();
  return new SqlResult( qry->lastError(), qry );
}

SqlResult * PropertiesSqlWorker::load( Properties *properties,
                                       QString filter, QString order )
{
  if ( !m_DB.isValid() ) return new SqlResult( QSqlError( QString(), QObject::tr( "DB is not valid" ),
                                                          QSqlError::UnknownError ),
                                               new QSqlQuery( m_DB ) );
  if ( m_DB.isOpenError() ) return new SqlResult( m_DB.lastError(), new QSqlQuery( m_DB ) );
  if ( properties == 0 )
    return new SqlResult( QSqlError( QString(), QObject::tr( "Storage = 0" ),
                                     QSqlError::UnknownError ),
                          new QSqlQuery( m_DB ) );
  if ( properties->isNull() )
    return new SqlResult( QSqlError( QString(), QObject::tr( "Storage is null" ),
                                     QSqlError::UnknownError ),
                          new QSqlQuery( m_DB ) );
  if ( properties->propertyNames().count() == 0 )
    return new SqlResult( QSqlError( QString(), QObject::tr( "Storage is empty" ),
                                     QSqlError::UnknownError ),
                          new QSqlQuery( m_DB ) );

  QStringList fieldNames = QStringList();
  foreach ( QString p_Name, properties->propertyNames() )
    fieldNames << preparePsName( p_Name );

  QString query_text = QObject::tr( "SELECT %1 FROM %2" ).arg(
        fieldNames.join( QObject::tr( ", " ) ), preparePsName( properties->name() ) );
  if ( !filter.isEmpty() )
    query_text += " WHERE "+filter;
  if ( !order.isEmpty() )
    query_text += " ORDER BY "+order;

  if ( !m_DB.isOpen() ) m_DB.open();

  QSqlQuery *qry = new QSqlQuery( m_DB );
  qry->exec( query_text );
  QSqlError err( qry->lastError() );
  if ( qry->lastError().isValid() )
    err.setDatabaseText( qry->lastError().databaseText()+"\nSQL query: "+query_text );
  return new SqlResult( err, qry );
}

SqlResult * PropertiesSqlWorker::notExists(
    Properties *properties, QStringList exists, const QString &keyField )
{
  if ( !m_DB.isValid() ) return new SqlResult( QSqlError( QString(), QObject::tr( "DB is not valid" ),
                                                          QSqlError::UnknownError ),
                                               new QSqlQuery( m_DB ) );
  if ( m_DB.isOpenError() ) return new SqlResult( m_DB.lastError(), new QSqlQuery( m_DB ) );
  if ( properties == 0 )
    return new SqlResult( QSqlError( QString(), QObject::tr( "Storage = 0" ),
                                     QSqlError::UnknownError ),
                          new QSqlQuery( m_DB ) );
  if ( properties->isNull() )
    return new SqlResult( QSqlError( QString(), QObject::tr( "Storage is null" ),
                                     QSqlError::UnknownError ),
                          new QSqlQuery( m_DB ) );
  if ( properties->propertyNames().count() == 0 )
    return new SqlResult( QSqlError( QString(), QObject::tr( "Storage is empty" ),
                                     QSqlError::UnknownError ),
                          new QSqlQuery( m_DB ) );

  QSqlQuery *qry = new QSqlQuery( m_DB );
  if ( exists.isEmpty() )
  {
    QSqlError err;
    return new SqlResult( err, qry );
  }

  QString table = preparePsName( properties->name() );
  QString field = preparePsName( keyField );

  QString query_text = QObject::tr(
        "SELECT t1.%1 FROM (SELECT unnest(ARRAY[%2]) AS %1) t1 "
        "WHERE NOT EXISTS (SELECT t2.%1 FROM %3 t2 WHERE t2.%1=t1.%1)" ).arg(
        field, exists.join( "," ), table );

  qry->exec( query_text );
  QSqlError err( qry->lastError() );
  if ( qry->lastError().isValid() )
    err.setDatabaseText( qry->lastError().databaseText()+"\nSQL query: "+query_text );
  return new SqlResult( err, qry );
}

SqlResult * PropertiesSqlWorker::nextVal( Properties *properties )
{
  if ( !m_DB.isValid() ) return new SqlResult( QSqlError( QString(), QObject::tr( "DB is not valid" ),
                                                          QSqlError::UnknownError ),
                                               new QSqlQuery( m_DB ) );
  if ( m_DB.isOpenError() ) return new SqlResult( m_DB.lastError(),
                                                  new QSqlQuery( m_DB ) );
  if ( properties == 0 )
    return new SqlResult( QSqlError( QString(), QObject::tr( "Storage = 0" ),
                                     QSqlError::UnknownError ), new QSqlQuery( m_DB ) );
  if ( properties->isNull() )
    return new SqlResult( QSqlError( QString(), QObject::tr( "Storage is null" ),
                                     QSqlError::UnknownError ), new QSqlQuery( m_DB ) );
  if ( properties->propertyNames().count() == 0 )
    return new SqlResult( QSqlError( QString(), QObject::tr( "Storage is empty" ),
                                     QSqlError::UnknownError ), new QSqlQuery( m_DB ) );

  QStringList qry_fields = QStringList();
  QStringList check_fields = QStringList();
  PgTable *table = m_PgDB->table( properties->name() );
  foreach ( QString primaryKey, table->primaryKeyFields() )
    foreach ( QString sequence ,table->sequences() )
      if ( table->fieldDefValue( primaryKey ).toString().contains( sequence ) )
      {
        qry_fields << QObject::tr( "%1 AS %2" ).arg(
                        table->fieldDefValue( primaryKey ).toString(),
                        preparePsName( primaryKey ) );
        check_fields << preparePsName( primaryKey );
      }

  if ( qry_fields.count() > 0 )
  {
    QString query_text = QObject::tr( "SELECT %1" ).arg( qry_fields.join( ", " ) );
    QSqlQuery *qry = new QSqlQuery( m_DB );
    QSqlQuery *checkCurrVal = new QSqlQuery( m_DB );
    do
    {
      if ( !qry->exec( query_text ) )
      {
        qDebug() <<qry->lastError().text();
        qDebug() <<"Query text:" << query_text;
      }
      qry->next();
      QStringList checkValues = QStringList();
      for ( int cIdx = 0; cIdx < qry->record().count(); cIdx++ )
        checkValues << QObject::tr( "%1=%2" ).arg(
                         check_fields[cIdx], qry->record().value( cIdx ).toString() );
      QString check_text = QObject::tr( "SELECT count(*) FROM %1 WHERE %2" ).arg(
            properties->name(), checkValues.join( " AND " ) );
      checkCurrVal->exec( check_text );
      checkCurrVal->next();
      qry->first();
    } while ( checkCurrVal->record().value( 0 ).toInt() != 0 );
    delete checkCurrVal;
    checkCurrVal = NULL;
    return new SqlResult( qry->lastError(), qry );
  }

  return new SqlResult( QSqlError( QString(), QObject::tr( "Sequences is not available "
                                                           "for table: %1" ).arg( properties->name() ),
                                   QSqlError::UnknownError ), new QSqlQuery( m_DB ) );
}

SqlResult * PropertiesSqlWorker::nextVal( QString sequenceName )
{
  if ( !m_DB.isValid() ) return new SqlResult( QSqlError( QString(), QObject::tr( "DB is not valid" ),
                                                          QSqlError::UnknownError ),
                                               new QSqlQuery( m_DB ) );
  if ( m_DB.isOpenError() ) return new SqlResult( m_DB.lastError(), new QSqlQuery( m_DB ) );

  QString query_text = QObject::tr( "SELECT nextval('%1')" ).arg( sequenceName );
  QSqlQuery *qry = new QSqlQuery( m_DB );
  qry->exec( query_text );
  return new SqlResult( qry->lastError(), qry );
}

bool PropertiesSqlWorker::transaction()
{
  if ( !m_DB.isValid() || m_InTransaction ) return false;
  bool result = m_DB.transaction();
  if ( result ) m_InTransaction = result;
  return result;
}

bool PropertiesSqlWorker::commit()
{
  if ( isInTransaction() )
    while ( !recordsInTransaction.isEmpty() )
    {
      QPair<MFCRecord *, bool> record = recordsInTransaction.takeFirst();
      record.first->dataSync();
    }
  m_InTransaction = false;
  if ( !m_DB.isValid() ) return false;
  return m_DB.commit();
}

bool PropertiesSqlWorker::rollback()
{
  if ( isInTransaction() )
  {
    qDebug() <<recordsInTransaction.count();
    while ( !recordsInTransaction.isEmpty() )
    {
      QPair<MFCRecord *, bool> record = recordsInTransaction.takeFirst();
      qDebug() <<record.first->properties()->name();
    }
  }
  m_InTransaction = false;
  if ( !m_DB.isValid() ) return false;
  return m_DB.rollback();
}

QSqlError PropertiesSqlWorker::saveRecord( MFCRecord *record, bool isNew, bool ignoreFirstAsPrimary )
{
  if ( record == 0 ) return QSqlError( QString(), QObject::tr( "record is null" ),
                                       QSqlError::UnknownError );

  if ( isInTransaction() )
    recordsInTransaction << qMakePair( record, isNew );
  QStringList fieldNames = QStringList();
  QStringList fieldValues = QStringList();
  QStringList insertFields = QStringList();
  QStringList insertValues = QStringList();

  foreach ( QString p_Name, record->properties()->propertyNames() )
  {
    fieldNames << preparePsName( p_Name );

    QVariant value = record->currentProperty( p_Name );
    if ( value.isNull() )
      fieldValues << QObject::tr( "NULL" );
    else
    {
      switch ( record->properties()->propertyType( p_Name ) )
      {
      case QVariant::String:
      {
        fieldValues << QObject::tr( "'%1'" ).arg( value.toString() );
        break;
      }
      case QVariant::DateTime:
      {
        if ( value.toString().isEmpty() )
          fieldValues << QObject::tr( "NULL" );
        else
          fieldValues << QObject::tr( "'%1'" ).arg(
                           value.toDateTime().toString( QObject::tr( "dd.MM.yyyy hh:mm:ss.zzz" ) ) );
        break;
      }
      case QVariant::Date:
      {
        if ( value.toString().isEmpty() )
          fieldValues << QObject::tr( "NULL" );
        else
          fieldValues << QObject::tr( "'%1'" ).arg(
                           value.toDateTime().toString( QObject::tr( "dd.MM.yyyy" ) ) );
        break;
      }
      case QVariant::Time:
      {
        if ( value.toString().isEmpty() )
          fieldValues << QObject::tr( "NULL" );
        else
          fieldValues << QObject::tr( "'%1'" ).arg(
                           value.toDateTime().toString( QObject::tr( "hh:mm:ss.zzz" ) ) );
        break;
      }
      case QVariant::Int:
      {
        fieldValues << value.toString();
        break;
      }
      case QVariant::UInt:
      {
        fieldValues << value.toString();
        break;
      }
      case QVariant::Double:
      {
        fieldValues << value.toString();
        break;
      }
      case QVariant::LongLong:
      {
        fieldValues << value.toString();
        break;
      }
      case QVariant::ULongLong:
      {
        fieldValues << value.toString();
        break;
      }
      default:
      {
        fieldValues << value.toString();
        break;
      }
      }
    }

    if ( fieldValues.last() != QObject::tr( "NULL" ) )
    {
      insertFields << fieldNames.last();
      insertValues << fieldValues.last();
    }
  }

  if ( isNew )
  {
    if ( ignoreFirstAsPrimary )
      if ( fieldNames.first() == insertFields.first() )
      {
        insertFields.removeFirst();
        insertValues.removeFirst();
      }

    QString sqlText = QObject::tr( "INSERT INTO %1(%2) VALUES(%3)" ).arg(
          record->properties()->name(), insertFields.join( ", " ), insertValues.join( ", " ) );

    QSqlQuery *qry = new QSqlQuery( m_DB );
    if ( !qry->exec( sqlText ) )
    {
      QSqlError err = qry->lastError();
      err.setDatabaseText( err.databaseText()+"\nSql text: "+sqlText );
      rollback();
      delete qry;
      qry = NULL;
      return err;
    }

    QStringList filter = QStringList();
    while ( !insertFields.isEmpty() )
    {
      QString fieldName = insertFields.takeFirst();
      QString fieldValue = insertValues.takeFirst();
      if ( fieldValue == QObject::tr( "NULL" ) )
        filter << ( fieldName+QObject::tr( " IS " )+fieldValue );
      else
        filter << ( fieldName+QObject::tr( "=" )+fieldValue );
    }

    sqlText = QObject::tr( "SELECT * FROM %1 WHERE %2" ).arg(
          record->properties()->name(), filter.join( QObject::tr( " AND " ) ) );
    QSqlQueryModel *queryModel = new QSqlQueryModel();
    queryModel->setQuery( sqlText, m_DB );

    if ( queryModel->lastError().isValid() )
    {
      QSqlError err = queryModel->lastError();
      rollback();
      delete queryModel;
      queryModel = NULL;
      return err;
    }
    if ( queryModel->rowCount() == 0 )
    {
      rollback();
      return QSqlError( QString(), "No result!", QSqlError::UnknownError );
    }

    for ( int cIdx = 0; cIdx < queryModel->columnCount(); cIdx++ )
    {
      if ( queryModel->index( 0, cIdx ).data() != record->currentProperty(
             queryModel->record().fieldName( cIdx ) ) )
        record->setCurrentProperty( queryModel->record().fieldName( cIdx ),
                                    queryModel->index( 0, cIdx ).data() );
//      table->setData( row, cIdx, queryModel->index( 0, cIdx ).data() );
    }

    delete queryModel;
    queryModel = NULL;
  }
  else
  {
    QStringList update = QStringList();
    QString filter = fieldNames.takeFirst()+"="+fieldValues.takeFirst();
    while ( !fieldNames.isEmpty() )
      update << ( fieldNames.takeFirst()+"="+fieldValues.takeFirst() );
    QString sqlText = QObject::tr( "UPDATE %1 SET %2 WHERE %3" ).arg(
          record->properties()->name(), update.join( ", " ), filter );
    QSqlQuery *qry = new QSqlQuery( m_DB );
    if ( !qry->exec( sqlText ) )
    {
      QSqlError err = qry->lastError();
      err.setDatabaseText( err.databaseText()+"\nSql text: "+sqlText );
      rollback();
      delete qry;
      qry = NULL;
      return err;
    }
  }

  return QSqlError();
}

QSqlError PropertiesSqlWorker::saveChanges( MFCRecord *record )
{
  if ( record == 0 ) return QSqlError( QString(), QObject::tr( "record is null" ),
                                       QSqlError::UnknownError );

  if ( isInTransaction() )
    recordsInTransaction << qMakePair( record, false );

  QStringList fieldNames = QStringList();
  QStringList fieldValues = QStringList();

  QStringList changedProperties = record->changedProperties();
  if ( changedProperties.isEmpty() ) return QSqlError();
  if ( !changedProperties.contains( record->properties()->propertyNames().first() ) )
    changedProperties.insert( 0, record->properties()->propertyNames().first() );

  foreach ( QString p_Name, changedProperties )
  {
    fieldNames << preparePsName( p_Name );

    QVariant value = record->currentProperty( p_Name );
    if ( value.isNull() )
      fieldValues << QObject::tr( "NULL" );
    else
    {
      switch ( record->properties()->propertyType( p_Name ) )
      {
      case QVariant::String:
      {
        fieldValues << QObject::tr( "'%1'" ).arg( value.toString() );
        break;
      }
      case QVariant::DateTime:
      {
        if ( value.toString().isEmpty() )
          fieldValues << QObject::tr( "NULL" );
        else
          fieldValues << QObject::tr( "'%1'" ).arg(
                           value.toDateTime().toString( QObject::tr( "dd.MM.yyyy hh:mm:ss.zzz" ) ) );
        break;
      }
      case QVariant::Date:
      {
        if ( value.toString().isEmpty() )
          fieldValues << QObject::tr( "NULL" );
        else
          fieldValues << QObject::tr( "'%1'" ).arg(
                           value.toDateTime().toString( QObject::tr( "dd.MM.yyyy" ) ) );
        break;
      }
      case QVariant::Time:
      {
        if ( value.toString().isEmpty() )
          fieldValues << QObject::tr( "NULL" );
        else
          fieldValues << QObject::tr( "'%1'" ).arg(
                           value.toDateTime().toString( QObject::tr( "hh:mm:ss.zzz" ) ) );
        break;
      }
      case QVariant::Int:
      {
        fieldValues << value.toString();
        break;
      }
      case QVariant::UInt:
      {
        fieldValues << value.toString();
        break;
      }
      case QVariant::Double:
      {
        fieldValues << value.toString();
        break;
      }
      case QVariant::LongLong:
      {
        fieldValues << value.toString();
        break;
      }
      case QVariant::ULongLong:
      {
        fieldValues << value.toString();
        break;
      }
      default:
      {
        fieldValues << value.toString();
        break;
      }
      }
    }
  }

//  QString sqlText = ( isNew ? tr( "INSER INTO %1(%2) VALUES(%3)" ) :
//                              tr( "UPDATE %1 SET %2 WHERE %3" ) );

  if ( !fieldNames.isEmpty() )
  {
    QStringList update = QStringList();
    QString filter = fieldNames.takeFirst()+"="+fieldValues.takeFirst();
    while ( !fieldNames.isEmpty() )
      update << ( fieldNames.takeFirst()+"="+fieldValues.takeFirst() );
    QString sqlText = QObject::tr( "UPDATE %1 SET %2 WHERE %3" ).arg(
          record->properties()->name(), update.join( ", " ), filter );
    QSqlQuery *qry = new QSqlQuery( sqlText, m_DB );
    if ( qry->lastError().isValid() )
    {
      QSqlError err = qry->lastError();
      rollback();
      delete qry;
      qry = NULL;
      return err;
    }
  }

  return QSqlError();
}

bool PropertiesSqlWorker::isInTransaction()
{
  return m_InTransaction;
}

PropertiesSqlWorker::PropertiesSqlWorker()
{
  m_Alias = new QString();
  m_PgDB = 0;
  m_InTransaction = false;
  recordsInTransaction = QList<QPair<MFCRecord *, bool> >();
}

PropertiesSqlWorker::PropertiesSqlWorker( QString alias, QSqlDatabase &db )
{
  m_Alias = new QString( alias );
  m_DB = db;
  m_PgDB = new PgDB( m_DB );
  m_InTransaction = false;
  recordsInTransaction = QList<QPair<MFCRecord *, bool> >();
}

PropertiesSqlWorker::~PropertiesSqlWorker()
{
//  qDebug() <<QObject::tr( "~PropertiesSqlWorker [%1]" ).arg( (*m_Alias) );
  delete m_Alias;
  m_Alias = NULL;
  if ( m_PgDB != 0 )
  {
    delete m_PgDB;
    m_PgDB = NULL;
  }
}
