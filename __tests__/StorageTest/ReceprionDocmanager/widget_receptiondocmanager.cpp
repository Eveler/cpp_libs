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

void Widget_ReceptionDocmanager::on_tView_Required_doubleClicked(const QModelIndex &index)
{

}

void Widget_ReceptionDocmanager::on_tView_New_doubleClicked(const QModelIndex &index)
{

}

void Widget_ReceptionDocmanager::on_tBt_Add_clicked()
{
  Wizard_AddDoc addDocWizard( p->m__Doctypes, p->m__Docmanager, this );
  addDocWizard.setDocumentCreationMode( Wizard_AddDoc::OnlyDetails );
  addDocWizard.exec();
}
