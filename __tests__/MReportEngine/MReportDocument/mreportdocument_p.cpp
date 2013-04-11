#include "mreportdocument_p.h"

#include "mreportdocument.h"


MReportDocument_P::MReportDocument_P(MReportDocument *parent) :
  QObject(parent)
{
}

MReportDocument * MReportDocument_P::p_dptr() const
{
  return qobject_cast<MReportDocument *>( parent() );
}
