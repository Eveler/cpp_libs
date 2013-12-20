#include "resultwayloader.h"

#include "resultwayloader_p.h"

#include <QSqlDatabase>


ResultwayLoader::ResultwayLoader(QObject *parent) :
  QObject(parent)
{
  p = new ResultwayLoader_P( this );
  connect( p, SIGNAL(sendError(QString)), SLOT(receivedError(QString)) );
  connect( p, SIGNAL(sendInfo(ResultwayInfo*)),
           SIGNAL(newInfo(ResultwayInfo*)) );
  connect( p, SIGNAL(finished()), SLOT(threadFinished()) );
  loop = new QEventLoop( this );
}

ResultwayLoader::~ResultwayLoader()
{
  p->m__LastError.clear();
  delete p;
  p = NULL;
}

QString ResultwayLoader::lastError() const
{
  return p->m__LastError;
}

const QString & ResultwayLoader::connectionName() const
{
  if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
  {
    p->m__ConnectionName = QSqlDatabase::connectionNames().first();
    emit connectionNameChanged();
  }
  return p->m__ConnectionName;
}

bool ResultwayLoader::setConnectionName( const QString &connectionName )
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

bool ResultwayLoader::load( const QString &filter, bool blockUI )
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

void ResultwayLoader::threadFinished()
{
  loop->exit( ( p->m__Successfully ? 0 : 1 ) );
  emit finished();
}

void ResultwayLoader::receivedError( QString errorText )
{
  p->m__LastError = errorText;
  emit lastErrorChanged();
}
