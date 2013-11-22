#include "declarclientloader.h"

#include "declarclientloader_p.h"

#include <QSqlDatabase>


DeclarClientLoader::DeclarClientLoader(QObject *parent) :
  QObject(parent)
{
  p = new DeclarClientLoader_P( this );
  newSource();
  connect( p, SIGNAL(finished()), SLOT(threadFinished()) );
  loop = new QEventLoop( this );
}

DeclarClientLoader::~DeclarClientLoader()
{
  p->m__Errors.clear();
  disconnect( p->m__Source, SIGNAL(destroyed()), this, SLOT(newSource()) );
  delete p;
  p = NULL;
}

QString DeclarClientLoader::error( int errorId ) const
{
  QString errorText = p->m__Errors.value( errorId, QString() );
  p->m__Errors.remove( errorId );
  return errorText;
}

const QString & DeclarClientLoader::connectionName() const
{
  if ( p->m__ConnectionName.isEmpty() && !QSqlDatabase::connectionNames().isEmpty() )
  {
    p->m__ConnectionName = QSqlDatabase::connectionNames().first();
    emit connectionNameChanged();
  }
  return p->m__ConnectionName;
}

bool DeclarClientLoader::setConnectionName( const QString &connectionName ) const
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

bool DeclarClientLoader::load( const QString &filter ) const
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

DeclarClient * DeclarClientLoader::create() const
{
  return NULL;
}

DeclarClientList * DeclarClientLoader::source() const
{
  return p->m__Source;
}

void DeclarClientLoader::newSource() const
{
  p->m__Source = new DeclarClientList( p->p_dptr() );
  connect( p->m__Source, SIGNAL(destroyed()), SLOT(newSource()) );
  connect( p, SIGNAL(sendDeclarClientInfo(DeclarClientInfo)),
           p->m__Source, SLOT(receivedDeclarClientInfo(DeclarClientInfo)) );
}

void DeclarClientLoader::threadFinished()
{
  loop->exit( ( p->m__Successfully ? 0 : 1 ) );
  emit finished();
}

void DeclarClientLoader::receivedError( QString errorText ) const
{
  int errorId = p->m__ErrorLastId++;
  p->m__Errors[errorId] = errorText;
  emit errorAdded( errorId );
}
