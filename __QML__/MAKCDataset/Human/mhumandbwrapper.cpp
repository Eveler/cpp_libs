#include "mhumandbwrapper.h"

#include "makcdataset.h"

#include <QReadWriteLock>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTime>


/*
 * Begin C++ - QML class definition: *[ MHuman ]*
*/
MHuman::MHuman( QQuickItem *parent ) :
  QQuickItem(parent),
  m__Documents(new MDataSourceModel( this ))
{
}

MHuman::~MHuman()
{
//  qDebug() << __func__ << this;
  delete m__Documents;
  m__Documents = NULL;
}

QVariant MHuman::identifier() const
{
  return m__Identifier;
}

void MHuman::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;
  emit identifierChanged();
}

const QVariant & MHuman::surname() const
{
  return m__Surname;
}

void MHuman::setSurname( const QVariant &surname )
{
  m__Surname = surname;
  emit surnameChanged();
}

const QVariant & MHuman::firstname() const
{
  return m__Firstname;
}

void MHuman::setFirstname( const QVariant &firstname )
{
  m__Firstname = firstname;
  emit firstnameChanged();
}

const QVariant & MHuman::lastname() const
{
  return m__Lastname;
}

void MHuman::setLastname( const QVariant &lastname )
{
  m__Lastname = lastname;
  emit lastnameChanged();
}

const QVariant & MHuman::phone() const
{
  return m__Phone;
}

void MHuman::setPhone( const QVariant &phone )
{
  m__Phone = phone;
  emit phoneChanged();
}

const QVariant & MHuman::address() const
{
  return m__Address;
}

void MHuman::setAddress( const QVariant &address )
{
  m__Address = address;
  emit addressChanged();
}

const QVariant & MHuman::email() const
{
  return m__Email;
}

void MHuman::setEmail( const QVariant &email )
{
  m__Email = email;
  emit emailChanged();
}

const QVariant & MHuman::birthday() const
{
  return m__Birthday;
}

void MHuman::setBirthday( const QVariant &birthday )
{
  m__Birthday = birthday;
  emit birthdayChanged();
}

MDataSourceModel * MHuman::documents() const
{
  return m__Documents;
}

int MHuman::externalLinksCount() const
{
  return m__ExternalLinksCount;
}

int MHuman::incrementExternalLinks()
{
  return m__ExternalLinksCount++;
}

int MHuman::decrementExternalLinks()
{
  if ( m__ExternalLinksCount > 0 ) m__ExternalLinksCount--;

  return m__ExternalLinksCount;
}
/*
 * End class definition: *[ MHuman ]*
*/


/*
 * Begin C++ class definition: *[ MHumanDBWrapper ]*
*/
MHumanDBWrapper::MHumanDBWrapper( MAbstractDataSource * parent ) :
  MAbstractDBWrapper( parent )
{
}

MHumanDBWrapper::~MHumanDBWrapper()
{
  m__ExistHumans.clear();
}

MHuman * MHumanDBWrapper::human( QVariant identifier )
{
  MHuman *result = NULL;
  if ( !identifier.isValid() || identifier.toInt() == 0 ) return result;

  locker()->lockForRead();
  result = m__ExistHumans.value( identifier.toInt(), NULL );
  locker()->unlock();

  if ( result == NULL )
  {
    QString currentQuery = tr( "SELECT * FROM humans WHERE id=%1" ).arg( identifier.toInt() );

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
    result = new MHuman;
    result->moveToThread( parent()->thread() );
    locker()->lockForWrite();
    m__ExistHumans[identifier] = result;
    result->setIdentifier( identifier );
    result->setSurname( qry.record().value( "surname" ) );
    result->setFirstname( qry.record().value( "firstname" ) );
    result->setLastname( qry.record().value( "lastname" ) );
    result->setPhone( qry.record().value( "phone" ) );
    result->setAddress( qry.record().value( "addr" ) );
    result->setEmail( qry.record().value( "e-mail" ) );
    result->setBirthday( qry.record().value( "birthday" ) );
    locker()->unlock();
    qry.clear();
  }

  return result;
}

QList<MHuman *> MHumanDBWrapper::humans( QVariantList identifiers )
{
  QList<MHuman *> result;

  locker()->lockForWrite();
  QString ids;
  foreach ( QVariant identifier, identifiers )
  {
    if ( !identifier.isValid() || identifier.toInt() == 0 ) continue;
    MHuman *human = m__ExistHumans.value( identifier.toInt(), NULL );

    if ( human == NULL )
      ids += ( !ids.isEmpty() ? ", " : "" )+identifier.toString();
    else result << human;
  }

  if ( !ids.isEmpty() )
  {
    QString currentQuery = tr( "SELECT * FROM humans WHERE id in (%1)" ).arg( ids );
    QSqlDatabase database = QSqlDatabase::database( pConnectionName(), false );
    if ( !database.open() )
    {
      qDebug() << __func__ << __LINE__ << database.lastError().text();
      locker()->unlock();
      return result;
    }

    QSqlQuery qry( currentQuery, database );
    if ( qry.lastError().isValid() )
    {
      qDebug() << __func__ << __LINE__ << qry.lastError().text();
      locker()->unlock();
      return result;
    }
    while ( qry.next() )
    {
      int identifier = qry.record().value( "id" ).toInt();
      MHuman *human = new MHuman;
      human->moveToThread( parent()->thread() );
      m__ExistHumans[identifier] = human;
      human->setIdentifier( identifier );
      human->setSurname( qry.record().value( "surname" ) );
      human->setFirstname( qry.record().value( "firstname" ) );
      human->setLastname( qry.record().value( "lastname" ) );
      human->setPhone( qry.record().value( "phone" ) );
      human->setAddress( qry.record().value( "addr" ) );
      human->setEmail( qry.record().value( "e-mail" ) );
      human->setBirthday( qry.record().value( "birthday" ) );
      result << human;
    }
    qry.clear();
  }
  locker()->unlock();

  return result;
}

bool MHumanDBWrapper::searching( const QString &queryText )
{
  MDocumentDBWrapper *documentDBWrapper = qobject_cast<MDocumentDBWrapper *>( MAKCDataset::MAKC_DocumentDataSource()->dbWrapper() );

  QString currentQuery = queryText;
  if ( currentQuery.isEmpty() ) currentQuery = tr( "SELECT * FROM humans ORDER BY id" );
  else currentQuery = tr( "SELECT * FROM humans WHERE %1 ORDER BY id" ).arg( currentQuery );
  QString maxIdQuery = queryText;
  if ( maxIdQuery.isEmpty() ) maxIdQuery = tr( "SELECT max(id) FROM humans" );
  else maxIdQuery = tr( "SELECT max(id) FROM humans WHERE %1" ).arg( maxIdQuery );

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

  if ( maxId == 0 )
  {
    while ( pCount( (int)Founded ) > 0 )
    {
      MHuman *oldHuman = qobject_cast<MHuman *>( pTake( (int)Founded, 0 ) );

      if ( oldHuman->externalLinksCount() == 0 && pIndex( (int)Initiated, oldHuman ) == -1 )
      {
        documentDBWrapper->releaseHumanDocuments( oldHuman );
        m__ExistHumans.remove( oldHuman->identifier().toInt() );
        connect( this, SIGNAL(aboutToReleaseOldResources()), oldHuman, SLOT(deleteLater()) );
      }
    }
  }
  else
  {
    int lastFounded = -1;
    while ( qry.next() )
    {
      int identifier = qry.record().value( "id" ).toInt();
      MHuman *human = m__ExistHumans.value( identifier, NULL );

      int humansCount = pCount( (int)Founded );
      int index = lastFounded+1;
      bool insertIntoFounded = true;
      for ( ; index < humansCount; index++ )
      {
        MHuman *oldHuman = qobject_cast<MHuman *>( pObject( (int)Founded, index ) );

        if ( identifier > oldHuman->identifier().toInt() || maxId < oldHuman->identifier().toInt() )
        {
          //        qDebug() << metaObject()->className() << __func__ << __LINE__ << "\tудалить объект с ID" << identifier;
          pTake( (int)Founded, index );
          index--;
          humansCount--;

          if ( oldHuman->externalLinksCount() == 0 && pIndex( (int)Initiated, oldHuman ) == -1 )
          {
            documentDBWrapper->releaseHumanDocuments( oldHuman );
            m__ExistHumans.remove( oldHuman->identifier().toInt() );
            connect( this, SIGNAL(aboutToReleaseOldResources()), oldHuman, SLOT(deleteLater()) );
          }
        }
        else if ( identifier == oldHuman->identifier().toInt() )
        {
          //        qDebug() << metaObject()->className() << __func__ << __LINE__ << "\tзапомнить объект с ID" << identifier;
          insertIntoFounded = false;
          lastFounded = index;
          break;
        }
      }

      if ( human == NULL )
      {
        //      qDebug() << metaObject()->className() << __func__ << __LINE__ << "\tобъект с ID" << identifier;
        human = new MHuman;
        human->moveToThread( parent()->thread() );
        m__ExistHumans[identifier] = human;
        human->setIdentifier( identifier );
      }
      if ( insertIntoFounded )
      {
        lastFounded++;
        pInsert( (int)Founded, human, lastFounded );
      }
      human->setSurname( qry.record().value( "surname" ) );
      human->setFirstname( qry.record().value( "firstname" ) );
      human->setLastname( qry.record().value( "lastname" ) );
      human->setPhone( qry.record().value( "phone" ) );
      human->setAddress( qry.record().value( "addr" ) );
      human->setEmail( qry.record().value( "e-mail" ) );
      human->setBirthday( qry.record().value( "birthday" ) );
    }
  }
  locker()->unlock();
  qry.clear();

  return true;
}

bool MHumanDBWrapper::initiating()
{
  QSqlDatabase database = QSqlDatabase::database( connectionName(), false );
  if ( !database.open() )
  {
    qDebug() << __func__ << __LINE__ << database.lastError().text();
    return false;
  }

  QString currentQuery = tr( "SELECT nextval('humans_id_seq')" );
  QSqlQuery qry( currentQuery, database );
  if ( qry.lastError().isValid() || !qry.next() )
  {
    qDebug() << __func__ << __LINE__ << qry.lastError().text();
    return false;
  }
  locker()->lockForWrite();

  MHuman *human = new MHuman;
  human->setIdentifier( qry.record().value( 0 ) );
  pInsert( (int)Initiated, human );
  human->moveToThread( parent()->thread() );
  qry.clear();

  locker()->unlock();

  return true;
}

bool MHumanDBWrapper::saving( QObject *object )
{
  QSqlDatabase database = QSqlDatabase::database( connectionName(), false );
  if ( !database.open() )
  {
    qDebug() << __func__ << __LINE__ << database.lastError().text();

    return false;
  }

  locker()->lockForWrite();

  MHuman *human = qobject_cast<MHuman *>( object );
  if ( human == NULL )
  {
    qDebug() << __func__ << __LINE__ << "Human object is NULL";
    locker()->unlock();

    return false;
  }

  QString identifier = human->identifier().toString();
  QString surname = ( human->surname().isNull() ? "NULL" : "'"+human->surname().toString().replace( "'", "''" )+"'" );
  QString firstname = ( human->firstname().isNull() ? "NULL" : "'"+human->firstname().toString().replace( "'", "''" )+"'" );
  QString lastname = ( human->lastname().isNull() ? "NULL" : "'"+human->lastname().toString().replace( "'", "''" )+"'" );
  QString address = ( human->address().isNull() ? "NULL" : "'"+human->address().toString().replace( "'", "''" )+"'" );
  QString phone = ( human->phone().isNull() ? "NULL" : "'"+human->phone().toString().replace( "'", "''" )+"'" );
  QString email = ( human->email().isNull() ? "NULL" : "'"+human->email().toString().replace( "'", "''" )+"'" );
  QString birthday = ( human->birthday().isNull() ? "NULL" : "'"+human->birthday().toDate().toString( "dd.MM.yyyy" )+"'" );

  QString currentQuery = tr( "SELECT EXISTS ((SELECT id FROM humans WHERE id=%1))" ).arg( identifier );
  QSqlQuery qry( database );
  if ( !qry.exec( currentQuery ) || !qry.next() )
  {
    qDebug() << __func__ << __LINE__ << qry.lastError().text() << "\n" << currentQuery;
    return false;
  }
  bool updating = qry.value( 0 ).toBool();
  qry.clear();
  if ( updating )
    currentQuery = tr( "UPDATE humans SET surname=%1, firstname=%2, lastname=%3, addr=%4, phone=%5, \"e-mail\"=%6, birthday=%7 WHERE id=%8" );
  else
    currentQuery = tr( "INSERT INTO humans (surname, firstname, lastname, addr, phone, \"e-mail\", birthday, id) VALUES (%1, %2, %3, %4, %5, %6, %7, %8)" );
  currentQuery = currentQuery.arg( surname, firstname, lastname, address, phone, email, birthday, identifier );
  if ( !qry.exec( currentQuery ) )
  {
    qDebug() << __func__ << __LINE__ << qry.lastError().text() << "\n" << currentQuery;
    return false;
  }
  qry.clear();

  currentQuery = tr( "SELECT NOT EXISTS ((SELECT id FROM clients WHERE clid=%1 AND isorg=0))" ).arg( identifier );
  if ( !qry.exec( currentQuery ) || !qry.next() )
  {
    qDebug() << __func__ << __LINE__ << qry.lastError().text() << "\n" << currentQuery;
    return false;
  }
  bool insert = qry.value( 0 ).toBool();
  qry.clear();
  if ( insert )
  {
    currentQuery = tr( "INSERT INTO clients (clid, isorg) VALUES (%1, %2)" ).arg( identifier, "0" );
    if ( !qry.exec( currentQuery ) )
    {
      qDebug() << __func__ << __LINE__ << qry.lastError().text() << "\n" << currentQuery;
      return false;
    }
    qry.clear();
  }

  int index = pIndex( (int)Initiated, human );
  pTake( (int)Initiated, index );
  pInsert( (int)Selected, human );

  locker()->unlock();

  return true;
}
/*
 * End class definition: *[ MHumanDBWrapper ]*
*/
