#include "muserdbwrapper.h"

#include "makcdataset.h"

#include <QReadWriteLock>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTime>

#include "amslogger.h"


/*
 * Begin C++ - QML class definition: *[ MUser ]*
*/
MUser::MUser( QQuickItem *parent ) :
  QQuickItem(parent),
  m__ExternalLinksCount(0)
{
}

MUser::~MUser()
{
//  qDebug() << __func__ << this;
}

QVariant MUser::identifier() const
{
  return m__Identifier;
}

void MUser::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;
  emit identifierChanged();
}

const QVariant & MUser::surname() const
{
  return m__Surname;
}

void MUser::setSurname( const QVariant &surname )
{
  m__Surname = surname;
  emit surnameChanged();
}

const QVariant & MUser::firstname() const
{
  return m__Firstname;
}

void MUser::setFirstname( const QVariant &firstname )
{
  m__Firstname = firstname;
  emit firstnameChanged();
}

const QVariant & MUser::lastname() const
{
  return m__Lastname;
}

void MUser::setLastname( const QVariant &lastname )
{
  m__Lastname = lastname;
  emit lastnameChanged();
}

const QVariant & MUser::login() const
{
  return m__Login;
}

void MUser::setLogin( const QVariant &login )
{
  m__Login = login;
  emit loginChanged();
}

int MUser::externalLinksCount() const
{
  return m__ExternalLinksCount;
}

int MUser::incrementExternalLinks()
{
  return m__ExternalLinksCount++;
}

int MUser::decrementExternalLinks()
{
  if ( m__ExternalLinksCount > 0 ) m__ExternalLinksCount--;

  return m__ExternalLinksCount;
}
/*
 * End class definition: *[ MUser ]*
*/


/*
 * Begin C++ class definition: *[ MUserDBWrapper ]*
*/
MUserDBWrapper::MUserDBWrapper( MAbstractDataSource *parent ) :
  MAbstractDBWrapper(parent)
{
}

MUserDBWrapper::~MUserDBWrapper()
{
  m__ExistUsers.clear();
}

MUser * MUserDBWrapper::user( QVariant identifier )
{
  MUser *result = NULL;
  if ( !identifier.isValid() || identifier.toInt() == 0 ) return result;

  locker()->lockForRead();
  result = m__ExistUsers.value( identifier.toInt(), NULL );
  locker()->unlock();

  if ( result == NULL )
  {
    QString currentQuery = tr( "SELECT * FROM users WHERE id=%1" ).arg( identifier.toInt() );

    QSqlQuery *qry = MDatabase::instance()->getQuery( currentQuery, pConnectionName() );
    if ( qry->lastError().isValid() )
    {
      LogDebug() << qry->lastError().text();
      locker()->unlock();
      return result;
    }
    int identifier = qry->record().value( "id" ).toInt();
    locker()->lockForWrite();
    result = new MUser;
    result->moveToThread( parent()->thread() );
    m__ExistUsers[identifier] = result;
    result->setIdentifier( identifier );
    result->setSurname( qry->record().value( "surname" ) );
    result->setFirstname( qry->record().value( "aname" ) );
    result->setLastname( qry->record().value( "lastname" ) );
    result->setLogin( qry->record().value( "dblogin" ) );
    locker()->unlock();
    qry->clear();
    delete qry;
    qry = NULL;
  }

  return result;
}

QList<MUser *> MUserDBWrapper::users( QVariantList identifiers )
{
  QList<MUser *> result;

  locker()->lockForWrite();
  QString ids;
  foreach ( QVariant identifier, identifiers )
  {
    if ( !identifier.isValid() || identifier.toInt() == 0 ) continue;
    MUser *user = m__ExistUsers.value( identifier.toInt(), NULL );

    if ( user == NULL )
      ids += ( !ids.isEmpty() ? ", " : "" )+identifier.toString();
    else result << user;
  }

  if ( !ids.isEmpty() )
  {
    QString currentQuery = tr( "SELECT * FROM users WHERE id in (%1)" ).arg( ids );

    QSqlQuery *qry = MDatabase::instance()->getQuery( currentQuery, pConnectionName() );
    if ( qry->lastError().isValid() )
    {
      LogDebug() << qry->lastError().text();
      locker()->unlock();
      return result;
    }
    while ( qry->next() )
    {
      int identifier = qry->record().value( "id" ).toInt();
      MUser *user = new MUser;
      user->moveToThread( parent()->thread() );
      m__ExistUsers[identifier] = user;
      user->setIdentifier( identifier );
      user->setSurname( qry->record().value( "surname" ) );
      user->setFirstname( qry->record().value( "aname" ) );
      user->setLastname( qry->record().value( "lastname" ) );
      user->setLogin( qry->record().value( "dblogin" ) );
      result << user;
    }
    qry->clear();
    delete qry;
    qry = NULL;
  }
  locker()->unlock();

  return result;
}

bool MUserDBWrapper::searching( const QString &queryText )
{
  QString currentQuery = queryText;
  if ( currentQuery.isEmpty() ) currentQuery = tr( "SELECT * FROM users ORDER BY id" );
  else currentQuery = tr( "SELECT * FROM users WHERE %1 ORDER BY id" ).arg( currentQuery );
  QString maxIdQuery = queryText;
  if ( maxIdQuery.isEmpty() ) maxIdQuery = tr( "SELECT max(id) FROM users" );
  else maxIdQuery = tr( "SELECT max(id) FROM users WHERE %1" ).arg( maxIdQuery );

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
      MUser *oldUser = qobject_cast<MUser *>( pTake( (int)Founded, 0 ) );

      if ( oldUser->externalLinksCount() == 0 && pIndex( (int)Initiated, oldUser ) == -1 )
      {
        m__ExistUsers.remove( oldUser->identifier().toInt() );
        connect( this, SIGNAL(aboutToReleaseOldResources()), oldUser, SLOT(deleteLater()) );
      }
    }
  }
  else
  {
    int lastFounded = -1;
    int counted = 0;
    while ( qry->next() )
    {
      counted++;
      int identifier = qry->record().value( "id" ).toInt();
      MUser *user = m__ExistUsers.value( identifier, NULL );

      int usersCount = pCount( (int)Founded );
      int index = lastFounded+1;
      bool insertIntoFounded = true;
      for ( ; index < usersCount; index++ )
      {
        MUser *oldUser = qobject_cast<MUser *>( pObject( (int)Founded, index ) );

        if ( identifier > oldUser->identifier().toInt() || maxId < oldUser->identifier().toInt() )
        {
          //        LogDebug() << "\tудалить объект с ID" << identifier;
          pTake( (int)Founded, index );
          index--;
          usersCount--;

          if ( oldUser->externalLinksCount() == 0 && pIndex( (int)Initiated, oldUser ) == -1 )
          {
            m__ExistUsers.remove( oldUser->identifier().toInt() );
            connect( this, SIGNAL(aboutToReleaseOldResources()), oldUser, SLOT(deleteLater()) );
          }
        }
        else if ( identifier == oldUser->identifier().toInt() )
        {
          //        LogDebug() << "\tзапомнить объект с ID" << identifier;
          insertIntoFounded = false;
          lastFounded = index;
          break;
        }
      }

      if ( user == NULL )
      {
        //      LogDebug() << "\tобъект с ID" << identifier;
        user = new MUser;
        user->moveToThread( parent()->thread() );
        m__ExistUsers[identifier] = user;
        user->setIdentifier( identifier );
      }
      if ( insertIntoFounded )
      {
        lastFounded++;
        pInsert( (int)Founded, user, lastFounded );
      }
      user->setSurname( qry->record().value( "surname" ) );
      user->setFirstname( qry->record().value( "aname" ) );
      user->setLastname( qry->record().value( "lastname" ) );
      user->setLogin( qry->record().value( "dblogin" ) );
    }
    int usersCount = pCount( (int)Founded );
    for ( int index = lastFounded+1; index < usersCount; index++ )
    {
      MUser *oldUser = qobject_cast<MUser *>( pObject( (int)Founded, index ) );

      pTake( (int)Founded, index );
      index--;
      usersCount--;

      if ( oldUser->externalLinksCount() == 0 && pIndex( (int)Initiated, oldUser ) == -1 )
      {
        m__ExistUsers.remove( oldUser->identifier().toInt() );
        connect( this, SIGNAL(aboutToReleaseOldResources()), oldUser, SLOT(deleteLater()) );
      }
    }
  }
  locker()->unlock();
  qry->clear();
  delete qry;
  qry = NULL;

  return true;
}

bool MUserDBWrapper::initiating()
{
  return true;
}

bool MUserDBWrapper::saving( QObject *object )
{
  Q_UNUSED( object )
  return true;
}
/*
 * End class definition: *[ MUserDBWrapper ]*
*/
