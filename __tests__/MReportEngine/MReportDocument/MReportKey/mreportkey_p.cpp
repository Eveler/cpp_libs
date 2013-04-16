#include "mreportkey_p.h"


MReportKey_P::MReportKey_P( const QString &name, MReportKey *parent ) :
  QObject(parent),
  m__Name(name)
{
}

MReportKey * MReportKey_P::p_dptr() const
{
  return qobject_cast<MReportKey *>( parent() );
}
