#include "wizard_adddoc.h"

#include "docsourcepage.h"
#include "createdocspage.h"
#include "clientdocspage.h"
#include "declardocspage.h"
#include "summarypage.h"


Wizard_AddDoc::Wizard_AddDoc( Docmanager *docmanager, QWidget *parent ) :
  QWizard(parent)
{
  setPage( Page_DocSource, new DocSourcePage );
  setPage( Page_CreateDocs, new CreateDocsPage( QStringList() ) );
  setPage( Page_ClientDocs, new ClientDocsPage );
  setPage( Page_DeclarDocs, new DeclarDocsPage );
}
