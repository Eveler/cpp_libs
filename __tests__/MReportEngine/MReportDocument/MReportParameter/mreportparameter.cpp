#include "mreportparameter.h"

#include "mreportparameter_p.h"
#include "mreportdocument.h"


MReportParameter::~MReportParameter()
{
  delete p;
  p = NULL;
}

MReportDocument * MReportParameter::reportDocument() const
{
  return qobject_cast<MReportDocument *>( parent() );
}

const QString & MReportParameter::name() const
{
  return p->m__Name;
}

void MReportParameter::setParent( QObject *parent )
{
  QObject::setParent( parent );
}

MReportParameter::MReportParameter( const QString &name, MReportDocument *parent ) :
  QObject(parent)
{
  p = new MReportParameter_P( name, this );
}
