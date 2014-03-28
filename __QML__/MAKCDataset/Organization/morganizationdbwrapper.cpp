#include "morganizationdbwrapper.h"

#include "makcdataset.h"

#include <QReadWriteLock>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTime>


/*
 * Begin C++ - QML class definition: *[ MOrganization ]*
*/
MOrganization::MOrganization( QQuickItem *parent ) :
  QQuickItem(parent),
  m__Documents(new MDataSourceModel( this ))
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
    int lastFounded = -1;
    while ( qry.next() )
    {
      int identifier = qry.record().value( "id" ).toInt();
      MOrganization *organization = m__ExistOrganizations.value( identifier, NULL );

      int organizationsCount = pCount( (int)Founded );
      int index = lastFounded+1;
      bool insertIntoFounded = true;
      for ( ; index < organizationsCount; index++ )
      {
        MOrganization *oldOrganization = qobject_cast<MOrganization *>( pObject( (int)Founded, index ) );

        if ( identifier > oldOrganization->identifier().toInt() || maxId < oldOrganization->identifier().toInt() )
        {
          //        qDebug() << metaObject()->className() << __func__ << __LINE__ << "\tудалить объект с ID" << identifier;
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
          //        qDebug() << metaObject()->className() << __func__ << __LINE__ << "\tзапомнить объект с ID" << identifier;
          insertIntoFounded = false;
          lastFounded = index;
          break;
        }
      }

      if ( organization == NULL )
      {
        //      qDebug() << metaObject()->className() << __func__ << __LINE__ << "\tобъект с ID" << identifier;
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
      organization->setName( qry.record().value( "fullname" ) );
      organization->setPhone( qry.record().value( "phone" ) );
      organization->setAddress( qry.record().value( "addr" ) );
      organization->setEmail( qry.record().value( "e-mail" ) );
      organization->setDelegate( humanDBWrapper->human( qry.record().value( "human_id" ) ) );
    }
  }
  locker()->unlock();
  qry.clear();

  return true;
}

bool MOrganizationDBWrapper::initiating()
{
  return true;
}

bool MOrganizationDBWrapper::saving( QObject *object )
{
  Q_UNUSED(object)
  return true;
}
/*
 * End class definition: *[ MOrganizationDBWrapper ]*
*/
