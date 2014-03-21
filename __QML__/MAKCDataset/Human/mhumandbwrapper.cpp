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

bool MHumanDBWrapper::searching( const QString &queryText )
{
  MDocumentDBWrapper *documentDBWrapper = qobject_cast<MDocumentDBWrapper *>( MAKCDataset::MAKC_DocumentDataSource()->dbWrapper() );

  QString currentQuery = queryText;
  if ( currentQuery.isEmpty() ) currentQuery = tr( "SELECT * FROM humans ORDER BY id" );
  else currentQuery = tr( "SELECT * FROM humans WHERE %1 ORDER BY id" ).arg( currentQuery );

  QSqlDatabase database = QSqlDatabase::database( connectionName(), false );
  if ( !database.open() )
  {
    qDebug() << __func__ << __LINE__ << database.lastError().text();
    return false;
  }

  QSqlQuery qry( currentQuery, database );
  if ( qry.lastError().isValid() )
  {
    qDebug() << __func__ << __LINE__ << qry.lastError().text();
    return false;
  }

  locker()->lockForWrite();
  while ( pCount( (int)Founded ) > 0 )
  {
    QObject *human = pTake( (int)Founded, 0 );
    if ( pIndex( (int)Selected, human ) == -1 )
    {
      documentDBWrapper->releaseHumanDocuments( qobject_cast<MHuman *>( human ) );
      connect( this, SIGNAL(aboutToReleaseOldResources()), human, SLOT(deleteLater()) );
    }
  }
  while ( qry.next() )
  {
    MHuman *human = new MHuman;
    human->setIdentifier( qry.record().value( "id" ) );
    human->setSurname( qry.record().value( "surname" ) );
    human->setFirstname( qry.record().value( "firstname" ) );
    human->setLastname( qry.record().value( "lastname" ) );
    human->setPhone( qry.record().value( "phone" ) );
    human->setAddress( qry.record().value( "addr" ) );
    human->setEmail( qry.record().value( "e-mail" ) );
    human->setBirthday( qry.record().value( "birthday" ) );
    pInsert( (int)Founded, human );
    human->moveToThread( parent()->thread() );
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
  MHuman *human = new MHuman;
  human->setIdentifier( qry.record().value( 0 ) );
  locker()->lockForWrite();
  pInsert( (int)Initiated, human );
  locker()->unlock();
  human->moveToThread( parent()->thread() );
  qry.clear();

  return true;
}

bool MHumanDBWrapper::saving( QObject *object )
{
  MHuman *human = qobject_cast<MHuman *>( object );
  if ( human == NULL )
  {
    qDebug() << __func__ << __LINE__ << "Human object is NULL";
    return false;
  }

  QSqlDatabase database = QSqlDatabase::database( connectionName(), false );
  if ( !database.open() )
  {
    qDebug() << __func__ << __LINE__ << database.lastError().text();
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

  int index = pIndex( (int)Initiated, human );
  pTake( (int)Initiated, index );
  pInsert( (int)Selected, human );

  return true;
}
/*
 * End class definition: *[ MHumanDBWrapper ]*
*/