#include "mdocumentdbwrapper.h"

#include "makcdataset.h"

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
  QQuickItem( parent ),
  m__Type(NULL),
  m__Revoker(NULL),
  m__ExternalLinksCount(0)
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

MDoctype * MDocument::type() const
{
  return m__Type;
}

void MDocument::setType( MDoctype *doctype )
{
  if ( m__Type != NULL )
    m__Type->decrementExternalLinks();
  m__Type = doctype;
  if ( m__Type != NULL )
    m__Type->incrementExternalLinks();
  emit typeChanged();
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

MUser * MDocument::revoker() const
{
  return m__Revoker;
}

void MDocument::setRevoker( MUser *revoker )
{
  if ( m__Revoker != NULL )
    m__Revoker->decrementExternalLinks();
  m__Revoker = revoker;
  if ( m__Revoker != NULL )
    m__Revoker->incrementExternalLinks();
  emit revokerChanged();
}

QDateTime MDocument::revoked() const
{
  return m__Revoked;
}

void MDocument::setRevoked( QDateTime revoked )
{
  m__Revoked = revoked;
  emit revokedChanged();
}

int MDocument::externalLinksCount() const
{
  return m__ExternalLinksCount;
}

int MDocument::incrementExternalLinks()
{
  return m__ExternalLinksCount++;
}

int MDocument::decrementExternalLinks()
{
  if ( m__ExternalLinksCount > 0 ) m__ExternalLinksCount--;

  return m__ExternalLinksCount;
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

MDocumentDBWrapper::~MDocumentDBWrapper()
{
  m__Searched.clear();
  m__ExistDocuments.clear();
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

bool MDocumentDBWrapper::find( MOrganization *organization )
{
//  qDebug() << metaObject()->className() << __func__ << __LINE__;
  if ( isRunning() ) return false;

  setObjective( (int)OrganizationDocuments, QVariant::fromValue( organization ) );

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

void MDocumentDBWrapper::releaseHumanDocuments( MHuman *human )
{
  locker()->lockForWrite();
  int docsCount = pCount( human->documents() );
  while ( docsCount > 0 )
  {
    MDocument *document = qobject_cast<MDocument *>( pTake( human->documents(), 0 ) );
    document->decrementExternalLinks();

    if ( document->externalLinksCount() == 0 )
    {
      m__ExistDocuments.remove( document->identifier().toInt() );
      connect( human, SIGNAL(destroyed()), document, SLOT(deleteLater()) );
    }

    docsCount--;
  }
  locker()->unlock();
}

void MDocumentDBWrapper::releaseOrganizationDocuments( MOrganization *organization )
{
  locker()->lockForWrite();
  int docsCount = pCount( organization->documents() );
  while ( docsCount > 0 )
  {
    MDocument *document = qobject_cast<MDocument *>( pTake( organization->documents(), 0 ) );
    document->decrementExternalLinks();

    if ( document->externalLinksCount() == 0 )
    {
      m__ExistDocuments.remove( document->identifier().toInt() );
      connect( organization, SIGNAL(destroyed()), document, SLOT(deleteLater()) );
    }

    docsCount--;
  }
  locker()->unlock();
}

void MDocumentDBWrapper::job( int objectiveType, const QVariant &objectiveValue )
{
//  qDebug() << metaObject()->className() << __func__ << __LINE__;
  if ( objectiveType == (int)HumanDocuments ) searching( objectiveValue.value<MHuman *>() );
  if ( objectiveType == (int)OrganizationDocuments ) searching( objectiveValue.value<MOrganization *>() );
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
  QSqlQuery *qry = MDatabase::instance()->getQuery( currentQuery, connectionName() );
  if ( qry->lastError().isValid() )
  {
    qDebug() << metaObject()->className() << __func__ << __LINE__ << qry->lastError().text();
    return false;
  }
  if ( !qry->next() ) return true;

  currentQuery = tr( "SELECT docs.id, docs.doctype_id, docs.docname, docs.docseries, docs.docdate, docs.expires,"
                     "   docs.docagency_id, docs.url, docs.revoke_date, docs.revoke_user_id, docs.revoke_comment"
                     " FROM client_documents cdocs, documents docs WHERE cdocs.documents_id=docs.id AND cdocs.clients_id=%1"
                     " GROUP BY docs.id, docs.doctype_id, docs.docname, docs.docseries, docs.docdate, docs.expires,"
                     "   docs.docagency_id, docs.url, docs.revoke_date, docs.revoke_user_id, docs.revoke_comment"
                     " ORDER BY docs.id" ).arg( qry->record().value( 0 ).toInt() );
  qry->clear();
  delete qry;
  qry = NULL;

  qry = MDatabase::instance()->getQuery( currentQuery, connectionName() );
  if ( qry->lastError().isValid() )
  {
    qDebug() << metaObject()->className() << __func__ << __LINE__ << qry->lastError().text();
    return false;
  }

  locker()->lockForWrite();
  int lastFounded = -1;
  int counted = 0;
  while ( qry->next() )
  {
    counted++;

    int identifier = qry->record().value( "id" ).toInt();
    MDocument *document = m__ExistDocuments.value( identifier, NULL );

    int docsCount = pCount( human->documents() );
    int index = lastFounded+1;
    for ( ; index < docsCount; index++ )
    {
      MDocument *oldDocument = qobject_cast<MDocument *>( pObject( human->documents(), index ) );

      if ( identifier > oldDocument->identifier().toInt() )
      {
//        qDebug() << metaObject()->className() << __func__ << __LINE__ << "\tудалить объект с ID" << identifier;
        pTake( human->documents(), index );
        oldDocument->decrementExternalLinks();
        index--;
        docsCount--;

        if ( oldDocument->externalLinksCount() == 0 )
        {
          m__ExistDocuments.remove( oldDocument->identifier().toInt() );
          connect( this, SIGNAL(aboutToReleaseOldResources()), oldDocument, SLOT(deleteLater()) );
        }
      }
      else if ( identifier == oldDocument->identifier().toInt() )
      {
//        qDebug() << metaObject()->className() << __func__ << __LINE__ << "\tзапомнить объект с ID" << identifier;
        lastFounded = index;
        break;
      }
    }

    MDoctypeDBWrapper *doctypeDBWrapper = qobject_cast<MDoctypeDBWrapper *>( MAKCDataset::MAKC_DoctypeDataSource()->dbWrapper() );
    MUserDBWrapper *userDBWrapper = qobject_cast<MUserDBWrapper *>( MAKCDataset::MAKC_UserDataSource()->dbWrapper() );

    if ( document == NULL )
    {
//      qDebug() << metaObject()->className() << __func__ << __LINE__ << "\tобъект с ID" << identifier;
      document = new MDocument;
      document->moveToThread( parent()->thread() );
      m__ExistDocuments[identifier] = document;
      lastFounded++;
      pInsert( human->documents(), document, lastFounded );
      document->incrementExternalLinks();
    }
    document->setIdentifier( identifier );
    document->setType( doctypeDBWrapper->doctype( qry->record().value( "doctype_id" ) ) );
    document->setName( qry->record().value( "docname" ).toString() );
    document->setSeries( qry->record().value( "docseries" ).toString() );
    document->setNumber( qry->record().value( "docnum" ).toString() );
    document->setCreated( qry->record().value( "docdate" ).toDate() );
    document->setExpires( qry->record().value( "expires" ).toDate() );
    document->setSource( QUrl( qry->record().value( "url" ).toString() ) );
    document->setRevoker( userDBWrapper->user( qry->record().value( "revoke_user_id" ) ) );
    document->setRevoked( qry->record().value( "revoke_date" ).toDateTime() );
  }
  qry->clear();
  delete qry;
  qry = NULL;

  if ( counted == 0 )
  {
    while ( pCount( human->documents() ) > 0 )
    {
      MDocument *oldDocument = qobject_cast<MDocument *>( pTake( human->documents(), 0 ) );

      oldDocument->decrementExternalLinks();

      if ( oldDocument->externalLinksCount() == 0 )
      {
        m__ExistDocuments.remove( oldDocument->identifier().toInt() );
        connect( this, SIGNAL(aboutToReleaseOldResources()), oldDocument, SLOT(deleteLater()) );
      }
    }
  }
//  qDebug() << metaObject()->className() << __func__ << __LINE__ << pCount( human->documents() ) << counted;
  m__Searched << human->documents();
  locker()->unlock();

  return true;
}

bool MDocumentDBWrapper::searching( MOrganization *organization )
{
  organization->documents()->setSource( (ObjectListPrivate *)this );

  QSqlDatabase database = QSqlDatabase::database( connectionName(), false );
  if ( !database.open() )
  {
    qDebug() << __func__ << __LINE__ << database.lastError().text();
    return false;
  }

  QString currentQuery = tr( "SELECT id FROM clients WHERE isorg=1 AND clid=%1" ).arg( organization->identifier().toInt() );
  QSqlQuery *qry = MDatabase::instance()->getQuery( currentQuery, connectionName() );
  if ( qry->lastError().isValid() )
  {
    qDebug() << metaObject()->className() << __func__ << __LINE__ << qry->lastError().text();
    return false;
  }
  if ( !qry->next() ) return true;

  currentQuery = tr( "SELECT docs.id, docs.doctype_id, docs.docname, docs.docseries, docs.docdate, docs.expires,"
                     "   docs.docagency_id, docs.url, docs.revoke_date, docs.revoke_user_id, docs.revoke_comment"
                     " FROM client_documents cdocs, documents docs WHERE cdocs.documents_id=docs.id AND cdocs.clients_id=%1"
                     " GROUP BY docs.id, docs.doctype_id, docs.docname, docs.docseries, docs.docdate, docs.expires,"
                     "   docs.docagency_id, docs.url, docs.revoke_date, docs.revoke_user_id, docs.revoke_comment"
                     " ORDER BY docs.id" ).arg( qry->record().value( 0 ).toInt() );
  qry->clear();
  delete qry;
  qry = NULL;

  qry = MDatabase::instance()->getQuery( currentQuery, connectionName() );
  if ( qry->lastError().isValid() )
  {
    qDebug() << metaObject()->className() << __func__ << __LINE__ << qry->lastError().text();
    return false;
  }

  locker()->lockForWrite();
  int lastFounded = -1;
  int counted = 0;
  while ( qry->next() )
  {
    counted++;

    int identifier = qry->record().value( "id" ).toInt();
    MDocument *document = m__ExistDocuments.value( identifier, NULL );

    int docsCount = pCount( organization->documents() );
    int index = lastFounded+1;
    for ( ; index < docsCount; index++ )
    {
      MDocument *oldDocument = qobject_cast<MDocument *>( pObject( organization->documents(), index ) );

      if ( identifier > oldDocument->identifier().toInt() )
      {
//        qDebug() << metaObject()->className() << __func__ << __LINE__ << "\tудалить объект с ID" << identifier;
        pTake( organization->documents(), index );
        oldDocument->decrementExternalLinks();
        index--;
        docsCount--;

        if ( oldDocument->externalLinksCount() == 0 )
        {
          m__ExistDocuments.remove( oldDocument->identifier().toInt() );
          connect( this, SIGNAL(aboutToReleaseOldResources()), oldDocument, SLOT(deleteLater()) );
        }
      }
      else if ( identifier == oldDocument->identifier().toInt() )
      {
//        qDebug() << metaObject()->className() << __func__ << __LINE__ << "\tзапомнить объект с ID" << identifier;
        lastFounded = index;
        break;
      }
    }

    MDoctypeDBWrapper *doctypeDBWrapper = qobject_cast<MDoctypeDBWrapper *>( MAKCDataset::MAKC_DoctypeDataSource()->dbWrapper() );
    MUserDBWrapper *userDBWrapper = qobject_cast<MUserDBWrapper *>( MAKCDataset::MAKC_UserDataSource()->dbWrapper() );

    if ( document == NULL )
    {
//      qDebug() << metaObject()->className() << __func__ << __LINE__ << "\tобъект с ID" << identifier;
      document = new MDocument;
      document->moveToThread( parent()->thread() );
      m__ExistDocuments[identifier] = document;
      lastFounded++;
      pInsert( organization->documents(), document, lastFounded );
      document->incrementExternalLinks();
    }
    document->setIdentifier( identifier );
    document->setType( doctypeDBWrapper->doctype( qry->record().value( "doctype_id" ) ) );
    document->setName( qry->record().value( "docname" ).toString() );
    document->setSeries( qry->record().value( "docseries" ).toString() );
    document->setNumber( qry->record().value( "docnum" ).toString() );
    document->setCreated( qry->record().value( "docdate" ).toDate() );
    document->setExpires( qry->record().value( "expires" ).toDate() );
    document->setSource( QUrl( qry->record().value( "url" ).toString() ) );
    document->setRevoker( userDBWrapper->user( qry->record().value( "revoke_user_id" ) ) );
    document->setRevoked( qry->record().value( "revoke_date" ).toDateTime() );
  }
  qry->clear();
  delete qry;
  qry = NULL;

  if ( counted == 0 )
  {
    while ( pCount( organization->documents() ) > 0 )
    {
      MDocument *oldDocument = qobject_cast<MDocument *>( pTake( organization->documents(), 0 ) );

      oldDocument->decrementExternalLinks();

      if ( oldDocument->externalLinksCount() == 0 )
      {
        m__ExistDocuments.remove( oldDocument->identifier().toInt() );
        connect( this, SIGNAL(aboutToReleaseOldResources()), oldDocument, SLOT(deleteLater()) );
      }
    }
  }
//  qDebug() << metaObject()->className() << __func__ << __LINE__ << pCount( human->documents() ) << counted;
  m__Searched << organization->documents();
  locker()->unlock();

  return true;
}

bool MDocumentDBWrapper::initiating()
{
  return true;
}

bool MDocumentDBWrapper::saving( QObject *object )
{
  QSqlDatabase database = QSqlDatabase::database( connectionName(), false );
  if ( !database.open() )
  {
    qDebug() << __func__ << __LINE__ << database.lastError().text();

    return false;
  }

  locker()->lockForWrite();

  MDocument *document = qobject_cast<MDocument *>( object );
  if ( document == NULL )
  {
    qDebug() << __func__ << __LINE__ << "Document object is NULL";
    locker()->unlock();

    return false;
  }
  else if ( document->type() == NULL )
  {
    qDebug() << __func__ << __LINE__ << "Document type is NULL";
    locker()->unlock();

    return false;
  }
  else if ( document->created().isNull() )
  {
    qDebug() << __func__ << __LINE__ << "Document date is NULL";
    locker()->unlock();

    return false;
  }

  QString identifier = document->identifier().toString();
  QString doctype = document->type()->identifier().toString();
  QString name = document->name(); /*===*/ name = ( name.isNull() ? "NULL" : "'"+name.replace( "'", "''" )+"'" );
  QString series = document->series(); /*===*/ series = ( series.isNull() ? "''" : "'"+series.replace( "'", "''" )+"'" );
  QString number = document->number(); /*===*/ number = ( number.isNull() ? "''" : "'"+number.replace( "'", "''" )+"'" );
  QString created = "'"+document->created().toString( "dd.MM.yyyy" )+"'";
  QString expires = ( document->expires().isNull() ? "NULL" : "'"+document->expires().toString( "dd.MM.yyyy" )+"'" );
  QString source = document->source().toString(); /*===*/ source = ( source.isNull() ? "NULL" : "'"+source.replace( "'", "''" )+"'" );
  QString revoker = ( document->revoker() == NULL ? "NULL" : document->revoker()->identifier().toString() );
  QString revoked = ( document->revoked().isNull() ? "NULL" : "'"+document->revoked().toString( "dd.MM.yyyy hh:mm:ss" )+"'" );

  QString currentQuery = tr( "SELECT EXISTS ((SELECT id FROM documents WHERE id=%1))" ).arg( identifier );
  QSqlQuery qry( database );
  if ( !qry.exec( currentQuery ) || !qry.next() )
  {
    qDebug() << __func__ << __LINE__ << qry.lastError().text() << "\n" << currentQuery;
    return false;
  }
  bool updating = qry.value( 0 ).toBool();
  qry.clear();
  if ( updating )
    currentQuery = tr( "UPDATE documents SET doctype_id=$doctype$, docname=$name$, docseries=$series$, docnum=$number$, docdate=$created$, expires=$expires$,"
                       " modified=now(), url=$source$, revoke_user_id=$revoker$, revoke_date=$revoked$ WHERE id=$identifier$" );
  else
    currentQuery = tr( "INSERT INTO documents (doctype_id, docname, docseries, docnum, docdate, expires, url, revoke_user_id, revoke_date, id)"
                       " VALUES ($doctype$, $name$, $series$, $number$, $created$, $expires$, $source$, $revoker$, $revoked$, $identifier$)" );
  currentQuery = currentQuery.replace( "$doctype$", doctype );
  currentQuery = currentQuery.replace( "$name$", name );
  currentQuery = currentQuery.replace( "$series$", series );
  currentQuery = currentQuery.replace( "$number$", number );
  currentQuery = currentQuery.replace( "$created$", created );
  currentQuery = currentQuery.replace( "$expires$", expires );
  currentQuery = currentQuery.replace( "$source$", source );
  currentQuery = currentQuery.replace( "$revoker$", revoker );
  currentQuery = currentQuery.replace( "$revoked$", revoked );
  currentQuery = currentQuery.replace( "$identifier$", identifier );
  if ( !qry.exec( currentQuery ) )
  {
    qDebug() << __func__ << __LINE__ << qry.lastError().text() << "\n" << currentQuery;
    return false;
  }
  qry.clear();

  int index = pIndex( (int)Initiated, document );
  if ( index != -1 ) pTake( (int)Initiated, index );
  locker()->unlock();

  return true;
}
/*
 * End class definition: *[ MDocumentDBWrapper ]*
*/
