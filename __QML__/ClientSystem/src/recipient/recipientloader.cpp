#include "recipientloader.h"

#include "recipientloader_p.h"

#include <QSqlDatabase>


RecipientLoader::RecipientLoader(QObject *parent) :
  QObject(parent)
{
  p = new RecipientLoader_P( this );
  connect( p, SIGNAL(sendError(QString)), SLOT(receivedError(QString)) );
  connect( p, SIGNAL(availableCountChanged()), SIGNAL(countChanged()) );
  connect( p, SIGNAL(started()), SLOT(threadStarted()) );
  connect( p, SIGNAL(finished()), SLOT(threadFinished()) );
  loop = new QEventLoop( this );
}

RecipientLoader::~RecipientLoader()
{
  p->m__LastError.clear();
  delete p;
  p = NULL;
}

QString RecipientLoader::lastError() const
{
  return p->m__LastError;
}

QString RecipientLoader::connectionName()
{
  if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
  {
    p->m__ConnectionName = QSqlDatabase::connectionNames().first();
    emit connectionNameChanged();
  }
  return p->m__ConnectionName;
}

bool RecipientLoader::setConnectionName( QString connectionName )
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

bool RecipientLoader::started() const
{
  return p->isRunning();
}

bool RecipientLoader::load( QString filter, bool blockUI )
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

int RecipientLoader::count() const
{
  return p->m__AvailableCount;
}

RecipientInfo * RecipientLoader::newInfo()
{
  return p->newInfo();
}

void RecipientLoader::threadStarted()
{
  p->m__Started = true;
  emit startedChanged();
}

void RecipientLoader::threadFinished()
{
  p->m__Started = false;
  loop->exit( ( p->m__Successfully ? 0 : 1 ) );
  emit startedChanged();
}

void RecipientLoader::receivedError( QString errorText )
{
  p->m__LastError = errorText;
  emit lastErrorChanged();
}
