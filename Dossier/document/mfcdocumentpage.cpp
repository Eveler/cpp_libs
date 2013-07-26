#include <QObject>
#include <QDir>
#include "mfcdocumentpage.h"
#include "amslogger.h"

MFCDocumentPage::MFCDocumentPage( QString pageName, const QByteArray &body )
{
  init(pageName);
  m_File->write(body);
}

MFCDocumentPage::MFCDocumentPage(QString pageName, const QPixmap &pixmap){
  init(pageName);
  pixmap.save(m_File,"PNG");
}

MFCDocumentPage::~MFCDocumentPage()
{
  delete m_PageName;
  delete m_File;
}

bool MFCDocumentPage::isValid()
{
  return ( !m_PageName->isEmpty() && m_File->size() > 0 );
}

const QString & MFCDocumentPage::getPageName()
{
  return *m_PageName;
}

QByteArray MFCDocumentPage::getBody()
{
  m_File->seek(0);
  return m_File->readAll();
}

QIODevice *MFCDocumentPage::device(){
  return m_File;
}

void MFCDocumentPage::init(const QString pageName){
  m_PageName = new QString( pageName );

  QDir d=QDir();
  d.mkdir("temp");
  m_File = new QTemporaryFile( QObject::tr( "temp/mfc_doc" ), 0 );
  if(!m_File->open()){
    LogWarning()<<QObject::tr("Error")<<m_File->error()<<":"<<
                  m_File->errorString();
    exit(-1);
  }
}

