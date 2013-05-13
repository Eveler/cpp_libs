#include "mreportparameter_p.h"


MReportParameter_P::MReportParameter_P( const QString &name, MReportParameter *parent ) :
  QObject(parent),
  m__Name(name),
  m__PT(MReportParameter::PT_Undefined),
  m__DT(MReportParameter::DT_Undefined),
  m__Source(QString()),
  m__DataSource(QString()),
  m__Data(QVariant()),
  m__DataIterator(QListIterator<QVariant>( QList<QVariant>() )),
  m__Count(0)
{
}

MReportParameter * MReportParameter_P::p_dptr() const
{
  return qobject_cast<MReportParameter *>( parent() );
}

