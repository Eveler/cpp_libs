#include "mfcdocumentzipper.h"

#include "amslogger.h"
#include "mfcdocument.h"
#include "quazipfile.h"

#include <QFileInfo>
#include <QObject>
#include <QTemporaryFile>
#include <QSettings>


MFCDocumentZipper::MFCDocumentZipper( QObject *parent ) :
  QObject(parent),
  MFCDocumentIOProvider()
{
}

void MFCDocumentZipper::setFilePath( const QString &filePath )
{
  m__FilePath = filePath;
}

const QString & MFCDocumentZipper::filePath() const
{
  return m__FilePath;
}

bool MFCDocumentZipper::load( MFCDocument *doc )
{
  LogDebug() << __func__ << m__FilePath << "BEGIN";
  if( m__FilePath.isEmpty() || doc == NULL ) return false;
  // обрабатываем архив и заполняем данными MFCDocument
  QuaZipFile zip( m__FilePath, "requisites.ini" );
  if(!zip.open(QIODevice::ReadOnly)){
    QFileInfo fi( m__FilePath );
    setError( tr("Ошибка при чтении архива: ")+zipErrStr(zip.getZipError())+
              tr(" размер файла: %1").arg(fi.size()) );
    return false;
  }
  QTemporaryFile reqFile("temp/requisites.ini");
  if(!reqFile.open()){
    setError( tr("Ошибка при создании временного файла реквизитов: ")+
              reqFile.errorString() );
    return false;
  }
  reqFile.write(zip.readAll());
  zip.close();
  reqFile.seek(0);
  QSettings requisites(reqFile.fileName(),QSettings::IniFormat);
  requisites.setIniCodec("UTF-8");
  if(requisites.value("FORMAT/version","0").toString()!="1.0"){
    setError( tr("Не совместимый формат документа %1. Требуется 1.0").arg(
                requisites.value("FORMAT/version","0").toString()) );
    return false;
  }
#ifndef QT_NO_DEBUG
  qDebug()<<requisites.allKeys();
#endif

  doc->setAgency(requisites.value("e-Doc/agency").toString());
  if(requisites.value("e-Doc/created").isValid() &&
     !requisites.value("e-Doc/created").isNull())
    doc->setCreateDate(
          QDateTime::fromString(
            requisites.value("e-Doc/created").toString(),
            "dd.MM.yyyy hh:mm:ss.zzz"));
  if(requisites.value("e-Doc/date").isValid() &&
     !requisites.value("e-Doc/date").isNull())
    doc->setDate(
          QDate::fromString(
            requisites.value("e-Doc/date").toString(),"dd.MM.yyyy"));
  if(requisites.value("e-Doc/expires").isValid() &&
     !requisites.value("e-Doc/expires").isNull())
    doc->setExpiresDate(
          QDate::fromString(
            requisites.value("e-Doc/expires").toString(),"dd.MM.yyyy"));
  doc->setName(requisites.value("e-Doc/name").toString());
  doc->setNumber(requisites.value("e-Doc/number").toString());
  doc->setSeries(requisites.value("e-Doc/series").toString());
  doc->setType(requisites.value("e-Doc/type").toString());
  if(requisites.allKeys().contains("ATTACHMENTS/count")){
    int attCount=requisites.value("ATTACHMENTS/count").toInt();
#ifndef QT_NO_DEBUG
    qDebug()<<"ATTACHMENTS:"<<attCount;
#endif
    for(int a=0;a<attCount;a++){
      QuaZipFile zip(
            m__FilePath,
            requisites.value( tr("ATTACHMENTS/file%1").arg(a)).toString() );
      if(!zip.open(QIODevice::ReadOnly)){
        setError(tr("Ошибка при чтении архива: ")+zipErrStr(zip.getZipError()));
        return false;
      }
      doc->addAttachment( requisites.value(tr("ATTACHMENTS/filename%1").arg(a)).toString(),
                          requisites.value(tr("ATTACHMENTS/mimetype%1").arg(a)).toString(),
                          zip.readAll() );
      zip.close();
    }
  }
  if(requisites.allKeys().contains("PAGES/count")){
    int pageCount=requisites.value("PAGES/count").toInt();
#ifndef QT_NO_DEBUG
    qDebug()<<"PAGES:"<<pageCount;
#endif
    for(int a=0;a<pageCount;a++){
      QuaZipFile zip(
            m__FilePath,
            requisites.value( tr("PAGES/file%1").arg(a)).toString() );
      if(!zip.open(QIODevice::ReadOnly)){
        setError(tr("Ошибка при чтении архива: ")+zipErrStr(zip.getZipError()));
        return false;
      }
      MFCDocumentPage *page=new MFCDocumentPage(
            requisites.value(tr("PAGES/name%1").arg(a)).toString(),
            zip.readAll());
      doc->addPage(*page);
      zip.close();
      emit dataTransferProgress( a+1, pageCount );
    }
  }

#ifndef QT_NO_DEBUG
  qDebug()<<"document:"<<doc->name()<<doc->series()<<doc->number()<<doc->date()<<
         "- created";
#endif
  LogDebug() << __func__ << m__FilePath << "END";
  return true;
}

bool MFCDocumentZipper::save( MFCDocument *doc )
{

}

QString MFCDocumentZipper::zipErrStr( int errn )
{
  QString erStr=tr("Неизвестная ошибка");
  switch(errn){
  case UNZ_OPENERROR:
    erStr=tr("Ошибка открытия файла");
    break;
  case UNZ_CRCERROR:
    erStr=tr("Ошибка CRC");
    break;
  case UNZ_BADZIPFILE:
    erStr=tr("Повреждённый файл архива");
    break;
  }
  return "Zip: "+erStr;
}
