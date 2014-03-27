#include "mdoctypedbwrapper.h"

#include <QReadWriteLock>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTime>


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

    QSqlDatabase database = QSqlDatabase::database( connectionName(), false );
    if ( !database.open() )
    {
      qDebug() << __func__ << __LINE__ << database.lastError().text();
      return result;
    }

    QSqlQuery qry( currentQuery, database );
    if ( qry.lastError().isValid() || !qry.next() )
    {
      qDebug() << __func__ << __LINE__ << qry.lastError().text();
      return result;
    }
    int identifier = qry.record().value( "id" ).toInt();
    result = new MDoctype;
    result->moveToThread( parent()->thread() );
    m__ExistDoctypes[identifier] = result;
    result->setIdentifier( identifier );
    result->setName( qry.record().value( "aname" ).toString() );
    locker()->unlock();
    qry.clear();
  }

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

  QSqlDatabase database = QSqlDatabase::database( connectionName(), false );
  if ( !database.open() )
  {
    qDebug() << __func__ << __LINE__ << database.lastError().text();
    return false;
  }

  QSqlQuery qry( maxIdQuery, database );
  if ( qry.lastError().isValid() || !qry.next() )
  {
    qDebug() << __func__ << __LINE__ << qry.lastError().text();
    return false;
  }
  int maxId = qry.record().value( 0 ).toInt();
  qry.clear();

  if ( !qry.exec( currentQuery ) || qry.lastError().isValid() )
  {
    qDebug() << __func__ << __LINE__ << qry.lastError().text();
    return false;
  }

  locker()->lockForWrite();
  int lastFounded = -1;
  while ( qry.next() )
  {
    int identifier = qry.record().value( "id" ).toInt();
    MDoctype *doctype = m__ExistDoctypes.value( identifier, NULL );

    int doctypesCount = pCount( (int)Founded );
    int index = lastFounded+1;
    bool insertIntoFounded = true;
    for ( ; index < doctypesCount; index++ )
    {
      MDoctype *oldDoctype = qobject_cast<MDoctype *>( pObject( (int)Founded, index ) );

      if ( identifier > oldDoctype->identifier().toInt() || maxId < oldDoctype->identifier().toInt() )
      {
//        qDebug() << metaObject()->className() << __func__ << __LINE__ << "\tудалить объект с ID" << identifier;
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
//        qDebug() << metaObject()->className() << __func__ << __LINE__ << "\tзапомнить объект с ID" << identifier;
        insertIntoFounded = false;
        lastFounded = index;
        break;
      }
    }

    if ( doctype == NULL )
    {
//      qDebug() << metaObject()->className() << __func__ << __LINE__ << "\tобъект с ID" << identifier;
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
    doctype->setName( qry.record().value( "aname" ).toString() );
  }
  qry.clear();
//  qDebug() << metaObject()->className() << __func__ << __LINE__ << pCount( human->documents() ) << counted;
  locker()->unlock();

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
