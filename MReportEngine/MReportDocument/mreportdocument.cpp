#include "mreportdocument.h"

#include "mreportdocument_p.h"
#include "mreportparameter.h"
#include "mreport.h"

#include <QFile>
#include <QStringList>

#include <QDebug>


MReportDocument::~MReportDocument()
{
  delete p;
  p = NULL;
}

MReportDocument * MReportDocument::load( const QString &filePath, QString *errorStr, QObject *parent )
{
  return MReport::load( filePath, errorStr, parent );
}

MReportDocument * MReportDocument::create(
    const QString &alias, const QString &dirPath, QObject *parent )
{
  return MReport::create( alias, dirPath, parent );
}

bool MReportDocument::save( MReportDocument *reportDocument )
{
  return MReport::save( reportDocument );
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

const QString & MReportDocument::body() const
{
  return p->m__Body;
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

MReportDocument * MReportDocument::addReportDocument( const QString &alias , MReportKey *reportKey )
{
  if ( p->m__FileName.isEmpty() ||
       reportDocument( alias ) != NULL ||
       reportKey->reportDocument() != this )
    return NULL;

  MReportDocument *reportDocument = new MReportDocument(
        tr( "%1/%2/%2.mrc" ).arg( p->filePath(), alias ), this );
  p->m__ChildDocuments << reportDocument;
  p->m__DocumentKey[reportDocument] = reportKey;

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

MReportParameter * MReportDocument::repeater() const
{
  if ( reportParameters().isEmpty() ||
       reportParameters().first()->parameterType() != MReportParameter::PT_Repeater ) return NULL;

  return reportParameters().first();
}

MReportParameter * MReportDocument::parentDocumentRepeater() const
{
  MReportParameter *result = NULL;

  if ( parentDocument() == NULL ) return result;
  result = parentDocument()->repeater();
  if ( result == NULL )
    result = parentDocument()->parentDocumentRepeater();

  return result;
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

QString MReportDocument::exec()
{
  QStringList result = QStringList();
  MReportParameter *firstParameter = repeater();
  if ( firstParameter != NULL )
    firstParameter->toFront();

  p->m__BufProgress = 0.;
  p->m__Progress = 0.;
  int repCount = 1;
  if ( firstParameter != NULL ) repCount = firstParameter->count();
  p->m__Units = repCount*p->m__Keys.count();

  do
  {
    QString html = body();
    if ( firstParameter != NULL && firstParameter->hasNext() ) firstParameter->next();
    foreach ( MReportKey *key, p->m__Keys )
    {
      if ( key->keyType() != MReportKey::KT_Attachment )
      {
        html = html.replace( key->name(), key->data() );
        p->increaseProgressValue();
      }
    }
    foreach ( MReportDocument *document, p->m__ChildDocuments )
    {
      MReportKey *key = p->m__DocumentKey[document];
      html = html.replace( key->name(), document->exec() );
    }
    result << html;
  } while ( firstParameter != NULL && firstParameter->hasNext() );

  return result.join( "\n" );
}

MReportDocument::MReportDocument( const QString &fileName, QObject *parent ) :
  QObject(parent)
{
  p = new MReportDocument_P( fileName, this );
}

void MReportDocument::setLastError( const QString &lastError )
{
  p->m__LastError = lastError;
}

void MReportDocument::emitProgress()
{
  MReportDocument *reportDocument = parentDocument();
  if ( reportDocument == NULL ) emit progress( (int)p->m__Progress, 10000 );
  else reportDocument->p->increaseProgressValue( p->m__Progress );
}

