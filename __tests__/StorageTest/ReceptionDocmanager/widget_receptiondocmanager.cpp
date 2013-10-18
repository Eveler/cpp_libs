#include "widget_receptiondocmanager.h"
#include "ui_widget_receptiondocmanager.h"

#include "receptiondocmanager_p.h"
#include "wizard_adddoc.h"
#include "mfccore.h"
#include "dialog_selectdocument.h"
#include "edvprocess.h"
#include "dialog_docdetails.h"

#include <QMessageBox>
#include <QScrollBar>


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

void Widget_ReceptionDocmanager::setDatabase( QSqlDatabase db )
{
  if ( p->m__Docmanager != NULL )
  {
    delete p->m__Docmanager;
    p->m__Docmanager = NULL;
  }

  if ( !db.isValid() ) return;

  p->m__Docmanager = new Docmanager( db, this );
  disconnect( p->m__Docmanager, SIGNAL(documentAdded(DocumentsModel*)),
              this, SLOT(newDocs_ResetViewport()) );
  connect( p->m__Docmanager, SIGNAL(documentAdded(DocumentsModel*)),
           SLOT(newDocs_ResetViewport()) );
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

  if ( id.isNull() )
  {
    p->m__Docmanager->unsetDeclar();
    return;
  }

  p->m__Clients.clear();

  p->m__Docmanager->clear();
  p->m__Docmanager->setDeclar( id );

  ui->tView_New->setModel( p->m__Docmanager->addedDocuments() );
  newDocs_ResetViewport();
  p->recalcNewDocuments( qobject_cast<DocumentsModel *>( ui->tView_New->model() ) );
  ui->tView_Required->expandAll();
}

QVariant Widget_ReceptionDocmanager::declar() const
{
  return p->m__Docmanager->declar();
}

void Widget_ReceptionDocmanager::addClient( const QVariant &id, const QString &clientInfo )
{
  if ( p->m__Docmanager == NULL ) return;

  p->m__Docmanager->addClient( id );
  p->m__Docmanager->unsetCurrentClient();
  p->m__Clients[clientInfo] = id;
}

void Widget_ReceptionDocmanager::addDocpaths( const QVariant &id )
{
  if ( p->m__Docmanager == NULL ) return;

  p->m__Docmanager->addDocpaths( id );
  p->m__Docmanager->unsetCurrentDocpaths();
}

void Widget_ReceptionDocmanager::setCurrentDocpaths( const QVariant &id )
{
  p->m__Docmanager->setDocpathsCurrent( id );
}

void Widget_ReceptionDocmanager::setRequiredDocs( RequiredDocs *requiredDocs )
{
  if( requiredDocs == NULL ) return;

  p->m__RequiredDocs = requiredDocs;
  p->recalcNewDocuments( qobject_cast<DocumentsModel *>( ui->tView_New->model() ) );
  ui->tView_Required->expandAll();

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

void Widget_ReceptionDocmanager::setAppealInfo(
    const QString &appealNum, QDate appealDate, QDate declarExpires )
{
  p->m__AppealNum = appealNum;
  p->m__AppealDate = appealDate;
  p->m__DeclarExpires = declarExpires;
}

QList<MFCDocumentInfo *> Widget_ReceptionDocmanager::newDocuments() const
{
  return p->m__Docmanager->addedDocuments()->documents();
}

void Widget_ReceptionDocmanager::clear()
{
  if ( p->m__Docmanager == NULL ) return;

  p->m__Clients.clear();

  p->m__Docmanager->clear();
}

bool Widget_ReceptionDocmanager::isCompleted() const
{
  return ( p->m__RequiredDocs &&
           p->m__RequiredDocs->requiredDocTypes().count() == 0 );
}

void Widget_ReceptionDocmanager::reqDocs_ResetViewport()
{
  if ( !p->reqCurIndex.isValid() ) return;
  ui->tView_Required->verticalScrollBar()->setValue( p->reqSBVal );
  ui->tView_Required->setCurrentIndex( p->reqCurIndex );
  p->reqSBVal = -1;
  p->reqCurIndex = QModelIndex();
}

void Widget_ReceptionDocmanager::newDocs_ResetViewport()
{
  if ( ui->tView_New->model()->columnCount() > 10 )
    for ( int rIdx = ui->tView_New->model()->columnCount()-1; rIdx > 10; rIdx-- )
      ui->tView_New->hideColumn( rIdx );
  ui->tView_New->resizeColumnsToContents();
  ui->tView_New->resizeRowsToContents();

  emit completedChanged();
}

void Widget_ReceptionDocmanager::on_tView_Required_doubleClicked(const QModelIndex &index)
{
  connect( ui->tView_Required->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
           SLOT(reqDocs_ResetViewport()), Qt::UniqueConnection );
  p->reqSBVal = ui->tView_Required->verticalScrollBar()->value();
  p->reqCurIndex = index;

  const QAbstractItemModel *mdl=index.model();
  if( mdl != p->m__RequiredDocs->model() ) return;
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
    QStringList doctypes = QStringList() << doctype;
    if ( index.parent().isValid() )
    {
      int col = MFCCore::findColumn(mdl,tr("Наименование"));
      for ( QModelIndex sub = index.parent().child( 0, col );
            sub.isValid(); sub = sub.sibling( sub.row()+1, col ) )
        if ( !doctypes.contains( sub.data().toString() ) )
          doctypes << sub.data().toString();
    }

    if ( doctype == Doc_Warrant && need-1 == added )
    {
      emit newDocument( doctype );
      if ( !p->newDocument( doctype, p->m__AppealNum,
                            p->m__AppealDate, p->m__DeclarExpires ) )
        return;
    }
    else if ( doctype == Doc_Agreement )
    {
      emit newDocument( doctype );
      if ( !p->newDocument( doctype, QString(), p->m__AppealDate ) )
        return;
    }
    else if ( doctype == Doc_Application &&
              doctype == Doc_AppRespite &&
              doctype == Doc_AppCancellation )
    {
      emit newDocument( doctype );
      if ( !p->newDocument( doctype ) )
        return;
    }
    else if ( doctype == Doc_Pasport )
    {
      QList<QPair<MFCDocumentInfo *, QVariant> > newDocs;
      bool rejected = false;
      foreach ( QVariant id, p->m__Clients.values() )
      {
        DocumentsModel *dm = p->findClientDocuments( id, doctypes );
        if ( dm == NULL ) return;

        if ( dm->rowCount() > 0 )
        {
          Dialog_SelectDocument dSelectDocument;
          dSelectDocument.setWindowTitle( tr( "Выберите документ" ) );
          dSelectDocument.setAutoExclusive( true );
          dSelectDocument.setCreatableDoctypes( QStringList() << doctypes );
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
                                   QStringList() << doctypes );
          if ( doc == NULL )
          {
            if ( !elDocProc.lastError().isEmpty() )
              QMessageBox::warning( this, tr( "Ошибка" ), elDocProc.lastError() );
            rejected = true;
          }
          else
          {
            Dialog_DocDetails dDocDetails;
            if( dDocDetails.exec( doc, Dialog_DocDetails::WritePagesnum ) == QDialog::Rejected )
              rejected = true;
            else newDocs << qMakePair( doc, id );
          }
        }
        if ( rejected ) break;
      }

      if ( rejected )
      {
        while ( !newDocs.isEmpty() )
        {
          MFCDocumentInfo *doc = newDocs.takeFirst().first;
          MFCDocumentInfo::remove( doc );
        }

        return;
      }
      else
        while ( !newDocs.isEmpty() )
        {
          MFCDocumentInfo *doc = newDocs.first().first;
          QVariant clientId = newDocs.takeFirst().second;
          p->m__Docmanager->setClientCurrent( clientId );
          p->m__Docmanager->newDocument( doc );
        }
    }
    else
    {
      DocumentsModel *dm = p->findDocuments( doctype );
      if ( dm == NULL ) return;
      QList<MFCDocumentInfo *> docs;
      if ( dm->rowCount() > 0 )
      {
        Dialog_SelectDocument dSelectDocument;
        dSelectDocument.setWindowTitle( tr( "Выберите документ" ) );
        dSelectDocument.setCreatableDoctypes( QStringList() << doctypes );
        docs = dSelectDocument.exec( p->m__Docmanager, dm );
        dm->clear();

        if ( docs.isEmpty() ) return;

        foreach ( QVariant id, p->m__Clients.values() )
        {
          p->m__Docmanager->setClientCurrent( id );
          foreach ( MFCDocumentInfo *doc, docs )
            p->m__Docmanager->newDocument( doc );
        }
      }
      else
      {
        EDVProcess elDocProc;
        MFCDocumentInfo *doc = elDocProc.writeDocument(
                                 QStringList() << doctype );
        if ( doc == NULL )
        {
          if ( !elDocProc.lastError().isEmpty() )
            QMessageBox::warning( this, tr( "Ошибка" ), elDocProc.lastError() );
          return;
        }
        else
        {
          Dialog_DocDetails dDocDetails;
          if( dDocDetails.exec( doc, Dialog_DocDetails::WritePagesnum ) == QDialog::Rejected )
            return;
          docs << doc;
        }
      }

      delete dm;
      dm = NULL;
    }

    p->recalcNewDocuments( qobject_cast<DocumentsModel *>( ui->tView_New->model() ) );
    ui->tView_Required->expandAll();
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

void Widget_ReceptionDocmanager::on_tBt_Remove_clicked()
{
  if ( !ui->tView_New->currentIndex().isValid() ) return;

  p->m__Docmanager->removeNewDocument(
        p->m__Docmanager->addedDocuments()->documents()[ui->tView_New->currentIndex().row()] );
  p->recalcNewDocuments( qobject_cast<DocumentsModel *>( ui->tView_New->model() ) );
  ui->tView_Required->expandAll();
}

void Widget_ReceptionDocmanager::on_tView_Required_clicked(const QModelIndex &index)
{
}

