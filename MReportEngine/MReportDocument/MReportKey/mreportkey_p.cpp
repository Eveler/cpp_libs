#include "mreportkey_p.h"


MReportKey_P::MReportKey_P( const QString &name, MReportKey *parent ) :
  QObject(parent),
  m__Name(name),
  m__KT(MReportKey::KT_Undefined),
  m__DT(MReportKey::DT_Undefined),
  m__Source(QString()),
  m__DataSource(QString()),
  m__DataFormat(QString())
{
}

MReportKey * MReportKey_P::p_dptr() const
{
  return qobject_cast<MReportKey *>( parent() );
}
