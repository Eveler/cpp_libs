#include "mreportdocument.h"

#include "mreportdocument_p.h"
#include "mreportparameter.h"
#include "mreportloader.h"

#include <QFile>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>


MReportDocument::MReportDocument( const QString &fileName, QObject *parent ) :
  QObject(parent)
{
  p = new MReportDocument_P( fileName, this );

  if ( p->m__LastError.isEmpty() )
  {
    QString err_text = MReportLoader::load( this );
    if ( !err_text.isEmpty() )
      p->m__LastError = err_text;
  }
}

MReportDocument::~MReportDocument()
{
  delete p;
  p = NULL;
}

const QString & MReportDocument::fileName() const
{
  return p->m__FileName;
}

void MReportDocument::setBody( const QString &body )
{
  p->m__Body = body;
  QFile f( tr( "%1/main.html" ).arg( p->filePath() ) );
  if ( f.exists() )
    if ( !f.remove() ) return;
  f.open( QFile::WriteOnly | QFile::Text );
  f.write( body.toLocal8Bit() );
  f.close();
}

MReportDocument * MReportDocument::errorDocument() const
{
  if ( !p->m__LastError.isEmpty() ) return p->p_dptr();

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

MReportDocument * MReportDocument::mainDocument() const
{
  if ( p->m__ParentDocument == NULL ) return p->p_dptr();
  else return p->m__ParentDocument->mainDocument();
}

MReportDocument * MReportDocument::addReportDocument( const QString &alias )
{
  if ( p->m__FileName.isEmpty() || reportDocument( alias ) != NULL ) return NULL;

  MReportDocument *reportDocument = new MReportDocument(
        this, tr( "%1/%2/%2.mrc" ).arg( p->filePath(), alias ) );
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

MReportDocument * MReportDocument::parentDocument() const
{
  return p->m__ParentDocument;
}

MReportSource * MReportDocument::addReportSource( const QString &name )
{
  foreach ( MReportSource *source, p->m__Sources )
    if ( source->name() == name ) return source;

  MReportSource *source = new MReportSource( name, this );
  p->m__Sources << source;

  return source;
}

const MReportSourceList & MReportDocument::reportSources() const
{
  return p->m__Sources;
}

MReportParameter * MReportDocument::addReportParameter( const QString &name )
{
  if ( name.contains( " " ) || p->m__FileName.isEmpty() ||
       reportParameter( name ) != NULL )
    return NULL;

  MReportParameter * rp = new MReportParameter( name, this );
  p->m__Parameters << rp;

  return rp;
}

const MReportParameterList & MReportDocument::reportParameters() const
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

MReportKey * MReportDocument::addReportKey( const QString &name )
{
  if ( name.contains( " " ) || p->m__FileName.isEmpty() ||
       reportKey( name ) != NULL )
    return NULL;

  MReportKey * rk = new MReportKey( name, this );
  p->m__Keys << rk;

  return rk;
}

const MReportKeyList & MReportDocument::reportKeys() const
{
  return p->m__Keys;
}

MReportKey * MReportDocument::reportKey( const QString &name ) const
{
  foreach ( MReportKey *key, p->m__Keys )
    if ( key->name() == name ) return key;

  foreach ( MReportDocument *childDocument, p->m__ChildDocuments )
  {
    MReportKey *key = childDocument->reportKey( name );
    if ( key != NULL ) return key;
  }

  return NULL;
}

QVariant MReportDocument::sqlResult( const QString &query ) const
{
//  QSqlDatabase

  return QVariant();
}

QString MReportDocument::exec()
{
  return QString();
}

MReportDocument::MReportDocument( MReportDocument *parent , const QString &fileName ) :
  QObject(parent)
{
  p = new MReportDocument_P( fileName, this );

  if ( p->m__LastError.isEmpty() )
  {
    QString err_text = MReportLoader::load( this );
    if ( !err_text.isEmpty() )
      p->m__LastError = err_text;
  }
}

