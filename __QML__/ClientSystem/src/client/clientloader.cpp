#include "clientloader.h"

#include "clientloader_p.h"

#include <QSqlDatabase>


ClientLoader::ClientLoader(QObject *parent) :
  QObject(parent)
{
  p = new ClientLoader_P( this );
  connect( p, SIGNAL(sendError(QString)), SLOT(receivedError(QString)) );
  connect( p, SIGNAL(availableCountChanged()), SIGNAL(countChanged()) );
  connect( p, SIGNAL(started()), SLOT(threadStarted()) );
  connect( p, SIGNAL(finished()), SLOT(threadFinished()) );
  loop = new QEventLoop( this );
}

ClientLoader::~ClientLoader()
{
  p->m__LastError.clear();
  delete p;
  p = NULL;
}

QString ClientLoader::lastError() const
{
  return p->m__LastError;
}

QString ClientLoader::connectionName()
{
  if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
  {
    p->m__ConnectionName = QSqlDatabase::connectionNames().first();
    emit connectionNameChanged();
  }
  return p->m__ConnectionName;
}

bool ClientLoader::setConnectionName( QString connectionName )
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

bool ClientLoader::started() const
{
  return p->isRunning();
}

bool ClientLoader::load( QString filter, bool blockUI )
{
  if ( p->m__Started || p->m__AvailableCount != p->m__ReceivedCount )
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

int ClientLoader::count() const
{
  return p->m__AvailableCount;
}

ClientInfo * ClientLoader::newInfo()
{
  return p->newInfo();
}

void ClientLoader::threadStarted()
{
  p->m__Started = true;
  emit startedChanged();
}

void ClientLoader::threadFinished()
{
  p->m__Started = false;
  loop->exit( ( p->m__Successfully ? 0 : 1 ) );
  emit startedChanged();
}

void ClientLoader::receivedError( QString errorText )
{
  p->m__LastError = errorText;
  emit lastErrorChanged();
}
