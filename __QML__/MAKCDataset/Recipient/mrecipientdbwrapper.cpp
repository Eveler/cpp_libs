#include "mrecipientdbwrapper.h"

#include "mdatabase.h"

#include <QReadWriteLock>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTime>

#include "amslogger.h"


/*
 * Begin C++ - QML class definition: *[ MRecipient ]*
*/
MRecipient::MRecipient( QQuickItem *parent ) :
  QQuickItem(parent),
  m__ExternalLinksCount(0)
{}

MRecipient::~MRecipient() {}

QVariant MRecipient::identifier() const
{
  return m__Identifier;
}

void MRecipient::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;

  emit identifierChanged();
}

const QString & MRecipient::name() const
{
  return m__Name;
}

void MRecipient::setName( const QString & name )
{
  m__Name = name;

  emit nameChanged();
}

int MRecipient::externalLinksCount() const
{
  return m__ExternalLinksCount;
}

int MRecipient::incrementExternalLinks()
{
  return m__ExternalLinksCount++;
}

int MRecipient::decrementExternalLinks()
{
  if ( m__ExternalLinksCount > 0 ) m__ExternalLinksCount--;

  return m__ExternalLinksCount;
}
/*
 * End class definition: *[ MRecipient ]*
*/


/*
 * Begin C++ class definition: *[ MRecipientDBWrapper ]*
*/
MRecipientDBWrapper::MRecipientDBWrapper( MAbstractDataSource *parent ) :
  MAbstractDBWrapper(parent)
{
}

MRecipientDBWrapper::~MRecipientDBWrapper()
{
  m__ExistRecipients.clear();
}

MRecipient * MRecipientDBWrapper::recipient( QVariant identifier )
{
  MRecipient *result = NULL;

  locker()->lockForRead();
  result = m__ExistRecipients.value( identifier.toInt(), result );
  locker()->unlock();

  if ( result == NULL )
  {
    QString currentQuery = tr( "SELECT * FROM recipients WHERE recipient_id=%1" ).arg( identifier.toInt() );

    QSqlQuery *qry = MDatabase::instance()->getQuery( currentQuery, connectionName() );
    if ( qry->lastError().isValid() || !qry->next() )
    {
      LogDebug() << qry->lastError().text();
      locker()->unlock();
      return result;
    }
    int identifier = qry->record().value( "recipient_id" ).toInt();
    locker()->lockForWrite();
    result = new MRecipient;
    result->moveToThread( parent()->thread() );
    m__ExistRecipients[identifier] = result;
    result->setIdentifier( identifier );
    result->setName( qry->record().value( "recipient_name" ).toString() );
    locker()->unlock();
    qry->clear();
    delete qry;
    qry = NULL;
  }

  return result;
}

QList<MRecipient *> MRecipientDBWrapper::recipients( QVariantList identifiers )
{
  QList<MRecipient *> result;

  locker()->lockForWrite();
  QString ids;
  foreach ( QVariant identifier, identifiers )
  {
    if ( !identifier.isValid() || identifier.toInt() == 0 ) continue;
    MRecipient *recipient = m__ExistRecipients.value( identifier.toInt(), NULL );

    if ( recipient == NULL )
      ids += ( !ids.isEmpty() ? ", " : "" )+identifier.toString();
    else result << recipient;
  }

  if ( !ids.isEmpty() )
  {
    QString currentQuery = tr( "SELECT * FROM recipients WHERE recipient_id in (%1)" ).arg( ids );

    QSqlQuery *qry = MDatabase::instance()->getQuery( currentQuery, connectionName() );
    if ( qry->lastError().isValid() )
    {
      LogDebug() << qry->lastError().text();
      locker()->unlock();
      return result;
    }
    while ( qry->next() )
    {
      int identifier = qry->record().value( "recipient_id" ).toInt();
      MRecipient *recipient = new MRecipient;
      recipient->moveToThread( parent()->thread() );
      m__ExistRecipients[identifier] = recipient;
      recipient->setIdentifier( identifier );
      recipient->setName( qry->record().value( "recipient_name" ).toString() );
      result << recipient;
    }
    qry->clear();
    delete qry;
    qry = NULL;
  }
  locker()->unlock();

  return result;
}

bool MRecipientDBWrapper::searching( const QString &queryText )
{
  QString currentQuery = queryText;
  if ( currentQuery.isEmpty() ) currentQuery = tr( "SELECT * FROM recipients ORDER BY recipient_id" );
  else currentQuery = tr( "SELECT * FROM recipients WHERE %1 ORDER BY recipient_id" ).arg( currentQuery );
  QString maxIdQuery = queryText;
  if ( maxIdQuery.isEmpty() ) maxIdQuery = tr( "SELECT max(recipient_id) FROM recipients" );
  else maxIdQuery = tr( "SELECT max(recipient_id) FROM recipients WHERE %1" ).arg( maxIdQuery );

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
      MRecipient *oldRecipient = qobject_cast<MRecipient *>( pTake( (int)Founded, 0 ) );

      if ( oldRecipient->externalLinksCount() == 0 && pIndex( (int)Initiated, oldRecipient ) == -1 )
      {
        m__ExistRecipients.remove( oldRecipient->identifier().toInt() );
        connect( this, SIGNAL(aboutToReleaseOldResources()), oldRecipient, SLOT(deleteLater()) );
      }
    }
  }
  else
  {
    int lastFounded = -1;
    while ( qry->next() )
    {
      int identifier = qry->record().value( "recipient_id" ).toInt();
      MRecipient *recipient = m__ExistRecipients.value( identifier, NULL );

      int recipientsCount = pCount( (int)Founded );
      int index = lastFounded+1;
      bool insertIntoFounded = true;
      for ( ; index < recipientsCount; index++ )
      {
        MRecipient *oldRecipient = qobject_cast<MRecipient *>( pObject( (int)Founded, index ) );

        if ( identifier > oldRecipient->identifier().toInt() || maxId < oldRecipient->identifier().toInt() )
        {
          //        LogDebug() << "\tудалить объект с ID" << identifier;
          pTake( (int)Founded, index );
          index--;
          recipientsCount--;

          if ( oldRecipient->externalLinksCount() == 0 && pIndex( (int)Initiated, oldRecipient ) == -1 )
          {
            m__ExistRecipients.remove( oldRecipient->identifier().toInt() );
            connect( this, SIGNAL(aboutToReleaseOldResources()), oldRecipient, SLOT(deleteLater()) );
          }
        }
        else if ( identifier == oldRecipient->identifier().toInt() )
        {
          //        LogDebug() << "\tзапомнить объект с ID" << identifier;
          insertIntoFounded = false;
          lastFounded = index;
          break;
        }
      }

      if ( recipient == NULL )
      {
        //      LogDebug() << "\tобъект с ID" << identifier;
        recipient = new MRecipient;
        recipient->moveToThread( parent()->thread() );
        m__ExistRecipients[identifier] = recipient;
        recipient->setIdentifier( identifier );
      }
      if ( insertIntoFounded )
      {
        lastFounded++;
        pInsert( (int)Founded, recipient, lastFounded );
      }
      recipient->setName( qry->record().value( "recipient_name" ).toString() );
    }
    //  LogDebug() << pCount( human->documents() ) << counted;
  }
  locker()->unlock();
  qry->clear();
  delete qry;
  qry = NULL;

  return true;
}

bool MRecipientDBWrapper::initiating()
{
  return true;
}

bool MRecipientDBWrapper::saving( QObject *object )
{
  Q_UNUSED(object)
  return true;
}
/*
 * End class definition: *[ MRecipientDBWrapper ]*
*/
