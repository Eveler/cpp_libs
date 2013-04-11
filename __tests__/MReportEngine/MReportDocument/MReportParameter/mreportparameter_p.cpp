#include "mreportparameter_p.h"


MReportParameter_P::MReportParameter_P( const QString &name, MReportParameter *parent ) :
  QObject(parent),
  m__Name(name)
{
}

MReportParameter * MReportParameter_P::p_dptr() const
{
  return qobject_cast<MReportParameter *>( parent() );
}
