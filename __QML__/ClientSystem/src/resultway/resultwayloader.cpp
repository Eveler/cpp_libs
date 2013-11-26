#include "resultwayloader.h"

#include "resultwayloader_p.h"

#include <QSqlDatabase>


ResultwayLoader::ResultwayLoader(QObject *parent) :
  QObject(parent)
{
  p = new ResultwayLoader_P( this );
  newSource();
  connect( p, SIGNAL(finished()), SLOT(threadFinished()) );
  loop = new QEventLoop( this );
}

ResultwayLoader::~ResultwayLoader()
{
  p->m__Errors.clear();
  disconnect( p->m__Source, SIGNAL(destroyed()), this, SLOT(newSource()) );
  delete p;
  p = NULL;
}

QString ResultwayLoader::error( int errorId ) const
{
  QString errorText = p->m__Errors.value( errorId, QString() );
  p->m__Errors.remove( errorId );
  return errorText;
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

bool ResultwayLoader::setConnectionName( const QString &connectionName ) const
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

bool ResultwayLoader::load( const QString &filter ) const
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

Resultway * ResultwayLoader::create() const
{
  return NULL;
}

ResultwayList * ResultwayLoader::source() const
{
  return p->m__Source;
}

void ResultwayLoader::newSource() const
{
  p->m__Source = new ResultwayList( p->p_dptr() );
  connect( p->m__Source, SIGNAL(destroyed()), SLOT(newSource()) );
  connect( p, SIGNAL(sendResultwayInfo(ResultwayInfo)),
           p->m__Source, SLOT(receivedResultwayInfo(ResultwayInfo)) );
}

void ResultwayLoader::threadFinished()
{
  loop->exit( ( p->m__Successfully ? 0 : 1 ) );
  emit finished();
}

void ResultwayLoader::receivedError( QString errorText ) const
{
  int errorId = p->m__ErrorLastId++;
  p->m__Errors[errorId] = errorText;
  emit errorAdded( errorId );
}
