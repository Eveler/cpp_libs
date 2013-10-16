#include "receptiondocmanager_p.h"

ReceptionDocmanager_P::ReceptionDocmanager_P( Widget_ReceptionDocmanager *parent ) :
  QObject(parent),
  m__Docmanager(NULL),
  m__RequiredDocs(NULL)
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
