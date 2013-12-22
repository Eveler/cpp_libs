#include "trusteeloader.h"

#include "trusteeloader_p.h"

#include <QSqlDatabase>


TrusteeLoader::TrusteeLoader(QObject *parent) :
  QObject(parent)
{
  p = new TrusteeLoader_P( this );
  connect( p, SIGNAL(sendError(QString)), SLOT(receivedError(QString)) );
  connect( p, SIGNAL(sendInfo(TrusteeInfo*)),
           SIGNAL(newInfo(TrusteeInfo*)) );
  connect( p, SIGNAL(started()), SLOT(threadStarted()) );
  connect( p, SIGNAL(finished()), SLOT(threadFinished()) );
  loop = new QEventLoop( this );
}

TrusteeLoader::~TrusteeLoader()
{
  p->m__LastError.clear();
  delete p;
  p = NULL;
}

QString TrusteeLoader::lastError() const
{
  return p->m__LastError;
}

QString TrusteeLoader::connectionName()
{
  if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
  {
    p->m__ConnectionName = QSqlDatabase::connectionNames().first();
    emit connectionNameChanged();
  }
  return p->m__ConnectionName;
}

bool TrusteeLoader::setConnectionName( QString connectionName )
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

bool TrusteeLoader::started() const
{
  return p->isRunning();
}

bool TrusteeLoader::load( const QString &filter, bool blockUI )
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

void TrusteeLoader::threadStarted()
{
  p->m__Started = true;
  emit startedChanged();
}

void TrusteeLoader::threadFinished()
{
  p->m__Started = false;
  loop->exit( ( p->m__Successfully ? 0 : 1 ) );
  emit startedChanged();
}

void TrusteeLoader::receivedError( QString errorText )
{
  p->m__LastError = errorText;
  emit lastErrorChanged();
}
