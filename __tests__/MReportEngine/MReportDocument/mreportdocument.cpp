#include "mreportdocument.h"

#include "mreportdocument_p.h"


MReportDocument::MReportDocument( const QString &fileName, QObject *parent ) :
  QObject(parent)
{
  p = new MReportDocument_P( this );
}

MReportDocument::~MReportDocument()
{
  delete p;
  p = NULL;
}

const QString & MReportDocument::lastError() const
{
  return p->m__LastError;
}
