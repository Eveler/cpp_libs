#include "resultloader.h"

#include "resultloader_p.h"

#include <QSqlDatabase>


ResultLoader::ResultLoader(QObject *parent) :
  QObject(parent)
{
  p = new ResultLoader_P( this );
  connect( p, SIGNAL(sendError(QString)), SLOT(receivedError(QString)) );
  connect( p, SIGNAL(availableCountChanged()), SIGNAL(countChanged()) );
  connect( p, SIGNAL(started()), SLOT(threadStarted()) );
  connect( p, SIGNAL(finished()), SLOT(threadFinished()) );
  loop = new QEventLoop( this );
}

ResultLoader::~ResultLoader()
{
  p->m__LastError.clear();
  delete p;
  p = NULL;
}

QString ResultLoader::lastError() const
{
  return p->m__LastError;
}

QString ResultLoader::connectionName()
{
  if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
  {
    p->m__ConnectionName = QSqlDatabase::connectionNames().first();
    emit connectionNameChanged();
  }
  return p->m__ConnectionName;
}

bool ResultLoader::setConnectionName( QString connectionName )
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

bool ResultLoader::started() const
{
  return p->isRunning();
}

bool ResultLoader::load( QString filter, bool blockUI )
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

int ResultLoader::count() const
{
  return p->m__AvailableCount;
}

ResultInfo * ResultLoader::newInfo()
{
  return p->newInfo();
}

void ResultLoader::threadStarted()
{
  p->m__Started = true;
  emit startedChanged();
}

void ResultLoader::threadFinished()
{
  p->m__Started = false;
  loop->exit( ( p->m__Successfully ? 0 : 1 ) );
  emit startedChanged();
}

void ResultLoader::receivedError( QString errorText )
{
  p->m__LastError = errorText;
  emit lastErrorChanged();
}
