#ifndef DIALOG_CLIENTDOCSCREATE_H
#define DIALOG_CLIENTDOCSCREATE_H

#include <QDialog>

#include "export/docmanagerwidgets_export_lib.h"
#include "docmanager.h"


namespace Ui {
  class Dialog_ClientDocsCreate;
}

class QCommandLinkButton;

class EXPORT_DOCMANAGERWIDGETS Dialog_ClientDocsCreate : public QDialog
{
    Q_OBJECT


  public:
    explicit Dialog_ClientDocsCreate(QWidget *parent = 0);
    ~Dialog_ClientDocsCreate();

    void setDocmanager( Docmanager *docmanager );
    void setDoctypes( const QStringList &doctypes );
    void addClient( QVariant id, const QString &clientInfo );
    void setOnlyClients( bool onlyClients );

    QString selectedDoctype() const;
    QVariant selectedClient() const;


  private:
    Ui::Dialog_ClientDocsCreate *ui;

    Docmanager *m__Docmanager;
    QHash<QCommandLinkButton *, QVariant> m__Clients;

    QString m__SelectedDoctype;
    QVariant m__SelectedClient;


  private slots:
    void clientAccepted();
};

#endif // DIALOG_CLIENTDOCSCREATE_H
