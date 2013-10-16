#include "widget_receptiondocmanager.h"
#include "ui_widget_receptiondocmanager.h"

#include "receptiondocmanager_p.h"
#include "wizard_adddoc.h"
#include "mfccore.h"
#include "dialog_selectdocument.h"
#include "edvprocess.h"

#include <QMessageBox>


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

Docmanager * Widget_ReceptionDocmanager::docmanager() const
{
  return p->m__Docmanager;
}

void Widget_ReceptionDocmanager::setDoctypes( const QStringList &doctypes )
{
  p->m__Doctypes = doctypes;
}

void Widget_ReceptionDocmanager::setDeclar( const QVariant &id )
{
  if ( p->m__Docmanager == NULL ) return;

  p->m__Clients.clear();

  p->m__Docmanager->clear();
  p->m__Docmanager->setDeclar( id );
}

void Widget_ReceptionDocmanager::addClient( const QVariant &id, const QString &clientInfo )
{
  if ( p->m__Docmanager == NULL ) return;

  p->m__Docmanager->addClient( id );
  p->m__Clients[clientInfo] = id;
}

void Widget_ReceptionDocmanager::addDocpaths( const QVariant &id )
{
  if ( p->m__Docmanager == NULL ) return;

  p->m__Docmanager->addDocpaths( id );
  p->m__Docmanager->setDocpathsCurrent( id );
}

void Widget_ReceptionDocmanager::setRequiredDocs( RequiredDocs *requiredDocs )
{
  if( requiredDocs == NULL ) return;

  p->m__RequiredDocs = requiredDocs;
  p->m__RequiredDocs->reset();

  QAbstractItemModel *model = p->m__RequiredDocs->model();
  ui->tView_Required->setModel(model);
  for(int c=0;c<model->columnCount();c++)
    ui->tView_Required->resizeColumnToContents(c);
  ui->tView_Required->setItemDelegateForColumn(
        MFCCore::findColumn( model, tr( "Необходимый" ) ), p->m__BoolDelegate );
  ui->tView_Required->setItemDelegateForColumn(
        MFCCore::findColumn( model, tr( "Образец" ) ), p->m__ButtonDelegate );
  ui->tView_Required->expandAll();
}

void Widget_ReceptionDocmanager::clear()
{
  if ( p->m__Docmanager == NULL ) return;

  p->m__Clients.clear();

  p->m__Docmanager->clear();
}

void Widget_ReceptionDocmanager::on_tView_Required_doubleClicked(const QModelIndex &index)
{
  const QAbstractItemModel *mdl=index.model();
  if(!mdl) return;
  if(index.column()!=MFCCore::findColumn(mdl,tr("Образец"))){
    QModelIndex idx=mdl->index(
          index.row(),
          MFCCore::findColumn(mdl,tr("Наименование")),index.parent());
    int need = mdl->index(
                 index.row(),
                 MFCCore::findColumn(
                   mdl, tr( "Количество" ) ), index.parent() ).data().toInt();
    int added = mdl->index(
                  index.row(),
                  MFCCore::findColumn(
                    mdl, tr( "Добавлено" ) ), index.parent() ).data().toInt();

    // строка с категорией пропускается
    if(!idx.parent().isValid() && idx.child(0,0).isValid()) return;

    QString doctype=idx.data().toString();

    if ( doctype == Doc_Warrant && need-1 == added )
      emit newDocument( doctype );
    else if ( doctype == Doc_Agreement && doctype == Doc_AppCancellation &&
              doctype == Doc_Application && doctype == Doc_AppRespite )
    {
      emit newDocument( doctype );
      return;
    }

    if ( doctype == Doc_Pasport )
    {
      QList<QPair<MFCDocumentInfo *, QVariant> > newDocs;
      bool rejected = false;
      foreach ( QVariant id, p->m__Clients.values() )
      {
        DocumentsModel *dm = p->findClientDocuments( id, doctype );
        if ( dm == NULL ) return;

        if ( dm->rowCount() > 0 )
        {
          Dialog_SelectDocument dSelectDocument;
          dSelectDocument.setWindowTitle( tr( "Выберите документ" ) );
          dSelectDocument.setAutoExclusive( true );
          QList<MFCDocumentInfo *> docs = dSelectDocument.exec(
                                            p->m__Docmanager, dm, p->m__Clients.key( id ) );
          if ( docs.isEmpty() ) rejected = true;
          else newDocs << qMakePair( docs.first(), id );
          dm->clear();
          delete dm;
          dm = NULL;
        }
        else
        {
          EDVProcess elDocProc;
          MFCDocumentInfo *doc = elDocProc.writeDocument(
                                   QStringList() << Doc_Pasport,
                                   QStringList() );
          if ( doc == NULL )
          {
            if ( !elDocProc.lastError().isEmpty() )
              QMessageBox::warning( this, tr( "Ошибка" ), elDocProc.lastError() );
            rejected = true;
          }
          else newDocs << qMakePair( doc, id );
        }
        if ( rejected ) break;
      }

      if ( rejected )
        while ( !newDocs.isEmpty() )
        {
          MFCDocumentInfo *doc = newDocs.takeFirst().first;
          MFCDocumentInfo::remove( doc );
        }
      else
        while ( !newDocs.isEmpty() )
        {
          MFCDocumentInfo *doc = newDocs.first().first;
          QVariant clientId = newDocs.takeFirst().second;
          p->m__Docmanager->setClientCurrent( clientId );
          p->m__Docmanager->newDocument( doc );
        }

      return;
    }

    DocumentsModel *dm = p->findDocuments( doctype );
    if ( dm == NULL ) return;
    if ( dm->rowCount() > 0 )
    {
      Dialog_SelectDocument dSelectDocument;
      dSelectDocument.setWindowTitle( tr( "Выберите документ" ) );
      QList<MFCDocumentInfo *> docs = dSelectDocument.exec( p->m__Docmanager, dm );
      dm->clear();

      foreach ( QVariant id, p->m__Clients.values() )
      {
        p->m__Docmanager->setClientCurrent( id );
        foreach ( MFCDocumentInfo *doc, docs )
          p->m__Docmanager->newDocument( doc );
      }
    }
    delete dm;
    dm = NULL;
  }
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
