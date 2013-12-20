#include "humanloader.h"

#include "humanloader_p.h"

#include <QSqlDatabase>


HumanLoader::HumanLoader(QObject *parent) :
  QObject(parent)
{
  p = new HumanLoader_P( this );
  connect( p, SIGNAL(sendError(QString)), SLOT(receivedError(QString)) );
  connect( p, SIGNAL(sendInfo(HumanInfo*)),
           SIGNAL(newInfo(HumanInfo*)) );
  connect( p, SIGNAL(finished()), SLOT(threadFinished()) );
  loop = new QEventLoop( this );
}

HumanLoader::~HumanLoader()
{
  p->m__LastError.clear();
  delete p;
  p = NULL;
}

QString HumanLoader::lastError() const
{
  return p->m__LastError;
}

const QString & HumanLoader::connectionName() const
{
  if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
  {
    p->m__ConnectionName = QSqlDatabase::connectionNames().first();
    emit connectionNameChanged();
  }
  return p->m__ConnectionName;
}

bool HumanLoader::setConnectionName( const QString &connectionName )
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

bool HumanLoader::load( const QString &filter, bool blockUI )
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

void HumanLoader::threadFinished()
{
  loop->exit( ( p->m__Successfully ? 0 : 1 ) );
  emit finished();
}

void HumanLoader::receivedError( QString errorText )
{
  p->m__LastError = errorText;
  emit lastErrorChanged();
}
