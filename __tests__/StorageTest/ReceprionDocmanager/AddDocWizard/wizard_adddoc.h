#ifndef WIZARD_ADDDOC_H
#define WIZARD_ADDDOC_H

#include <QWizard>

#include "docmanager.h"


class DocSourcePage;
class CreateDocsPage;
class ClientDocsPage;
class DeclarDocsPage;

class Wizard_AddDoc : public QWizard
{
    Q_OBJECT


  public:
    enum {Page_DocSource = 0, Page_CreateDocs, Page_ClientDocs, Page_DeclarDocs};
    explicit Wizard_AddDoc( const QStringList &doctypes,
                            Docmanager *docmanager,
                            QWidget *parent = NULL );
    ~Wizard_AddDoc();


  signals:


  public slots:


  protected:
    virtual void done( int result );


  private:
    DocSourcePage *m__DocSourcePage;
    CreateDocsPage *m__CreateDocsPage;
    ClientDocsPage *m__ClientDocsPage;
    DeclarDocsPage *m__DeclarDocsPage;
};

#endif // WIZARD_ADDDOC_H
