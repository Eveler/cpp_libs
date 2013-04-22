#include "mreportsource_p.h"


MReportSource_P::MReportSource_P(const QString &name, MReportSource *parent) :
  QObject(parent),
  m__Name(name),
  m__ST(MReportSource::ST_Undefined)
{
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
