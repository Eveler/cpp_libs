#include "mreportviewer_p.h"
#include "ui_mreportviewer.h"

#include <QWebFrame>

#include <QDebug>


MReportViewer_P::MReportViewer_P( MReportViewer *parent ) :
  QObject(parent)
{
}

MReportViewer * MReportViewer_P::p_dptr() const
{
  return qobject_cast<MReportViewer *>( parent() );
}
