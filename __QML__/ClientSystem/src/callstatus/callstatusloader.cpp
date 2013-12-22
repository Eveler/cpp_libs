#include "callstatusloader.h"

#include "callstatusloader_p.h"

#include <QSqlDatabase>


CallstatusLoader::CallstatusLoader(QObject *parent) :
  QObject(parent)
{
  p = new CallstatusLoader_P( this );
  connect( p, SIGNAL(sendError(QString)), SLOT(receivedError(QString)) );
  connect( p, SIGNAL(sendInfo(CallstatusInfo*)),
           SIGNAL(newInfo(CallstatusInfo*)) );
  connect( p, SIGNAL(started()), SLOT(threadStarted()) );
  connect( p, SIGNAL(finished()), SLOT(threadFinished()) );
  loop = new QEventLoop( this );
}

CallstatusLoader::~CallstatusLoader()
{
  p->m__LastError.clear();
  delete p;
  p = NULL;
}

QString CallstatusLoader::lastError() const
{
  return p->m__LastError;
}

QString CallstatusLoader::connectionName()
{
  if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
  {
    p->m__ConnectionName = QSqlDatabase::connectionNames().first();
    emit connectionNameChanged();
  }
  return p->m__ConnectionName;
}

bool CallstatusLoader::setConnectionName( QString connectionName )
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

bool CallstatusLoader::started() const
{
  return p->isRunning();
}

bool CallstatusLoader::load( bool blockUI )
{
  if ( p->isRunning() )
  {
    receivedError( tr( "Процесс загрузки списка пользователей занят" ) );
    return false;
  }

  p->start();
  if ( blockUI )
    return ( loop->exec() == 0 );
  else return true;
}

bool CallstatusLoader::load( QVariant identifier, bool blockUI )
{
  if ( p->isRunning() )
  {
    receivedError( tr( "Процесс загрузки списка пользователей занят" ) );
    return false;
  }

  p->m__LoadIdentifier.setValue( identifier );
  emit started();
  p->start();
  if ( blockUI )
    return ( loop->exec() == 0 );
  else return true;
}

void CallstatusLoader::threadStarted()
{
  p->m__Started = true;
  emit startedChanged();
}

void CallstatusLoader::threadFinished()
{
  p->m__Started = false;
  loop->exit( ( p->m__Successfully ? 0 : 1 ) );
  emit startedChanged();
}

void CallstatusLoader::receivedError( QString errorText )
{
  p->m__LastError = errorText;
  emit lastErrorChanged();
}
