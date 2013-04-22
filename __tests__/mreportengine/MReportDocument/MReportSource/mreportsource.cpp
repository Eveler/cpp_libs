#include "mreportsource.h"

#include "mreportsource_p.h"


MReportSource::~MReportSource()
{
  delete p;
  p = NULL;
}

MReportSource::MReportSource( const QString &name, MReportDocument *parent ) :
  QObject(parent)
{
  p = new MReportParameter_P( name, this );
}
