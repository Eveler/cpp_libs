#include "declarloader.h"

#include "declarloader_p.h"

#include <QSqlDatabase>


DeclarLoader::DeclarLoader(QObject *parent) :
  QObject(parent)
{
  p = new DeclarLoader_P( this );
  connect( p, SIGNAL(sendError(QString)), SLOT(receivedError(QString)) );
  connect( p, SIGNAL(availableCountChanged()), SIGNAL(countChanged()) );
  connect( p, SIGNAL(started()), SLOT(threadStarted()) );
  connect( p, SIGNAL(finished()), SLOT(threadFinished()) );
  loop = new QEventLoop( this );
}

DeclarLoader::~DeclarLoader()
{
  p->m__LastError.clear();
  delete p;
  p = NULL;
}

QString DeclarLoader::lastError() const
{
  return p->m__LastError;
}

QString DeclarLoader::connectionName()
{
  if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
  {
    p->m__ConnectionName = QSqlDatabase::connectionNames().first();
    emit connectionNameChanged();
  }
  return p->m__ConnectionName;
}

bool DeclarLoader::setConnectionName( QString connectionName )
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

bool DeclarLoader::started() const
{
  return p->isRunning();
}

bool DeclarLoader::load( QString filter, bool blockUI )
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

int DeclarLoader::count() const
{
  return p->m__AvailableCount;
}

DeclarInfo * DeclarLoader::newInfo()
{
  return p->newInfo();
}

void DeclarLoader::threadStarted()
{
  p->m__Started = true;
  emit startedChanged();
}

void DeclarLoader::threadFinished()
{
  p->m__Started = false;
  loop->exit( ( p->m__Successfully ? 0 : 1 ) );
  emit startedChanged();
}

void DeclarLoader::receivedError( QString errorText )
{
  p->m__LastError = errorText;
  emit lastErrorChanged();
}
