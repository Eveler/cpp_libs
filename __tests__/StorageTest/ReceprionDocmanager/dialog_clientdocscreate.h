#ifndef DIALOG_CLIENTDOCSCREATE_H
#define DIALOG_CLIENTDOCSCREATE_H

#include <QDialog>

#include "docmanager.h"


namespace Ui {
  class Dialog_ClientDocsCreate;
}

class QCommandLinkButton;

class Dialog_ClientDocsCreate : public QDialog
{
    Q_OBJECT


  public:
    explicit Dialog_ClientDocsCreate(QWidget *parent = 0);
    ~Dialog_ClientDocsCreate();

    void setDocmanager( Docmanager *docmanager );
    void setDoctypes( const QStringList &doctypes );
    void addClient( QVariant id, const QStringList &clientInfo );


  private:
    Ui::Dialog_ClientDocsCreate *ui;

    Docmanager *m__Docmanager;
    QStringList m__Doctypes;
    QHash<QCommandLinkButton *, QVariant> m__Clients;
};

#endif // DIALOG_CLIENTDOCSCREATE_H
