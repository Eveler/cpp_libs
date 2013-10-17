#include "createdocspage.h"
#include "ui_createdocspage.h"

#include "wizard_adddoc.h"
#include "edvprocess.h"
#include "dialog_docdetails.h"

#include <QMessageBox>


CreateDocsPage::CreateDocsPage( QWidget *parent ) :
  QWizardPage(parent),
  ui(new Ui::CreateDocsPage)
{
  ui->setupUi(this);

  setTitle( tr( "Создание новых документов" ) );
  setCreateText( tr( "Создать документ" ) );

  m__Documents = new DocumentsModel( this );
  ui->tableView->setModel( m__Documents );
  m__DocumentMode = Wizard_AddDoc::OnlyDetails;

  setFinalPage( true );
}

CreateDocsPage::~CreateDocsPage()
{
  m__Documents->clear();
  delete m__Documents;
  m__Documents = NULL;

  delete ui;
}

int CreateDocsPage::nextId() const
{
  return -1;
}

void CreateDocsPage::initializePage()
{
  QTimer *timer = new QTimer( this );
  timer->singleShot( 100, ui->tBt_Create, SLOT(click()) );
  timer->deleteLater();
}

bool CreateDocsPage::isComplete() const
{
  return m__Documents->rowCount() > 0;
}

DocumentsModel * CreateDocsPage::createdDocs() const
{
  return m__Documents;
}

void CreateDocsPage::setDocumentCreationMode( int documentMode )
{
  m__DocumentMode = documentMode;
}

void CreateDocsPage::setDoctypes( const QStringList &doctypes )
{
  m__Doctypes = doctypes;
}

void CreateDocsPage::on_tBt_Create_clicked()
{
  bool withBody = false;
  MFCDocumentInfo *doc = NULL;

  if ( m__DocumentMode == (int)Wizard_AddDoc::WithBody ) withBody = true;
  else if ( m__DocumentMode == (int)Wizard_AddDoc::Both )
  {

  }

  if ( withBody )
  {
    EDVProcess elDocProc;
    doc = elDocProc.writeDocument( m__Doctypes );
    if ( doc == NULL )
    {
      if ( !elDocProc.lastError().isEmpty() )
        QMessageBox::warning( this, tr( "Ошибка" ), elDocProc.lastError() );
    }
    else if ( m__Documents->addDocument( doc ) )
    {
      QFileInfo fi( doc->localFile() );
      QString newPath = tr( "%1/temp/%2" ).arg( qApp->applicationDirPath(), fi.fileName() );
      if ( !QFile::copy( fi.absoluteFilePath(), newPath ) )
      {
        QMessageBox::warning( this, tr( "Ошибка" ),
                              tr( "Ошибка прикопировании файла:\nиз %1\nв %2" ).arg(
                                fi.absoluteFilePath(), newPath ) );
        return;
      }
      doc->setLocalFile( newPath );
      QFile::remove( fi.absoluteFilePath() );
    }
  }
  else
  {
    Dialog_DocDetails docDetails( this );
    docDetails.setWindowTitle( tr( "Новый документ" ) );
    doc = docDetails.exec( m__Doctypes );
  }

  if ( doc == NULL ) return;
  m__Documents->addDocument( doc );
  for ( int rIdx = m__Documents->columnCount()-1; rIdx > 10; rIdx-- )
    ui->tableView->hideColumn( rIdx );
  ui->tableView->resizeColumnsToContents();

  if ( m__Documents->rowCount() > 0 )
    setCreateText( tr( "Добавить ещё документ" ) );
  emit completeChanged();
}

void CreateDocsPage::setCreateText( const QString &text )
{
  ui->tBt_Create->setText( text );
  setSubTitle( tr( "<html><head/><body><p><span style=\" color:#000000;\">Для создания документа нажмите на кнопку </span><span style=\" font-weight:600; color:#000000;\">%1</span><span style=\" color:#000000;\"> и введите реквезиты нового документа</span></p></body></html>" ).arg( text ) );
}

void CreateDocsPage::on_tableView_doubleClicked(const QModelIndex &index)
{
  if ( !index.isValid() ) return;

  MFCDocumentInfo *doc = m__Documents->document( index.row() );
  if ( doc == NULL ) return;
  Dialog_DocDetails docDetails( this );
  docDetails.setWindowTitle( tr( "Новый документ" ) );
  docDetails.exec( doc );
}

void CreateDocsPage::on_tBt_Delete_clicked()
{
  QModelIndex index = ui->tableView->currentIndex();
  if ( !index.isValid() ) return;

  int res = QMessageBox::question( this, tr( "Удаление документа" ),
                                   tr( "Вы действительно хотите удалить документ?" ) );
  if ( res == (int)QMessageBox::No ) return;

  MFCDocumentInfo *doc = m__Documents->document( index.row() );
  if ( doc == NULL ) return;
  m__Documents->removeDocument( doc );
  MFCDocumentInfo::remove( doc );
  doc = NULL;
}
