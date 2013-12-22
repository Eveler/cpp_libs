#include "doctypeloader.h"

#include "doctypeloader_p.h"

#include <QSqlDatabase>


DoctypeLoader::DoctypeLoader(QObject *parent) :
  QObject(parent)
{
  p = new DoctypeLoader_P( this );
  connect( p, SIGNAL(sendError(QString)), SLOT(receivedError(QString)) );
  connect( p, SIGNAL(sendInfo(DoctypeInfo*)),
           SIGNAL(newInfo(DoctypeInfo*)) );
  connect( p, SIGNAL(started()), SLOT(threadStarted()) );
  connect( p, SIGNAL(finished()), SLOT(threadFinished()) );
  loop = new QEventLoop( this );
}

DoctypeLoader::~DoctypeLoader()
{
  p->m__LastError.clear();
  delete p;
  p = NULL;
}

QString DoctypeLoader::lastError() const
{
  return p->m__LastError;
}

QString DoctypeLoader::connectionName()
{
  if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
  {
    p->m__ConnectionName = QSqlDatabase::connectionNames().first();
    emit connectionNameChanged();
  }
  return p->m__ConnectionName;
}

bool DoctypeLoader::setConnectionName( QString connectionName )
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

bool DoctypeLoader::started() const
{
  return p->isRunning();
}

bool DoctypeLoader::load( const QString &filter, bool blockUI )
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

void DoctypeLoader::threadStarted()
{
  p->m__Started = true;
  emit startedChanged();
}

void DoctypeLoader::threadFinished()
{
  p->m__Started = false;
  loop->exit( ( p->m__Successfully ? 0 : 1 ) );
  emit startedChanged();
}

void DoctypeLoader::receivedError( QString errorText )
{
  p->m__LastError = errorText;
  emit lastErrorChanged();
}
