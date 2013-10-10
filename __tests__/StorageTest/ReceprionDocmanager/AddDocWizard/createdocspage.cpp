#include "createdocspage.h"
#include "ui_createdocspage.h"

#include "edvprocess.h"
#include "dialog_docdetails.h"

#include <QMessageBox>


CreateDocsPage::CreateDocsPage( const QStringList &doctypes, QWidget *parent ) :
  QWizardPage(parent),
  ui(new Ui::CreateDocsPage)
{
  ui->setupUi(this);

  setTitle( tr( "Создание новых документов" ) );
  setCreateText( tr( "Создать документ" ) );

  m__Doctypes = doctypes;
  m__Documents = new DocumentsModel( this );
  ui->tableView->setModel( m__Documents );
  registerField( "CreatedDocuments", ui->tableView );

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

void CreateDocsPage::on_tBt_Create_clicked()
{
//  EDVProcess elDocProc;
//  MFCDocumentInfo *doc = elDocProc.writeDocument( m__Doctypes, QStringList() );
//  if ( doc == NULL )
//  {
//    if ( !elDocProc.lastError().isEmpty() )
//      QMessageBox::warning( this, tr( "Ошибка" ), elDocProc.lastError() );
//  }
//  else if ( docmanager->declarDocuments()->addDocument( doc ) )
//  {
//    QFileInfo fi( doc->localFile() );
//    QString newPath = tr( "%1/temp/%2" ).arg( qApp->applicationDirPath(), fi.fileName() );
//    if ( !QFile::copy( fi.absoluteFilePath(), newPath ) )
//    {
//      QMessageBox::warning( this, tr( "Ошибка" ),
//                            tr( "Ошибка прикопировании файла:\nиз %1\nв %2" ).arg(
//                              fi.absoluteFilePath(), newPath ) );
//      return;
//    }
//    doc->setLocalFile( newPath );
//    QFile::remove( fi.absoluteFilePath() );
//    docmanager->save();
//  }

  Dialog_DocDetails docDetails( this );
  docDetails.exec( m__Doctypes );
}

void CreateDocsPage::setCreateText( const QString &text )
{
  ui->tBt_Create->setText( text );
  setSubTitle( tr( "<html><head/><body><p><span style=\" color:#000000;\">Для создания документа нажмите на кнопку </span><span style=\" font-weight:600; color:#000000;\">%1</span><span style=\" color:#000000;\"> и введите реквезиты нового документа</span></p></body></html>" ).arg( text ) );
}
