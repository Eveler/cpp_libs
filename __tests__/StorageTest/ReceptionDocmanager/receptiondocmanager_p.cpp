#include "receptiondocmanager_p.h"

#include "widget_receptiondocmanager.h"
#include "edvprocess.h"
#include "dialog_docdetails.h"

#include <QMessageBox>


ReceptionDocmanager_P::ReceptionDocmanager_P( Widget_ReceptionDocmanager *parent ) :
  QObject(parent),
  m__Docmanager(NULL),
  m__RequiredDocs(NULL),
  reqSBVal(-1)
{
  m__BoolDelegate = new BoolDelegate( this );
  m__BoolDelegate->setIcon( true, QIcon( ":/Icons/check.png" ) );
  m__BoolDelegate->setText( true );
  m__BoolDelegate->setText( false );

  m__ButtonDelegate = new ToolButtonDelegate( this );
  m__ButtonDelegate->setIcon( tr( "Образец" ), QIcon( ":/Icons/question.png" ) );
}

ReceptionDocmanager_P::~ReceptionDocmanager_P()
{
  delete m__BoolDelegate;
  m__BoolDelegate = NULL;

  delete m__ButtonDelegate;
  m__ButtonDelegate = NULL;
}

Widget_ReceptionDocmanager * ReceptionDocmanager_P::p_dptr() const
{
  return qobject_cast<Widget_ReceptionDocmanager *>( parent() );
}

DocumentsModel * ReceptionDocmanager_P::findDocuments( const QString &doctype ) const
{
  if ( m__Docmanager == NULL ) return NULL;

  DocumentsModel *result = new DocumentsModel;

  foreach ( QVariant id, m__Clients.values() )
  {
    DocumentsModel *dm = m__Docmanager->clientDocuments( id );
    foreach ( MFCDocumentInfo *doc, dm->documents() )
      if ( doc->type() == doctype ) result->addDocument( doc );
  }

  return result;
}

DocumentsModel * ReceptionDocmanager_P::findClientDocuments(
    QVariant clientId, const QStringList &doctypes ) const
{
  if ( m__Docmanager == NULL ) return NULL;

  DocumentsModel *result = new DocumentsModel;

  DocumentsModel *dm = m__Docmanager->clientDocuments( clientId );
  foreach ( MFCDocumentInfo *doc, dm->documents() )
    if ( doctypes.contains( doc->type() ) ) result->addDocument( doc );

  return result;
}

bool ReceptionDocmanager_P::newDocument(
    const QString &doctype, const QString &num, QDate date, QDate expires )
{
  EDVProcess elDocProc;
  MFCDocumentInfo *doc = elDocProc.writeDocument(
                           QStringList() << doctype, QString(), QString(),
                           num, date, expires );
  if ( doc == NULL )
  {
    if ( !elDocProc.lastError().isEmpty() )
      QMessageBox::warning( p_dptr(), tr( "Ошибка" ), elDocProc.lastError() );
    return false;
  }
  else
  {
    Dialog_DocDetails dDocDetails;
    if( dDocDetails.exec( doc, Dialog_DocDetails::WritePagesnum ) == QDialog::Rejected )
      return false;

    m__Docmanager->unsetCurrentClient();
    m__Docmanager->newDocument( doc );
  }
  return true;
}

void ReceptionDocmanager_P::recalcNewDocuments( DocumentsModel *dm )
{
  m__RequiredDocs->reset();

  if ( dm == NULL ) return;

  foreach ( MFCDocumentInfo *doc, dm->documents() )
    m__RequiredDocs->useDocType( doc->type() );
}
