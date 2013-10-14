#include "clientdocspage.h"
#include "ui_clientdocspage.h"

#include "wizard_adddoc.h"

#include <QTextLayout>

#include <QDebug>


ClientDocsPage::ClientDocsPage( QWidget *parent ) :
  QWizardPage(parent),
  ui(new Ui::ClientDocsPage),
  m__Docmanager(NULL),
  m__CanLoadClientDocs(false)
{
  ui->setupUi(this);

  setTitle( tr( "Добавление документов из ранее принятых документов у заявителя" ) );

  setFinalPage( true );
}

ClientDocsPage::~ClientDocsPage()
{
  delete ui;
}

int ClientDocsPage::nextId() const
{
  return -1;
}

bool ClientDocsPage::isComplete() const
{
  return m__SelectedDocs.count() > 0;
}

void ClientDocsPage::firstStart()
{
  setCanLoadClientDocs( true );
  ui->cBox_Client->setCurrentIndex( -1 );
  qApp->processEvents();
  if ( ui->cBox_Client->count() == 1 )
    ui->cBox_Client->setCurrentIndex( 0 );
}

void ClientDocsPage::setDocmanager( Docmanager *docmanager )
{
  m__Docmanager = docmanager;
}

void ClientDocsPage::addClient( const QVariant &id, const QString &clientInfo )
{
  if ( m__ClientIds.contains( id ) ) return;
  setCanLoadClientDocs( false );
  m__ClientIds << id;

  ui->cBox_Client->addItem( clientInfo, id );
  ui->cBox_Client->setCurrentIndex( -1 );
}

void ClientDocsPage::setCanLoadClientDocs( bool can )
{
  m__CanLoadClientDocs = can;
}

void ClientDocsPage::on_cBox_Client_currentIndexChanged(int index)
{
  if ( index < 0 || !m__CanLoadClientDocs || m__Docmanager == NULL ) return;

  ui->cBox_Client->setMinimumHeight(
        ui->cBox_Client->view()->visualRect(
          ui->cBox_Client->view()->model()->index( index, 0 ) ).height()+5 );

  m__Docmanager->setClientCurrent( ui->cBox_Client->itemData( index ) );


}
