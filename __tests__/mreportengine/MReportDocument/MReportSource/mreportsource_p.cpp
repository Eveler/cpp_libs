#include "mreportsource_p.h"

#include <QUuid>


MReportSource_P::MReportSource_P(const QString &name, MReportSource *parent) :
  QObject(parent),
  m__Name(name),
  m__ST(MReportSource::ST_Undefined)
{
  do
    m__Uuid = QUuid::createUuid().toString();
  while ( QSqlDatabase::contains( m__Uuid ) || exists( m__Uuid ) );
}

MReportSource * MReportSource_P::p_dptr() const
{
  return qobject_cast<MReportSource *>( parent() );
}

MReportDocument * MReportSource_P::reportDocument() const
{
  return qobject_cast<MReportDocument *>( parent()->parent() );
}

bool MReportSource_P::exists( const QString &driverName, const QString &host,
                              int port, const QString &dbName, const QString &userName )
{
  foreach ( MReportSource *source, reportDocument()->reportSources() )
    if ( source != p_dptr() && source->driverName() == driverName && source->host() == host &&
         source->port() == port && source->databaseName() == dbName && source->userName() == userName )
      return true;

  return false;
}

bool MReportSource_P::exists( const QString &uuid )
{
  foreach ( MReportSource *source, reportDocument()->reportSources() )
    if ( source != p_dptr() && source->p->m__Uuid == uuid ) return true;

  return false;
}
