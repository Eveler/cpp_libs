#include "mreportparameter_p.h"


MReportParameter_P::MReportParameter_P( const QString &name, MReportParameter *parent ) :
  QObject(parent),
  m__Name(name),
  m__PT(MReportParameter::PT_Undefined),
  m__DT(MReportParameter::DT_Undefined),
  m__DataSource(QString()),
  m__Data(QVariant())
{
}

MReportParameter * MReportParameter_P::p_dptr() const
{
  return qobject_cast<MReportParameter *>( parent() );
}
