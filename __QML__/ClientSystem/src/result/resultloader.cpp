#include "resultloader.h"

#include "resultloader_p.h"

#include <QSqlDatabase>


ResultLoader::ResultLoader(QObject *parent) :
  QObject(parent)
{
  p = new ResultLoader_P( this );
  newSource();
  connect( p, SIGNAL(finished()), SLOT(threadFinished()) );
  loop = new QEventLoop( this );
}

ResultLoader::~ResultLoader()
{
  p->m__Errors.clear();
  disconnect( p->m__Source, SIGNAL(destroyed()), this, SLOT(newSource()) );
  delete p;
  p = NULL;
}

QString ResultLoader::error( int errorId ) const
{
  QString errorText = p->m__Errors.value( errorId, QString() );
  p->m__Errors.remove( errorId );
  return errorText;
}

const QString & ResultLoader::connectionName() const
{
  if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
  {
    p->m__ConnectionName = QSqlDatabase::connectionNames().first();
    emit connectionNameChanged();
  }
  return p->m__ConnectionName;
}

bool ResultLoader::setConnectionName( const QString &connectionName ) const
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

bool ResultLoader::load( const QString &filter ) const
{
  if ( p->isRunning() )
  {
    receivedError( tr( "Процесс загрузки списка пользователей занят" ) );
    return false;
  }

  emit started();
  p->m__Filter = filter;
  p->m__Source->clear();
  p->start();
  return ( loop->exec() == 0 );
}

Result * ResultLoader::create() const
{
  return NULL;
}

ResultList * ResultLoader::source() const
{
  return p->m__Source;
}

void ResultLoader::newSource() const
{
  p->m__Source = new ResultList( p->p_dptr() );
  connect( p->m__Source, SIGNAL(destroyed()), SLOT(newSource()) );
  connect( p, SIGNAL(sendResultInfo(ResultInfo)),
           p->m__Source, SLOT(receivedResultInfo(ResultInfo)) );
}

void ResultLoader::threadFinished()
{
  loop->exit( ( p->m__Successfully ? 0 : 1 ) );
  emit finished();
}

void ResultLoader::receivedError( QString errorText ) const
{
  int errorId = p->m__ErrorLastId++;
  p->m__Errors[errorId] = errorText;
  emit errorAdded( errorId );
}
