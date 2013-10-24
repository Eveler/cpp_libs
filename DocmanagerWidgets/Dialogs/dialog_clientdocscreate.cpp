#include "dialog_clientdocscreate.h"
#include "ui_dialog_clientdocscreate.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QCommandLinkButton>


Dialog_ClientDocsCreate::Dialog_ClientDocsCreate(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog_ClientDocsCreate)
{
  ui->setupUi(this);

  resize( qApp->desktop()->availableGeometry().width()*0.8,
          qApp->desktop()->availableGeometry().height()*0.8 );
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
  ui->cBox_Doctype->clear();
  ui->cBox_Doctype->addItems( doctypes );
}

void Dialog_ClientDocsCreate::addClient(QVariant id, const QString &clientInfo )
{
  if ( !id.isValid() || clientInfo.isEmpty() ) return;

  QCommandLinkButton *clientButton = NULL;
  if ( m__Clients.values().contains( id ) )
    clientButton = m__Clients.key( id );
  else
  {
    clientButton = new QCommandLinkButton( clientInfo, QString() );
    clientButton->setCheckable( true );
    clientButton->setAutoExclusive( true );
    clientButton->setMinimumHeight( 80 );

    ui->verticalLayout_2->insertWidget( ui->verticalLayout_2->count()-1, clientButton );
    m__Clients[clientButton] = id;
  }
}

void Dialog_ClientDocsCreate::setOnlyClients( bool onlyClients )
{
  ui->groupBox->setVisible( !onlyClients );
}

QString Dialog_ClientDocsCreate::selectedDoctype() const
{
  return m__SelectedDoctype;
}

QVariant Dialog_ClientDocsCreate::selectedClient() const
{
  return m__SelectedClient;
}

void Dialog_ClientDocsCreate::clientAccepted()
{
  if ( ui->cBox_Doctype->currentIndex() > -1 )
    m__SelectedDoctype = ui->cBox_Doctype->itemText( ui->cBox_Doctype->currentIndex() );
  else m__SelectedDoctype.clear();

  m__SelectedClient = QVariant();
  foreach ( QCommandLinkButton *clientButton, m__Clients.keys() )
    if ( clientButton->isChecked() ) m__SelectedClient = m__Clients.value( clientButton );

  accept();
}
