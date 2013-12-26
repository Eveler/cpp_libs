#include "procedureloader.h"

#include "procedureloader_p.h"

#include <QSqlDatabase>


ProcedureLoader::ProcedureLoader(QObject *parent) :
  QObject(parent)
{
  p = new ProcedureLoader_P( this );
  connect( p, SIGNAL(sendError(QString)), SLOT(receivedError(QString)) );
  connect( p, SIGNAL(availableCountChanged()), SIGNAL(countChanged()) );
  connect( p, SIGNAL(started()), SLOT(threadStarted()) );
  connect( p, SIGNAL(finished()), SLOT(threadFinished()) );
  loop = new QEventLoop( this );
}

ProcedureLoader::~ProcedureLoader()
{
  p->m__LastError.clear();
  delete p;
  p = NULL;
}

QString ProcedureLoader::lastError() const
{
  return p->m__LastError;
}

QString ProcedureLoader::connectionName()
{
  if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
  {
    p->m__ConnectionName = QSqlDatabase::connectionNames().first();
    emit connectionNameChanged();
  }
  return p->m__ConnectionName;
}

bool ProcedureLoader::setConnectionName( QString connectionName )
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

bool ProcedureLoader::started() const
{
  return p->isRunning();
}

bool ProcedureLoader::load( QString filter, bool blockUI )
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

int ProcedureLoader::count() const
{
  return p->m__AvailableCount;
}

ProcedureInfo * ProcedureLoader::newInfo()
{
  return p->newInfo();
}

void ProcedureLoader::threadStarted()
{
  p->m__Started = true;
  emit startedChanged();
}

void ProcedureLoader::threadFinished()
{
  p->m__Started = false;
  loop->exit( ( p->m__Successfully ? 0 : 1 ) );
  emit startedChanged();
}

void ProcedureLoader::receivedError( QString errorText )
{
  p->m__LastError = errorText;
  emit lastErrorChanged();
}
