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
    enum DocumentMode { OnlyDetails = 0, WithBody, Both };
    explicit Wizard_AddDoc( QWidget *parent = NULL );
    ~Wizard_AddDoc();

    void setDocumentCreationMode( DocumentMode documentMode = Both );
    void setDoctypes( const QStringList &doctypes );
    void setDocmanager( Docmanager *docmanager );
    void addClient( const QVariant &id, const QString &clientInfo );


  signals:


  public slots:
    virtual int exec();


  protected:
    virtual void done( int result );


  private:
    Docmanager *m__Docmanager;
    DocSourcePage *m__DocSourcePage;
    CreateDocsPage *m__CreateDocsPage;
    ClientDocsPage *m__ClientDocsPage;
    DeclarDocsPage *m__DeclarDocsPage;

    void deleteCreatedDocs();
    void deselectClientDocs();
    void deselectDeclarDocs();
};

#endif // WIZARD_ADDDOC_H
