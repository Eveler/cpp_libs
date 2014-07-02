#include "morganizationdbwrapper.h"

#include "makcdataset.h"

#include <QReadWriteLock>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTime>

#include "amslogger.h"


/*
 * Begin C++ - QML class definition: *[ MOrganization ]*
*/
MOrganization::MOrganization( QQuickItem *parent ) :
  QQuickItem(parent),
  m__Delegate(NULL),
  m__Documents(new MDataSourceModel( this )),
  m__ExternalLinksCount(0)
{
}

MOrganization::~MOrganization()
{
//  qDebug() << __func__ << this;
}

QVariant MOrganization::identifier() const
{
  return m__Identifier;
}

void MOrganization::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;
  emit identifierChanged();
}

const QVariant & MOrganization::name() const
{
  return m__Name;
}

void MOrganization::setName( const QVariant &name )
{
  m__Name = name;
  emit nameChanged();
}

const QVariant & MOrganization::phone() const
{
  return m__Phone;
}

void MOrganization::setPhone( const QVariant &phone )
{
  m__Phone = phone;
  emit phoneChanged();
}

const QVariant & MOrganization::address() const
{
  return m__Address;
}

void MOrganization::setAddress( const QVariant &address )
{
  m__Address = address;
  emit addressChanged();
}

const QVariant & MOrganization::email() const
{
  return m__Email;
}

void MOrganization::setEmail( const QVariant &email )
{
  m__Email = email;
  emit emailChanged();
}

MHuman * MOrganization::delegate() const
{
  return m__Delegate;
}

void MOrganization::setDelegate( MHuman *delegate )
{
  m__Delegate = delegate;
  emit delegateChanged();
}

MDataSourceModel * MOrganization::documents() const
{
  return m__Documents;
}

int MOrganization::externalLinksCount() const
{
  return m__ExternalLinksCount;
}

int MOrganization::incrementExternalLinks()
{
  return m__ExternalLinksCount++;
}

int MOrganization::decrementExternalLinks()
{
  if ( m__ExternalLinksCount > 0 ) m__ExternalLinksCount--;

  return m__ExternalLinksCount;
}
/*
 * End class definition: *[ MOrganization ]*
*/


/*
 * Begin C++ class definition: *[ MOrganizationDBWrapper ]*
*/
MOrganizationDBWrapper::MOrganizationDBWrapper( MAbstractDataSource *parent ) :
  MAbstractDBWrapper(parent)
{
}

MOrganizationDBWrapper::~MOrganizationDBWrapper()
{
  m__ExistOrganizations.clear();
}

MOrganization * MOrganizationDBWrapper::organization( QVariant identifier )
{
  Q_UNUSED(identifier)
  return NULL;
}

bool MOrganizationDBWrapper::searching( const QString &queryText )
{
  MDocumentDBWrapper *documentDBWrapper = qobject_cast<MDocumentDBWrapper *>( MAKCDataset::MAKC_DocumentDataSource()->dbWrapper() );
  MHumanDBWrapper *humanDBWrapper = qobject_cast<MHumanDBWrapper *>( MAKCDataset::MAKC_HumanDataSource()->dbWrapper() );

  QString currentQuery = queryText;
  if ( currentQuery.isEmpty() ) currentQuery = tr( "SELECT * FROM orgs ORDER BY id" );
  else currentQuery = tr( "SELECT * FROM orgs WHERE %1 ORDER BY id" ).arg( currentQuery );
  QString maxIdQuery = queryText;
  if ( maxIdQuery.isEmpty() ) maxIdQuery = tr( "SELECT max(id) FROM orgs" );
  else maxIdQuery = tr( "SELECT max(id) FROM orgs WHERE %1" ).arg( maxIdQuery );

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
      MOrganization *oldOrganization = qobject_cast<MOrganization *>( pTake( (int)Founded, 0 ) );

      if ( oldOrganization->externalLinksCount() == 0 && pIndex( (int)Initiated, oldOrganization ) == -1 )
      {
        documentDBWrapper->releaseOrganizationDocuments( oldOrganization );
        m__ExistOrganizations.remove( oldOrganization->identifier().toInt() );
        connect( this, SIGNAL(aboutToReleaseOldResources()), oldOrganization, SLOT(deleteLater()) );
      }
    }
  }
  else
  {
    QVariantList humanIds;
    while ( qry->next() )
      humanIds << qry->record().value( "human_id" );
    humanDBWrapper->humans( humanIds );

    qry->seek( -1 );
    int lastFounded = -1;
    while ( qry->next() )
    {
      int identifier = qry->record().value( "id" ).toInt();
      MOrganization *organization = m__ExistOrganizations.value( identifier, NULL );

      int organizationsCount = pCount( (int)Founded );
      int index = lastFounded+1;
      bool insertIntoFounded = true;
      for ( ; index < organizationsCount; index++ )
      {
        MOrganization *oldOrganization = qobject_cast<MOrganization *>( pObject( (int)Founded, index ) );

        if ( identifier > oldOrganization->identifier().toInt() || maxId < oldOrganization->identifier().toInt() )
        {
          //        LogDebug() << "\tудалить объект с ID" << identifier;
          pTake( (int)Founded, index );
          index--;
          organizationsCount--;

          if ( oldOrganization->externalLinksCount() == 0 && pIndex( (int)Initiated, oldOrganization ) == -1 )
          {
            documentDBWrapper->releaseOrganizationDocuments( oldOrganization );
            m__ExistOrganizations.remove( oldOrganization->identifier().toInt() );
            connect( this, SIGNAL(aboutToReleaseOldResources()), oldOrganization, SLOT(deleteLater()) );
          }
        }
        else if ( identifier == oldOrganization->identifier().toInt() )
        {
          //        LogDebug() << "\tзапомнить объект с ID" << identifier;
          insertIntoFounded = false;
          lastFounded = index;
          break;
        }
      }

      if ( organization == NULL )
      {
        //      LogDebug() << "\tобъект с ID" << identifier;
        organization = new MOrganization;
        organization->moveToThread( parent()->thread() );
        m__ExistOrganizations[identifier] = organization;
        organization->setIdentifier( identifier );
      }
      if ( insertIntoFounded )
      {
        lastFounded++;
        pInsert( (int)Founded, organization, lastFounded );
      }
      organization->setName( qry->record().value( "fullname" ) );
      organization->setPhone( qry->record().value( "phone" ) );
      organization->setAddress( qry->record().value( "addr" ) );
      organization->setEmail( qry->record().value( "e-mail" ) );
      organization->setDelegate( humanDBWrapper->human( qry->record().value( "human_id" ) ) );
    }

    int organizationsCount = pCount( (int)Founded );
    for ( int index = lastFounded+1; index < organizationsCount; index++ )
    {
      MOrganization *oldOrganization = qobject_cast<MOrganization *>( pObject( (int)Founded, index ) );

      pTake( (int)Founded, index );
      index--;
      organizationsCount--;

      if ( oldOrganization->externalLinksCount() == 0 && pIndex( (int)Initiated, oldOrganization ) == -1 )
      {
        documentDBWrapper->releaseOrganizationDocuments( oldOrganization );
        m__ExistOrganizations.remove( oldOrganization->identifier().toInt() );
        connect( this, SIGNAL(aboutToReleaseOldResources()), oldOrganization, SLOT(deleteLater()) );
      }
    }
  }
  qry->clear();
  delete qry;
  qry = NULL;

  locker()->unlock();

  return true;
}

bool MOrganizationDBWrapper::initiating()
{
  QSqlDatabase database = QSqlDatabase::database( connectionName(), false );
  if ( !database.open() )
  {
    LogDebug() << database.lastError().text();
    return false;
  }

  QString currentQuery = tr( "SELECT nextval('orgs_id_seq')" );
  QSqlQuery qry( currentQuery, database );
  if ( qry.lastError().isValid() || !qry.next() )
  {
    LogDebug() << qry.lastError().text();
    return false;
  }
  locker()->lockForWrite();

  MOrganization *organization = new MOrganization;
  organization->setIdentifier( qry.record().value( 0 ) );
  pInsert( (int)Initiated, organization );
  organization->moveToThread( parent()->thread() );
  qry.clear();

  locker()->unlock();

  return true;
}

bool MOrganizationDBWrapper::saving( QObject *object )
{
  QSqlDatabase database = QSqlDatabase::database( connectionName(), false );
  if ( !database.open() )
  {
    LogDebug() << database.lastError().text();

    return false;
  }

  locker()->lockForWrite();

  MOrganization *organization = qobject_cast<MOrganization *>( object );
  if ( organization == NULL )
  {
    LogDebug() << "Organization object is NULL";
    locker()->unlock();

    return false;
  }

  QString identifier = organization->identifier().toString();
  QString name = ( organization->name().isNull() ? "NULL" : "'"+organization->name().toString().replace( "'", "''" )+"'" );
  QString address = ( organization->address().isNull() ? "NULL" : "'"+organization->address().toString().replace( "'", "''" )+"'" );
  QString phone = ( organization->phone().isNull() ? "NULL" : "'"+organization->phone().toString().replace( "'", "''" )+"'" );
  QString email = ( organization->email().isNull() ? "NULL" : "'"+organization->email().toString().replace( "'", "''" )+"'" );
  QString delegate = ( organization->delegate() == NULL ? "NULL" : organization->delegate()->identifier().toString() );

  QString currentQuery = tr( "SELECT EXISTS ((SELECT id FROM orgs WHERE id=%1))" ).arg( identifier );
  QSqlQuery qry( database );
  if ( !qry.exec( currentQuery ) || !qry.next() )
  {
    LogDebug() << qry.lastError().text() << "\n" << currentQuery;
    locker()->unlock();

    return false;
  }
  bool updating = qry.value( 0 ).toBool();
  qry.clear();
  if ( updating )
    currentQuery = tr( "UPDATE orgs SET fullname=$name$, addr=$address$, phone=$phone$, \"e-mail\"=$email$, human_id=$delegate$ WHERE id=$identifier$" );
  else
    currentQuery = tr( "INSERT INTO orgs (fullname, addr, phone, \"e-mail\", human_id, id) VALUES ($name, $address$, $phone$, $email$, $delegate$, $identifier$)" );
  currentQuery = currentQuery.replace( tr( "$name$" ), name );
  currentQuery = currentQuery.replace( tr( "$address$" ), address );
  currentQuery = currentQuery.replace( tr( "$phone$" ), phone );
  currentQuery = currentQuery.replace( tr( "$email$" ), email );
  currentQuery = currentQuery.replace( tr( "$delegate$" ), delegate );
  currentQuery = currentQuery.replace( tr( "$identifier$" ), identifier );
  if ( !qry.exec( currentQuery ) )
  {
    LogDebug() << qry.lastError().text() << "\n" << currentQuery;
    locker()->unlock();

    return false;
  }
  qry.clear();

  currentQuery = tr( "SELECT NOT EXISTS ((SELECT id FROM clients WHERE clid=%1 AND isorg=1))" ).arg( identifier );
  if ( !qry.exec( currentQuery ) || !qry.next() )
  {
    LogDebug() << qry.lastError().text() << "\n" << currentQuery;
    locker()->unlock();

    return false;
  }
  bool insert = qry.value( 0 ).toBool();
  qry.clear();
  if ( insert )
  {
    currentQuery = tr( "INSERT INTO clients (clid, isorg) VALUES (%1, %2)" ).arg( identifier, "1" );
    if ( !qry.exec( currentQuery ) )
    {
      LogDebug() << qry.lastError().text() << "\n" << currentQuery;
      locker()->unlock();

      return false;
    }
    qry.clear();
  }

  m__ExistOrganizations[identifier.toInt()] = organization;
  pInsert( (int)Founded, organization );
  int index = pIndex( (int)Initiated, organization );
  pTake( (int)Initiated, index );

  locker()->unlock();

  return true;
}
/*
 * End class definition: *[ MOrganizationDBWrapper ]*
*/
