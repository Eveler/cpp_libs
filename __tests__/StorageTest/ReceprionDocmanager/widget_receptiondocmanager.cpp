#include "widget_receptiondocmanager.h"
#include "ui_widget_receptiondocmanager.h"

#include "receptiondocmanager_p.h"
#include "wizard_adddoc.h"


Widget_ReceptionDocmanager::Widget_ReceptionDocmanager(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Widget_ReceptionDocmanager)
{
  ui->setupUi(this);

  p = new ReceptionDocmanager_P( this );
}

Widget_ReceptionDocmanager::~Widget_ReceptionDocmanager()
{
  delete ui;
}

void Widget_ReceptionDocmanager::setDocmanager( Docmanager *docmanager )
{
  p->m__Docmanager = docmanager;
}

void Widget_ReceptionDocmanager::setDoctypes( const QStringList &doctypes )
{
  p->m__Doctypes = doctypes;
}

void Widget_ReceptionDocmanager::setDeclar( const QVariant &id )
{
  if ( p->m__Docmanager == NULL ) return;

  p->m__Docmanager->setDeclar( id );
}

void Widget_ReceptionDocmanager::addClient( const QVariant &id, const QString &clientInfo )
{
  if ( p->m__Docmanager == NULL ) return;

  p->m__Docmanager->addClient( id );
  p->m__Clients[clientInfo] = id;
}

void Widget_ReceptionDocmanager::on_tView_Required_doubleClicked(const QModelIndex &index)
{

}

void Widget_ReceptionDocmanager::on_tView_New_doubleClicked(const QModelIndex &index)
{

}

void Widget_ReceptionDocmanager::on_tBt_Add_clicked()
{
  Wizard_AddDoc addDocWizard( this );
  addDocWizard.setDocumentCreationMode( Wizard_AddDoc::OnlyDetails );
  addDocWizard.setDoctypes( p->m__Doctypes );
  addDocWizard.setDocmanager( p->m__Docmanager );
  foreach ( QString clientInfo, p->m__Clients.keys() )
    addDocWizard.addClient( p->m__Clients.value( clientInfo ), clientInfo );
  addDocWizard.exec();
}
