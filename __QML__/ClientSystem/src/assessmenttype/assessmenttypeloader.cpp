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

const QString & AssessmenttypeLoader::connectionName() const
{
  if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
  {
    p->m__ConnectionName = QSqlDatabase::connectionNames().first();
    emit connectionNameChanged();
  }
  return p->m__ConnectionName;
}

bool AssessmenttypeLoader::setConnectionName( const QString &connectionName )
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

bool AssessmenttypeLoader::load( const QString &filter, bool blockUI )
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

void AssessmenttypeLoader::threadFinished()
{
  loop->exit( ( p->m__Successfully ? 0 : 1 ) );
  emit finished();
}

void AssessmenttypeLoader::receivedError( QString errorText )
{
  p->m__LastError = errorText;
  emit lastErrorChanged();
}
