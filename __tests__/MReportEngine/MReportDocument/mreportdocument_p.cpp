#include "mreportdocument_p.h"

#include <QFileInfo>


MReportDocument_P::MReportDocument_P (const QString &fileName, MReportDocument *parent ) :
  QObject(parent),
  m__ParentDocument(qobject_cast<MReportDocument *>( parent->parent() )),
  m__ChildDocuments(MReportDocumentList()),
  m__Parameters(QList<MReportParameter *>()),
  m__LastError(tr( "none" ))
{
  m__FileName = QString();
  m__Body = QString();
  QFileInfo fi( fileName );
  if ( fi.exists() ) m__FileName = fi.absoluteFilePath();
  else
  {
    QFile f( fileName );
    if ( f.open( QFile::WriteOnly ) ) m__FileName = fi.absoluteFilePath();
    else m__LastError = tr( "Can't create report file" );
    f.close();
  }

  if ( !m__FileName.isEmpty() )
  {
    QFile f( tr( "%1/main.html" ).arg( filePath() ) );
    if ( !f.exists() )
      f.open( QFile::WriteOnly | QFile::Text );
    else
    {
      f.open( QFile::ReadOnly | QFile::Text );
      m__Body = f.readAll();
    }
    f.close();
  }
}

MReportDocument_P::~MReportDocument_P()
{
  m__FileName.clear();

  m__DB.removeDatabase( m__DB.databaseName() );

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
