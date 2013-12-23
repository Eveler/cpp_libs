#include "assessmentloader.h"

#include "assessmentloader_p.h"

#include <QSqlDatabase>

#include <QDebug>


AssessmentLoader::AssessmentLoader(QObject *parent) :
  QObject(parent)
{
  p = new AssessmentLoader_P( this );
  connect( p, SIGNAL(sendError(QString)), SLOT(receivedError(QString)) );
  connect( p, SIGNAL(sendInfo(AssessmentInfo*)),
           SIGNAL(newInfo(AssessmentInfo*)) );
  connect( p, SIGNAL(countChanged()), SIGNAL(countChanged()) );
  connect( p, SIGNAL(started()), SLOT(threadStarted()) );
  connect( p, SIGNAL(finished()), SLOT(threadFinished()) );
  loop = new QEventLoop( this );
}

AssessmentLoader::~AssessmentLoader()
{
  p->m__LastError.clear();
  delete p;
  p = NULL;
}

const QString &AssessmentLoader::lastError() const
{
  return p->m__LastError;
}

QString AssessmentLoader::connectionName()
{
  if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
  {
    p->m__ConnectionName = QSqlDatabase::connectionNames().first();
    emit connectionNameChanged();
  }
  return p->m__ConnectionName;
}

bool AssessmentLoader::setConnectionName(QString connectionName )
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

bool AssessmentLoader::started() const
{
  return p->isRunning();
}

bool AssessmentLoader::load( const QString &filter, bool blockUI )
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

int AssessmentLoader::count() const
{
  return p->m__Count;
}

void AssessmentLoader::threadStarted()
{
  p->m__Started = true;
  emit startedChanged();
}

void AssessmentLoader::threadFinished()
{
  p->m__Started = false;
  loop->exit( ( p->m__Successfully ? 0 : 1 ) );
  emit startedChanged();
}

void AssessmentLoader::receivedError( QString errorText )
{
  p->m__LastError = errorText;
  emit lastErrorChanged();
}
