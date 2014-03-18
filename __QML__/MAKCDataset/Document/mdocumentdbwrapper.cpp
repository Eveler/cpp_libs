#include "mdocumentdbwrapper.h"

#include "mhumandbwrapper.h"

#include <QReadWriteLock>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTime>


/*
 * Begin C++ - QML class definition: *[ MDocument ]*
*/
MDocument::MDocument( QQuickItem *parent ) :
  QQuickItem( parent )
{

}

MDocument::~MDocument()
{
//  qDebug() << __func__ << this;
}

QVariant MDocument::identifier() const
{
  return m__Identifier;
}

void MDocument::setIdentifier( QVariant identifier )
{
  m__Identifier = identifier;
  emit identifierChanged();
}

const QString & MDocument::name() const
{
  return m__Name;
}

void MDocument::setName( const QString &name )
{
  m__Name = name;
  emit nameChanged();
}

const QString & MDocument::series() const
{
  return m__Series;
}

void MDocument::setSeries( const QString &series )
{
  m__Series = series;
  emit seriesChanged();
}

const QString & MDocument::number() const
{
  return m__Number;
}

void MDocument::setNumber( const QString &number )
{
  m__Number = number;
  emit numberChanged();
}

QDate MDocument::created() const
{
  return m__Created;
}

void MDocument::setCreated( QDate created )
{
  m__Created = created;
  emit createdChanged();
}

QDate MDocument::expires() const
{
  return m__Expires;
}

void MDocument::setExpires( QDate expires )
{
  m__Expires = expires;
  emit expiresChanged();
}

QUrl MDocument::source() const
{
  return m__Source;
}

void MDocument::setSource( QUrl source )
{
  m__Source = source;
  emit sourceChanged();
}

const QObjectList & MDocument::externalLinks() const
{
  return m__ExternalLinks;
}

void MDocument::addExternalLink( QObject *externalLink )
{
  if ( !m__ExternalLinks.contains( externalLink ) ) m__ExternalLinks << externalLink;
}

void MDocument::removeExternalLink( QObject *externalLink )
{
  m__ExternalLinks.removeOne( externalLink );
}
/*
 * End class definition: *[ MDocument ]*
*/


/*
 * Begin C++ class definition: *[ MDocumentDBWrapper ]*
*/
MDocumentDBWrapper::MDocumentDBWrapper( MAbstractDataSource * parent ) :
  MAbstractDBWrapper(parent)
{
}

bool MDocumentDBWrapper::find( const QString &filter )
{
  Q_UNUSED(filter)
  return true;
}

bool MDocumentDBWrapper::find( MHuman *human )
{
//  qDebug() << metaObject()->className() << __func__ << __LINE__;
  if ( isRunning() ) return false;

  setObjective( (int)HumanDocuments, QVariant::fromValue( human ) );

  start();
  return true;
}

QObject * MDocumentDBWrapper::searched()
{
  QObject *result = NULL;

  locker()->lockForRead();
  if ( !m__Searched.isEmpty() ) result = m__Searched.takeFirst();
  locker()->unlock();

  return result;
}

void MDocumentDBWrapper::job( int objectiveType, const QVariant &objectiveValue )
{
//  qDebug() << metaObject()->className() << __func__ << __LINE__;
  if ( objectiveType == (int)HumanDocuments ) searching( objectiveValue.value<MHuman *>() );
  else MAbstractDBWrapper::job( objectiveType, objectiveValue );
}

bool MDocumentDBWrapper::searching( const QString &queryText )
{
  Q_UNUSED(queryText)
  return true;
}

bool MDocumentDBWrapper::searching( MHuman *human )
{
  human->documents()->setSource( (ObjectListPrivate *)this );

  QSqlDatabase database = QSqlDatabase::database( connectionName(), false );
  if ( !database.open() )
  {
    qDebug() << __func__ << __LINE__ << database.lastError().text();
    return false;
  }

  QString currentQuery = tr( "SELECT id FROM clients WHERE isorg=0 AND clid=%1" ).arg( human->identifier().toInt() );
  QSqlQuery qry( database );
  if ( !qry.exec( currentQuery ) )
  {
    qDebug() << __func__ << __LINE__ << qry.lastError().text();
    return false;
  }
  if ( !qry.next() ) return true;

  currentQuery = tr( "SELECT docs.id, docs.doctype_id, docs.docname, docs.docseries, docs.docdate, docs.expires, docs.docagency_id, docs.url"
                     " FROM client_documents cdocs, documents docs WHERE cdocs.documents_id=docs.id AND cdocs.clients_id=%1"
                     " GROUP BY docs.id, docs.doctype_id, docs.docname, docs.docseries, docs.docdate, docs.expires, docs.docagency_id, docs.url"
                     " ORDER BY docs.id" ).arg( qry.record().value( 0 ).toInt() );
  qry.clear();
  if ( !qry.exec( currentQuery ) )
  {
    qDebug() << __func__ << __LINE__ << qry.lastError().text();
    return false;
  }

  locker()->lockForWrite();
  int lastFounded = -1;
  int counted = 0;
  while ( qry.next() )
  {
    counted++;
    int identifier = qry.record().value( "id" ).toInt();
    MDocument *document = m__ExistDocuments.value( identifier, NULL );

    int docsCount = pCount( human->documents() );
    int index = lastFounded+1;
    for ( ; index < docsCount; index++ )
    {
      MDocument *oldDocument = qobject_cast<MDocument *>( pObject( human->documents(), index ) );

      if ( identifier > oldDocument->identifier().toInt() )
      {
        qDebug() << metaObject()->className() << __func__ << __LINE__ << "\tудалить объект с ID" << identifier;
        pTake( human->documents(), index );
        oldDocument->removeExternalLink( human->documents() );
        index--;
        docsCount--;

        if ( oldDocument->externalLinks().isEmpty() )
          connect( this, SIGNAL(finished()), oldDocument, SLOT(deleteLater()) );
      }
      else if ( identifier == oldDocument->identifier().toInt() )
      {
        qDebug() << metaObject()->className() << __func__ << __LINE__ << "\tзапомнить объект с ID" << identifier;
        lastFounded = index;
        break;
      }
    }

    if ( document == NULL )
    {
//      qDebug() << metaObject()->className() << __func__ << __LINE__ << "\tобъект с ID" << identifier;
      document = new MDocument;
      document->moveToThread( parent()->thread() );
      m__ExistDocuments[identifier] = document;
      lastFounded++;
      pInsert( human->documents(), document, lastFounded );
      document->addExternalLink( human->documents() );
    }
    document->setIdentifier( identifier );
    document->setName( qry.record().value( "docname" ).toString() );
    document->setSeries( qry.record().value( "docseries" ).toString() );
    document->setNumber( qry.record().value( "docnum" ).toString() );
    document->setCreated( qry.record().value( "docdate" ).toDate() );
    document->setExpires( qry.record().value( "expires" ).toDate() );
    document->setSource( QUrl( qry.record().value( "url" ).toString() ) );
  }
  qry.clear();
//  qDebug() << metaObject()->className() << __func__ << __LINE__ << pCount( human->documents() ) << counted;
  m__Searched << human->documents();
  locker()->unlock();

  return true;
}

bool MDocumentDBWrapper::initiating()
{
  return true;
}

bool MDocumentDBWrapper::saving( QObject *object )
{
  return true;
}
/*
 * End class definition: *[ MDocumentDBWrapper ]*
*/
