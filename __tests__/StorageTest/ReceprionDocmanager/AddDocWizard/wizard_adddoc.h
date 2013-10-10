#ifndef WIZARD_ADDDOC_H
#define WIZARD_ADDDOC_H

#include <QWizard>

#include "docmanager.h"


class Wizard_AddDoc : public QWizard
{
    Q_OBJECT


  public:
    enum {Page_DocSource = 0, Page_CreateDocs, Page_ClientDocs, Page_DeclarDocs};
    explicit Wizard_AddDoc( Docmanager *docmanager, QWidget *parent = NULL );


  signals:


  public slots:


};

#endif // WIZARD_ADDDOC_H
