#include "mreportdocument_p.h"

#include <QFileInfo>


MReportDocument_P::MReportDocument_P (const QString &fileName, MReportDocument *parent ) :
  QObject(parent),
  m__ParentDocument(qobject_cast<MReportDocument *>( parent->parent() )),
  m__ChildDocuments(MReportDocumentList()),
  m__Sources(MReportSourceList()),
  m__Parameters(MReportParameterList()),
  m__Keys(MReportKeyList())
{
  m__FileName = fileName;
  m__Body = QString();
  m__LastError = QString();
}

MReportDocument_P::~MReportDocument_P()
{
  m__FileName.clear();

  m__ParentDocument = NULL;
  while ( !m__ChildDocuments.isEmpty() )
  {
    MReportDocument *reportDocument = m__ChildDocuments.takeFirst();
    delete reportDocument;
    reportDocument = NULL;
  }

  while ( !m__Parameters.isEmpty() )
  {
    MReportParameter *reportParameter = m__Parameters.takeFirst();
    delete reportParameter;
    reportParameter = NULL;
  }

  while ( !m__Keys.isEmpty() )
  {
    MReportKey *reportKey = m__Keys.takeFirst();
    delete reportKey;
    reportKey = NULL;
  }

  m__LastError.clear();
}

QString MReportDocument_P::filePath() const
{
  QFileInfo fi( m__FileName );
  return fi.path();
}

QString MReportDocument_P::alias() const
{
  QFileInfo fi( m__FileName );
  return fi.baseName();
}

MReportDocument * MReportDocument_P::p_dptr() const
{
  return qobject_cast<MReportDocument *>( parent() );
}

void MReportDocument_P::increaseProgressValue( double progress )
{
  double index = 10000./(double)m__Units;
  if ( progress == 10000. )
  {
    m__BufProgress += index;
    m__Progress = m__BufProgress;
  }
  else m__Progress = m__BufProgress+(index*(progress/10000));

  p_dptr()->emitProgress();
}
