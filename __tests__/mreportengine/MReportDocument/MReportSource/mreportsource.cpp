#include "mreportsource.h"

#include "mreportsource_p.h"

#include <QStringList>
#include <QUuid>
#include <QSqlQuery>
#include <QSqlError>


MReportSource::~MReportSource()
{
  delete p;
  p = NULL;
}

const QString & MReportSource::name() const
{
  return p->m__Name;
}

void MReportSource::setSourceType( MReportSource::SourceType sourceType )
{
  p->m__ST = sourceType;
}

MReportSource::SourceType MReportSource::sourceType() const
{
  return p->m__ST;
}

bool MReportSource::setDriverName( const QString & driverName )
{
  if ( !QSqlDatabase::drivers().contains( driverName ) ) return false;

  if ( p->exists( driverName, p->m__Host, p->m__Port, p->m__DatabaseName, p->m__UserName ) )
    return false;

  p->m__DriverName = driverName;

  return true;
}

const QString & MReportSource::driverName() const
{
  return p->m__DriverName;
}

bool MReportSource::setHost( const QString & host )
{
  if ( p->exists( p->m__DriverName, host, p->m__Port, p->m__DatabaseName, p->m__UserName ) )
    return false;

  p->m__Host = host;

  return true;
}

const QString & MReportSource::host() const
{
  return p->m__Host;
}

bool MReportSource::setPort( int port )
{
  if ( p->exists( p->m__DriverName, p->m__Host, port, p->m__DatabaseName, p->m__UserName ) )
    return false;

  p->m__Port = port;

  return true;
}

int MReportSource::port() const
{
  return p->m__Port;
}

bool MReportSource::setDatabaseName( const QString & databaseName )
{
  if ( p->exists( p->m__DriverName, p->m__Host, p->m__Port, databaseName, p->m__UserName ) )
    return false;

  p->m__DatabaseName = databaseName;

  return true;
}

const QString & MReportSource::databaseName() const
{
  return p->m__DatabaseName;
}

bool MReportSource::setUserName( const QString & userName )
{
  if ( p->exists( p->m__DriverName, p->m__Host, p->m__Port, p->m__DatabaseName, userName ) )
    return false;

  p->m__UserName = userName;

  return true;
}

const QString & MReportSource::userName() const
{
  return p->m__UserName;
}

void MReportSource::setPassword( const QString & password )
{
  p->m__Password = password;
}

const QString & MReportSource::password() const
{
  return p->m__Password;
}

QVariant MReportSource::executeQuery( const QString &query )
{
  QVariant result = QVariant();

  QSqlDatabase db = QSqlDatabase::addDatabase( p->m__DriverName, QUuid::createUuid().toString() );
  db.setHostName( p->m__Host );
  db.setPort( p->m__Port );
  db.setDatabaseName( p->m__DatabaseName );
  db.setUserName( p->m__UserName );
  db.setPassword( p->m__Password );
  if ( !db.open() ) return result;

  QSqlQuery qry = db.exec( query );
  if ( db.lastError().isValid() ) return result;
  if ( qry.lastError().isValid() || !qry.next() ) return result;

  result = qry.value( 0 );
  db.close();
  db.removeDatabase( db.connectionName() );

  return result;
}

MReportSource::MReportSource( const QString &name, MReportDocument *parent ) :
  QObject(parent)
{
  p = new MReportSource_P( name, this );
}
