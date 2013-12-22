#include "serviceloader.h"

#include "serviceloader_p.h"

#include <QSqlDatabase>


ServiceLoader::ServiceLoader(QObject *parent) :
  QObject(parent)
{
  p = new ServiceLoader_P( this );
  connect( p, SIGNAL(sendError(QString)), SLOT(receivedError(QString)) );
  connect( p, SIGNAL(sendInfo(ServiceInfo*)),
           SIGNAL(newInfo(ServiceInfo*)) );
  connect( p, SIGNAL(started()), SLOT(threadStarted()) );
  connect( p, SIGNAL(finished()), SLOT(threadFinished()) );
  loop = new QEventLoop( this );
}

ServiceLoader::~ServiceLoader()
{
  p->m__LastError.clear();
  delete p;
  p = NULL;
}

QString ServiceLoader::lastError() const
{
  return p->m__LastError;
}

QString ServiceLoader::connectionName()
{
  if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
  {
    p->m__ConnectionName = QSqlDatabase::connectionNames().first();
    emit connectionNameChanged();
  }
  return p->m__ConnectionName;
}

bool ServiceLoader::setConnectionName( QString connectionName )
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

bool ServiceLoader::started() const
{
  return p->isRunning();
}

bool ServiceLoader::load( const QString &filter, bool blockUI )
{
  if ( p->isRunning() )
  {
    receivedError( tr( "Процесс загрузки списка пользователей занят" ) );
    return false;
  }

  p->m__Filter = filter;
  p->start();
  if ( blockUI )
    return ( loop->exec() == 0 );
  else return true;
}

void ServiceLoader::threadStarted()
{
  p->m__Started = true;
  emit startedChanged();
}

void ServiceLoader::threadFinished()
{
  p->m__Started = false;
  loop->exit( ( p->m__Successfully ? 0 : 1 ) );
  emit startedChanged();
}

void ServiceLoader::receivedError( QString errorText )
{
  p->m__LastError = errorText;
  emit lastErrorChanged();
}
