#include "wizard_adddoc.h"

#include "docsourcepage.h"
#include "createdocspage.h"
#include "clientdocspage.h"
#include "declardocspage.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>

#include <QDebug>


Wizard_AddDoc::Wizard_AddDoc( QWidget *parent ) :
  QWizard(parent),
  m__Docmanager(NULL)
{
  resize( qApp->desktop()->availableGeometry().width()*0.8,
          qApp->desktop()->availableGeometry().height()*0.8 );

  m__DocSourcePage = new DocSourcePage;
  m__CreateDocsPage = new CreateDocsPage;
  m__ClientDocsPage = new ClientDocsPage;
  m__DeclarDocsPage = new DeclarDocsPage;

  setPage( Page_DocSource, m__DocSourcePage );
  setPage( Page_CreateDocs, m__CreateDocsPage );
  setPage( Page_ClientDocs, m__ClientDocsPage );
  setPage( Page_DeclarDocs, m__DeclarDocsPage );

  setDocumentCreationMode();
}

Wizard_AddDoc::~Wizard_AddDoc()
{
  m__Docmanager = NULL;
  delete m__DocSourcePage;
  m__DocSourcePage = NULL;
  delete m__CreateDocsPage;
  m__CreateDocsPage = NULL;
  delete m__ClientDocsPage;
  m__ClientDocsPage = NULL;
  delete m__DeclarDocsPage;
  m__DeclarDocsPage = NULL;
}

void Wizard_AddDoc::setDocumentCreationMode( DocumentMode documentMode )
{
  m__CreateDocsPage->setDocumentCreationMode( documentMode );
}

void Wizard_AddDoc::setDoctypes( const QStringList &doctypes )
{
  m__CreateDocsPage->setDoctypes( doctypes );
}

void Wizard_AddDoc::setDocmanager( Docmanager *docmanager )
{
  m__Docmanager = docmanager;
}

void Wizard_AddDoc::addClient( const QVariant &id, const QString &clientInfo )
{
  m__ClientDocsPage->addClient( id, clientInfo );
}

int Wizard_AddDoc::exec()
{
  if ( m__Docmanager == NULL || m__Docmanager->declarDocuments() == NULL )
  {
    QMessageBox::warning( parentWidget(), tr( "Ошибка" ),
                          tr( "Для Мастера добавления документов не "
                              "инициализирован менеджер документов" ) );
    return QDialog::Rejected;
  }


  if ( m__Docmanager->docpathsDocuments() == NULL )
  {
    m__DocSourcePage->setClientDocsAvailable( false );
    m__DocSourcePage->setDeclarDocsAvailable( false );
  }
  else if ( m__Docmanager->clientDocuments() == NULL )
  {
    m__DocSourcePage->setClientDocsAvailable( false );

    m__DocSourcePage->setDeclarDocsAvailable( true );
  }
  else
  {
    m__DocSourcePage->setClientDocsAvailable( true );
    m__ClientDocsPage->setDocmanager( m__Docmanager );
    m__ClientDocsPage->firstStart();

    m__DocSourcePage->setDeclarDocsAvailable( true );
  }

  return QDialog::exec();
}

void Wizard_AddDoc::done( int result )
{
  if ( (QDialog::DialogCode)result == QDialog::Accepted )
  {
    if ( field( "isCreateDocs" ).toBool() )
    {
      deselectClientDocs();
      deselectDeclarDocs();

      foreach ( MFCDocumentInfo *doc, m__CreateDocsPage->createdDocs()->documents())
        m__Docmanager->declarDocuments()->addDocument( doc );
    }
    else if ( field( "isClientDocs" ).toBool() )
    {
      deleteCreatedDocs();
      deselectDeclarDocs();

    }
    else if ( field( "isDeclarDocs" ).toBool() )
    {
      deleteCreatedDocs();
      deselectClientDocs();

    }
    else return;
  }
  else
  {
    deleteCreatedDocs();
    deselectClientDocs();
    deselectDeclarDocs();
  }

  QWizard::done( result );
}

void Wizard_AddDoc::deleteCreatedDocs()
{
  while( m__CreateDocsPage->createdDocs()->rowCount() > 0 )
  {
    MFCDocumentInfo *doc = m__CreateDocsPage->createdDocs()->documents().first();
    m__CreateDocsPage->createdDocs()->removeDocument( doc );
    MFCDocumentInfo::remove( doc );
    doc = NULL;
  }
}

void Wizard_AddDoc::deselectClientDocs()
{

}

void Wizard_AddDoc::deselectDeclarDocs()
{

}
