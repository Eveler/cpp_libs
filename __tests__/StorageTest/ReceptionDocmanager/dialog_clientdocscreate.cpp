#include "dialog_clientdocscreate.h"
#include "ui_dialog_clientdocscreate.h"

#include <QCommandLinkButton>


Dialog_ClientDocsCreate::Dialog_ClientDocsCreate(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog_ClientDocsCreate)
{
  ui->setupUi(this);
}

Dialog_ClientDocsCreate::~Dialog_ClientDocsCreate()
{
  delete ui;
}

void Dialog_ClientDocsCreate::setDocmanager( Docmanager *docmanager )
{
  m__Docmanager = docmanager;
}

void Dialog_ClientDocsCreate::setDoctypes( const QStringList &doctypes )
{
  m__Doctypes = doctypes;
}

void Dialog_ClientDocsCreate::addClient( QVariant id, const QStringList &clientInfo )
{
  if ( !id.isValid() || clientInfo.isEmpty() ) return;

  QCommandLinkButton *clientButton = NULL;
  if ( m__Clients.values().contains( id ) )
    clientButton = m__Clients.key( id );
  else
  {
    clientButton = new QCommandLinkButton( clientInfo.first(), QString() );

    ui->vL_Clients->addWidget( clientButton );
  }

  QString description;
  for ( int cIIdx = 1; cIIdx < clientInfo.count(); cIIdx++ )
    description += " "+clientInfo[cIIdx];
  clientButton->setDescription( description );
}
