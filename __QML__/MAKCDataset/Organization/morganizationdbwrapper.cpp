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
  QQuickItem(parent)
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
 * End class definition: *[ MHumanDBWrapper ]*
*/
