#include "mreportdocument.h"

#include "mreportdocument_p.h"
#include "mreportparameter.h"

#include <QFile>


MReportDocument::MReportDocument( const QString &fileName, QObject *parent ) :
  QObject(parent)
{
  p = new MReportDocument_P( fileName, this );
}

MReportDocument::~MReportDocument()
{
  delete p;
  p = NULL;
}

MReportDocument * MReportDocument::errorDocument() const
{
  if ( p->m__LastError != tr( "none" ) ) return p->p_dptr();

  foreach ( MReportDocument *childDocument, p->m__ChildDocuments )
  {
    MReportDocument *reportDocument = childDocument->errorDocument();
    if ( reportDocument != NULL ) return reportDocument;
  }

  return NULL;
}

const QString & MReportDocument::lastError() const
{
  return p->m__LastError;
}

MReportDocument * MReportDocument::addReportDocument( const QString &alias )
{
  if ( errorDocument() != NULL || reportDocument( alias ) != NULL ) return NULL;

  MReportDocument *reportDocument = new MReportDocument(
        this, tr( "%1%2/%2.xml" ).arg( p->filePath(), alias ) );
  p->m__ChildDocuments << reportDocument;

  return reportDocument;
}

MReportDocument * MReportDocument::reportDocument( const QString &alias ) const
{
  if ( p->alias() == alias ) return p->p_dptr();

  foreach ( MReportDocument *childDocument, p->m__ChildDocuments )
  {
    MReportDocument *reportDocument = childDocument->reportDocument( alias );
    if ( reportDocument != NULL ) return reportDocument;
  }

  return NULL;
}

MReportParameter * MReportDocument::addReportParameter( const QString &name )
{
  if ( errorDocument() != NULL || reportParameter( name ) != NULL ) return NULL;

  MReportParameter * rp = new MReportParameter( name, this );
  p->m__Parameters << rp;

  return rp;
}

const QList<MReportParameter *> & MReportDocument::reportParameters() const
{
  return p->m__Parameters;
}

MReportParameter * MReportDocument::reportParameter( const QString &name ) const
{
  foreach ( MReportParameter *parameter, p->m__Parameters )
    if ( parameter->name() == name ) return parameter;

  foreach ( MReportDocument *childDocument, p->m__ChildDocuments )
  {
    MReportParameter *parameter = childDocument->reportParameter( name );
    if ( parameter != NULL ) return parameter;
  }

  return NULL;
}

MReportDocument::MReportDocument( MReportDocument *parent , const QString &fileName ) :
  QObject(parent)
{
  p = new MReportDocument_P( fileName, this );
}

