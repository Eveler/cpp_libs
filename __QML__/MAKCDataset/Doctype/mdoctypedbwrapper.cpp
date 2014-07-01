#include "mdoctypedbwrapper.h"

#include "mdatabase.h"

#include <QReadWriteLock>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTime>

#include "amslogger.h"


/*
 * Begin C++ - QML class definition: *[ MDoctype ]*
*/
MDoctype::MDoctype( QQuickItem *parent ) :
  QQuickItem(parent),
  m__ExternalLinksCount(0)
{}

MDoctype::~MDoctype() {}

QVariant MDoctype::identifier() const
{
  return m__Identifier;
}

void MDoctype::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;

  emit identifierChanged();
}

const QString & MDoctype::name() const
{
  return m__Name;
}

void MDoctype::setName( const QString & name )
{
  m__Name = name;

  emit nameChanged();
}

int MDoctype::externalLinksCount() const
{
  return m__ExternalLinksCount;
}

int MDoctype::incrementExternalLinks()
{
  return m__ExternalLinksCount++;
}

int MDoctype::decrementExternalLinks()
{
  if ( m__ExternalLinksCount > 0 ) m__ExternalLinksCount--;

  return m__ExternalLinksCount;
}
/*
 * End class definition: *[ MDoctype ]*
*/


/*
 * Begin C++ - class definition: *[ MDoctypeDBWrapper ]*
*/
MDoctypeDBWrapper::MDoctypeDBWrapper( MAbstractDataSource *parent ) :
  MAbstractDBWrapper(parent)
{
}

MDoctypeDBWrapper::~MDoctypeDBWrapper()
{
  m__ExistDoctypes.clear();
}

MDoctype * MDoctypeDBWrapper::doctype( QVariant identifier )
{
  MDoctype *result = NULL;

  locker()->lockForRead();
  result = m__ExistDoctypes.value( identifier.toInt(), result );
  locker()->unlock();

  if ( result == NULL )
  {
    QString currentQuery = tr( "SELECT * FROM doctypes WHERE id=%1" ).arg( identifier.toInt() );

    QSqlQuery *qry = MDatabase::instance()->getQuery( currentQuery, connectionName() );
    if ( qry->lastError().isValid() || !qry->next() )
    {
      LogDebug() << qry->lastError().text();
      locker()->unlock();
      return result;
    }
    int identifier = qry->record().value( "id" ).toInt();
    locker()->lockForWrite();
    result = new MDoctype;
    result->moveToThread( parent()->thread() );
    m__ExistDoctypes[identifier] = result;
    result->setIdentifier( identifier );
    result->setName( qry->record().value( "aname" ).toString() );
    locker()->unlock();
    qry->clear();
    delete qry;
    qry = NULL;
  }

  return result;
}

QList<MDoctype *> MDoctypeDBWrapper::doctypes( QVariantList identifiers )
{
  QList<MDoctype *> result;

  locker()->lockForWrite();
  QString ids;
  foreach ( QVariant identifier, identifiers )
  {
    if ( !identifier.isValid() || identifier.toInt() == 0 ) continue;
    MDoctype *doctype = m__ExistDoctypes.value( identifier.toInt(), NULL );

    if ( doctype == NULL )
      ids += ( !ids.isEmpty() ? ", " : "" )+identifier.toString();
    else result << doctype;
  }

  if ( !ids.isEmpty() )
  {
    QString currentQuery = tr( "SELECT * FROM doctypes WHERE id in (%1)" ).arg( ids );

    QSqlQuery *qry = MDatabase::instance()->getQuery( currentQuery, connectionName() );
    if ( qry->lastError().isValid() )
    {
      LogDebug() << qry->lastError().text();
      locker()->unlock();
      return result;
    }
    while ( qry->next() )
    {
      int identifier = qry->record().value( "id" ).toInt();
      MDoctype *doctype = new MDoctype;
      doctype->moveToThread( parent()->thread() );
      m__ExistDoctypes[identifier] = doctype;
      doctype->setIdentifier( identifier );
      doctype->setName( qry->record().value( "aname" ).toString() );
      result << doctype;
    }
    qry->clear();
    delete qry;
    qry = NULL;
  }
  locker()->unlock();

  return result;
}

bool MDoctypeDBWrapper::searching( const QString &queryText )
{
  QString currentQuery = queryText;
  if ( currentQuery.isEmpty() ) currentQuery = tr( "SELECT * FROM doctypes ORDER BY id" );
  else currentQuery = tr( "SELECT * FROM doctypes WHERE %1 ORDER BY id" ).arg( currentQuery );
  QString maxIdQuery = queryText;
  if ( maxIdQuery.isEmpty() ) maxIdQuery = tr( "SELECT max(id) FROM doctypes" );
  else maxIdQuery = tr( "SELECT max(id) FROM doctypes WHERE %1" ).arg( maxIdQuery );

  QSqlQuery *qry = MDatabase::instance()->getQuery( maxIdQuery, connectionName() );
  if ( qry->lastError().isValid() || !qry->next() )
  {
    LogDebug() << qry->lastError().text();
    return false;
  }
  int maxId = qry->record().value( 0 ).toInt();
  qry->clear();
  delete qry;
  qry = NULL;

  qry = MDatabase::instance()->getQuery( currentQuery, connectionName() );
  if ( qry->lastError().isValid() )
  {
    LogDebug() << qry->lastError().text();
    return false;
  }

  locker()->lockForWrite();
  if ( maxId == 0 )
  {
    while ( pCount( (int)Founded ) > 0 )
    {
      MDoctype *oldDoctype = qobject_cast<MDoctype *>( pTake( (int)Founded, 0 ) );

      if ( oldDoctype->externalLinksCount() == 0 && pIndex( (int)Initiated, oldDoctype ) == -1 )
      {
        m__ExistDoctypes.remove( oldDoctype->identifier().toInt() );
        connect( this, SIGNAL(aboutToReleaseOldResources()), oldDoctype, SLOT(deleteLater()) );
      }
    }
  }
  else
  {
    int lastFounded = -1;
    while ( qry->next() )
    {
      int identifier = qry->record().value( "id" ).toInt();
      MDoctype *doctype = m__ExistDoctypes.value( identifier, NULL );

      int doctypesCount = pCount( (int)Founded );
      int index = lastFounded+1;
      bool insertIntoFounded = true;
      for ( ; index < doctypesCount; index++ )
      {
        MDoctype *oldDoctype = qobject_cast<MDoctype *>( pObject( (int)Founded, index ) );

        if ( identifier > oldDoctype->identifier().toInt() || maxId < oldDoctype->identifier().toInt() )
        {
          //        LogDebug() << "\tудалить объект с ID" << identifier;
          pTake( (int)Founded, index );
          index--;
          doctypesCount--;

          if ( oldDoctype->externalLinksCount() == 0 && pIndex( (int)Initiated, oldDoctype ) == -1 )
          {
            m__ExistDoctypes.remove( oldDoctype->identifier().toInt() );
            connect( this, SIGNAL(aboutToReleaseOldResources()), oldDoctype, SLOT(deleteLater()) );
          }
        }
        else if ( identifier == oldDoctype->identifier().toInt() )
        {
          //        LogDebug() << "\tзапомнить объект с ID" << identifier;
          insertIntoFounded = false;
          lastFounded = index;
          break;
        }
      }

      if ( doctype == NULL )
      {
        //      LogDebug() << "\tобъект с ID" << identifier;
        doctype = new MDoctype;
        doctype->moveToThread( parent()->thread() );
        m__ExistDoctypes[identifier] = doctype;
        doctype->setIdentifier( identifier );
      }
      if ( insertIntoFounded )
      {
        lastFounded++;
        pInsert( (int)Founded, doctype, lastFounded );
      }
      doctype->setName( qry->record().value( "aname" ).toString() );
    }
    //  LogDebug() << pCount( human->documents() ) << counted;
  }
  locker()->unlock();
  qry->clear();
  delete qry;
  qry = NULL;

  return true;
}

bool MDoctypeDBWrapper::initiating()
{
  return true;
}

bool MDoctypeDBWrapper::saving( QObject *object )
{
  Q_UNUSED(object)
  return true;
}
/*
 * End class definition: *[ MDoctypeDBWrapper ]*
*/
