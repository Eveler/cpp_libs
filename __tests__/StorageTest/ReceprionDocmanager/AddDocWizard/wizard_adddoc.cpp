#include "wizard_adddoc.h"

#include "docsourcepage.h"
#include "createdocspage.h"
#include "clientdocspage.h"
#include "declardocspage.h"

#include <QApplication>
#include <QDesktopWidget>

#include <QDebug>


Wizard_AddDoc::Wizard_AddDoc( const QStringList &doctypes,
                              Docmanager *docmanager, QWidget *parent ) :
  QWizard(parent)
{
  resize( qApp->desktop()->availableGeometry().width()*0.8,
          qApp->desktop()->availableGeometry().height()*0.8 );

  m__DocSourcePage = new DocSourcePage;
  m__CreateDocsPage = new CreateDocsPage( doctypes );
  m__ClientDocsPage = new ClientDocsPage;
  m__DeclarDocsPage = new DeclarDocsPage;

  setPage( Page_DocSource, m__DocSourcePage );
  setPage( Page_CreateDocs, m__CreateDocsPage );
  setPage( Page_ClientDocs, m__ClientDocsPage );
  setPage( Page_DeclarDocs, m__DeclarDocsPage );
}

Wizard_AddDoc::~Wizard_AddDoc()
{
  delete m__DocSourcePage;
  m__DocSourcePage = NULL;
  delete m__CreateDocsPage;
  m__CreateDocsPage = NULL;
  delete m__ClientDocsPage;
  m__ClientDocsPage = NULL;
  delete m__DeclarDocsPage;
  m__DeclarDocsPage = NULL;
}

void Wizard_AddDoc::done( int result )
{
  qDebug() << __func__;
  QWizard::done( result );
}
