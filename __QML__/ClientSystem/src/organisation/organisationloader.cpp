#include "organisationloader.h"

#include "organisationloader_p.h"

#include <QSqlDatabase>


OrganisationLoader::OrganisationLoader(QObject *parent) :
  QObject(parent)
{
  p = new OrganisationLoader_P( this );
  connect( p, SIGNAL(sendError(QString)), SLOT(receivedError(QString)) );
  connect( p, SIGNAL(sendInfo(OrganisationInfo*)),
           SIGNAL(newInfo(OrganisationInfo*)) );
  connect( p, SIGNAL(finished()), SLOT(threadFinished()) );
  loop = new QEventLoop( this );
}

OrganisationLoader::~OrganisationLoader()
{
  p->m__LastError.clear();
  delete p;
  p = NULL;
}

QString OrganisationLoader::lastError() const
{
  return p->m__LastError;
}

const QString & OrganisationLoader::connectionName() const
{
  if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
  {
    p->m__ConnectionName = QSqlDatabase::connectionNames().first();
    emit connectionNameChanged();
  }
  return p->m__ConnectionName;
}

bool OrganisationLoader::setConnectionName( const QString &connectionName )
{
  if ( !QSqlDatabase::contains( connectionName ) )
  {
    QString connection = this->connectionName();
    if ( connection.isEmpty() ) return false;
  }
  else
  {
    p->m__ConnectionName = connectionName;
    emit connectionNameChanged();
  }
  return true;
}

bool OrganisationLoader::load( const QString &filter, bool blockUI )
{
  if ( p->isRunning() )
  {
    receivedError( tr( "Процесс загрузки списка пользователей занят" ) );
    return false;
  }

  emit started();
  p->m__Filter = filter;
  p->start();
  if ( blockUI )
    return ( loop->exec() == 0 );
  else return true;
}

void OrganisationLoader::threadFinished()
{
  loop->exit( ( p->m__Successfully ? 0 : 1 ) );
  emit finished();
}

void OrganisationLoader::receivedError( QString errorText )
{
  p->m__LastError = errorText;
  emit lastErrorChanged();
}
