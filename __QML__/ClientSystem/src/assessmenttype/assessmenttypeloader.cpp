#include "assessmenttypeloader.h"

#include "assessmenttypeloader_p.h"

#include <QSqlDatabase>


AssessmenttypeLoader::AssessmenttypeLoader(QObject *parent) :
  QObject(parent)
{
  p = new AssessmenttypeLoader_P( this );
  connect( p, SIGNAL(sendError(QString)), SLOT(receivedError(QString)) );
  connect( p, SIGNAL(sendInfo(AssessmenttypeInfo*)),
           SIGNAL(newInfo(AssessmenttypeInfo*)) );
  connect( p, SIGNAL(countChanged()), SIGNAL(countChanged()) );
  connect( p, SIGNAL(started()), SLOT(threadStarted()) );
  connect( p, SIGNAL(finished()), SLOT(threadFinished()) );
  loop = new QEventLoop( this );
}

AssessmenttypeLoader::~AssessmenttypeLoader()
{
  p->m__LastError.clear();
  delete p;
  p = NULL;
}

QString AssessmenttypeLoader::lastError() const
{
  return p->m__LastError;
}

QString AssessmenttypeLoader::connectionName()
{
  if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
  {
    p->m__ConnectionName = QSqlDatabase::connectionNames().first();
    emit connectionNameChanged();
  }
  return p->m__ConnectionName;
}

bool AssessmenttypeLoader::setConnectionName( QString connectionName )
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

bool AssessmenttypeLoader::started() const
{
  return p->isRunning();
}

bool AssessmenttypeLoader::load( const QString &filter, bool blockUI )
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

int AssessmenttypeLoader::count() const
{
  return p->m__Count;
}

void AssessmenttypeLoader::threadStarted()
{
  p->m__Started = true;
  emit startedChanged();
}

void AssessmenttypeLoader::threadFinished()
{
  p->m__Started = false;
  loop->exit( ( p->m__Successfully ? 0 : 1 ) );
  emit startedChanged();
}

void AssessmenttypeLoader::receivedError( QString errorText )
{
  p->m__LastError = errorText;
  emit lastErrorChanged();
}
