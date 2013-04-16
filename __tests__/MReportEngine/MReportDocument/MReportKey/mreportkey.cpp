#include "mreportkey.h"

#include "mreportkey_p.h"
#include "mreportdocument.h"


MReportKey::~MReportKey()
{
  delete p;
  p = NULL;
}

void MReportKey::setParent( QObject *parent )
{
  QObject::setParent( parent );
}

MReportKey::MReportKey( const QString &name, MReportDocument *parent ) :
  QObject(parent)
{
  p = new MReportKey_P( name, this );
}
