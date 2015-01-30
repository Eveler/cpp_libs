#include "mfcdocumentzipper.h"

#include "amslogger.h"
#include "mfcdocument.h"
#include "quazipfile.h"
#include "poppler-qt5.h"

#include <QFileInfo>
#include <QObject>
#include <QTemporaryFile>
#include <QSettings>
#include <QMetaProperty>
#include <QImageReader>
#include <QBuffer>
#include <QPrinter>
#include <QPainter>

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
  QString format = requisites.value("FORMAT/version","0").toString();
  if(format!="1.0" && format!="1.1"){
    setError( tr("Не совместимый формат документа %1. Требуется 1.0 или 1.1").arg(
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

  if(requisites.allKeys().contains("PDF/file")){
    //////////////////////// PDF variant ///////////////////////////////////////
    QuaZipFile zip(
          m__FilePath,
          requisites.value("PDF/file").toString());
    if(!zip.open(QIODevice::ReadOnly)){
      setError(tr("Ошибка при чтении архива: ")+zipErrStr(zip.getZipError()));
      return false;
    }
    if(!addPDF(doc, zip.readAll(), &requisites)){
      zip.close();
      return false;
    }
    zip.close();
  }else if(requisites.allKeys().contains("PAGES/count")){
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
  return true;
}

bool MFCDocumentZipper::save(MFCDocument *doc , Format fmt)
{
  QuaZip zip( m__FilePath );
  if(!zip.open(QuaZip::mdCreate)){
    setError( tr( "Ошибка при создании архива: " )+zipErrStr(zip.getZipError()) );
    return false;
  }

  QuaZipFile zipf(&zip);
  QuaZipNewInfo zinfo=QuaZipNewInfo("");

  // сохраним реквизиты документа //////////////////////////////////////////////
#ifndef QT_NO_DEBUG
  qDebug()<<"Archiving doc requisites";
#endif
  zinfo=QuaZipNewInfo(tr("requisites.ini"));
  zinfo.internalAttr=0660;
  zinfo.externalAttr=0660;
  if(!zipf.open(QIODevice::WriteOnly,zinfo)){
    setError( tr( "Ошибка при добавлении реквизитов в архив: ")+
              zipErrStr(zipf.getZipError()) );
    zip.close();
    return false;
  }
  QTextStream stream(&zipf);
  stream.setCodec("UTF-8");
  stream<<"[FORMAT]\n";
  QString format = fmt==Version11?"1.1":"1.0";
  stream<<"version="<<format<<"\n";
  stream<<"[e-Doc]"<<"\n";
  const QMetaObject *mobj=doc->metaObject();
  for(int i=mobj->propertyOffset();i<mobj->propertyCount();i++){
    QMetaProperty p=mobj->property(i);
    stream<<p.name()<<"=";
    if(p.type()==QVariant::DateTime)
      stream<<doc->property(p.name()).toDateTime().toString(
                "dd.MM.yyyy hh:mm:ss.zzz")<<"\n";
    else if(p.type()==QVariant::Date)
      stream<<doc->property(p.name()).toDateTime().toString(
                "dd.MM.yyyy")<<"\n";
    else stream<<"\""<<doc->property(p.name()).toString()<<"\"\n";
  }
  if(doc->haveAttachments()){
    DocAttachments *atts=doc->attachments();
    stream<<"[ATTACHMENTS]\n";
    stream<<"count="<<atts->count()<<"\n";
    for(int a=0;a<atts->count();a++){
      const DocAttachment &att=atts->getAttachment(a);
      QFileInfo fi(att.fileName());
      stream<<"filename"<<a<<"="<<att.fileName()<<"\n";
      stream<<"mimetype"<<a<<"="<<att.mimeType()<<"\n";
      stream<<"file"<<a<<"="<<"attachment"<<a<<"."<<fi.completeSuffix()<<"\n";
    }
  }
  if(doc->havePages()){
    MFCDocumentPages *pages=doc->pages();
    if(fmt==Version11){
      //////////////////////// PDF variant /////////////////////////////////////
      stream<<"[PDF]\n";
      stream<<"file=pages.pdf\n";
      stream<<"count="<<pages->count()<<"\n";
      for(int p=0;p<pages->count();p++){
        MFCDocumentPage *page=pages->getPage(p);
        stream<<"name"<<p<<"="<<page->getPageName()<<"\n";
      }
    }else{
      stream<<"[PAGES]\n";
      stream<<"count="<<pages->count()<<"\n";
      for(int p=0;p<pages->count();p++){
        MFCDocumentPage *page=pages->getPage(p);
        stream<<"name"<<p<<"="<<page->getPageName()<<"\n";
        stream<<"file"<<p<<"="<<"page"<<p<<".jpg\n";
      }
    }
  }
  stream.flush();
  zipf.close();
  if(zipf.getZipError()!=UNZ_OK){
    setError( tr( "Ошибка при добавлении реквизитов в архив: ")+
              zipErrStr(zipf.getZipError()) );
    zip.close();
    return false;
  }
  ////////////////////////////////////////////// сохраним реквизиты документа //

  // сохраним вложение (документ, созданный в сторонней программе) /////////////
  if(doc->haveAttachments()){
#ifndef QT_NO_DEBUG
    qDebug()<<"Archiving doc attachments";
#endif
    DocAttachments *atts=doc->attachments();
#ifndef QT_NO_DEBUG
    qDebug()<<"attachments.count():"<<atts->count();
#endif
    for(int a=0;a<atts->count();a++){
      const DocAttachment &att=atts->getAttachment(a);
      QFileInfo fi(att.fileName());
#ifndef QT_NO_DEBUG
      qDebug()<<"Archiving doc attachment"<<tr("attachment")+att.fileName()<<
             "size ="<<att.device()->size();
#endif
      zinfo=QuaZipNewInfo(tr("attachment%1.%2").arg(a).arg(fi.completeSuffix()));
      zinfo.internalAttr=0660;
      zinfo.externalAttr=0660;
      if(!zipf.open(QIODevice::WriteOnly,
                    QuaZipNewInfo(zinfo))){
        setError( tr( "Ошибка при добавлении вложения в архив: ")+
                  zipErrStr(zipf.getZipError()) );
        zip.close();
        return false;
      }
      zipf.write(att.data());
      zipf.close();
      if(zipf.getZipError()!=UNZ_OK){
        setError( tr( "Ошибка при добавлении вложения в архив: ")+
                  zipErrStr(zipf.getZipError()) );
        zip.close();
        return false;
      }
    }
  }
  ///////////// сохраним вложение (документ, созданный в сторонней программе) //

  // сохраним страницы /////////////////////////////////////////////////////////
  if(doc->havePages()){
#ifndef QT_NO_DEBUG
    qDebug()<<"Archiving doc pages";
#endif
    MFCDocumentPages *pages=doc->pages();
#ifndef QT_NO_DEBUG
    qDebug()<<"pages.count():"<<pages->count();
#endif

    if(fmt==Version11){
      //////////////////////// PDF variant /////////////////////////////////////
      QPrinter printer;
      QFileInfo fi(QFileInfo(m__FilePath).absolutePath()+"/pages.pdf");
      printer.setOutputFileName(fi.absoluteFilePath());
      printer.setResolution(200);
      printer.setPaperSize(QPrinter::A4);
      printer.setOrientation(QPrinter::Portrait);
      printer.setPageMargins(5, 5, 5, 5, QPrinter::Millimeter);
      QPainter painter;
      painter.begin(&printer);

      int count = pages->count();
      for(int pIdx=0;pIdx<count;pIdx++){
        QPixmap pixmap = QPixmap();
        MFCDocumentPage *page = pages->getPage(pIdx);
        pixmap.loadFromData(page->getBody());
        painter.drawPixmap(
              0, 0, pixmap.scaled(printer.pageRect().size(),
                                  Qt::KeepAspectRatio, Qt::SmoothTransformation));
        if(pIdx<count-1) printer.newPage();
        emit dataTransferProgress(pIdx+1, pages->count());
      }

      painter.end();

      zinfo=QuaZipNewInfo("pages.pdf");
      zinfo.internalAttr=0660;
      zinfo.externalAttr=0660;
      if(!zipf.open(QIODevice::WriteOnly,
                    QuaZipNewInfo(zinfo))){
        setError(tr("Ошибка при добавлении страниц в архив: %1").arg(
                   zipErrStr(zipf.getZipError())));
        zip.close();
        return false;
      }

      QFile pdf(fi.absoluteFilePath());
      if(!pdf.open(QFile::ReadOnly)){
        pdf.remove();
        zipf.close();
        zip.close();
        setError(tr("Ошибка чтения временного файла: ").arg(pdf.errorString()));
        return false;
      }
      zipf.write(pdf.readAll());
      zipf.close();
      pdf.remove();
      if(zipf.getZipError()!=UNZ_OK){
        setError(tr("Ошибка при добавлении страниц в архив: %1").arg(
                   zipErrStr(zipf.getZipError())));
        zip.close();
        return false;
      }
    }else{
      for(int p=0;p<pages->count();p++){
        MFCDocumentPage *page=pages->getPage(p);
  #ifndef QT_NO_DEBUG
        qDebug()<<"Archiving doc page:"<<
               tr("page%1_%2").arg(p).arg(page->getPageName());
  #endif
        zinfo=QuaZipNewInfo(tr("page%1.jpg").arg(p));
        zinfo.internalAttr=0660;
        zinfo.externalAttr=0660;
        if(!zipf.open(QIODevice::WriteOnly,
                      QuaZipNewInfo(zinfo))){
          setError( tr( "Ошибка при добавлении страницы %1 в архив: ").arg(p+1)+
                    zipErrStr(zipf.getZipError()) );
          return false;
        }
        page->device()->seek(0);
        QImageReader ir(page->device());
        if(ir.format().toUpper()!="JPG" || ir.format().toUpper()!="JPEG"){
          QBuffer buf;
          QImage im;
          im=ir.read();
          if(im.isNull()){
            setError( tr( "Ошибка при обработке страницы %1: %2").arg(p+1).arg(ir.errorString()) );
            return false;
          }
          buf.open(QBuffer::ReadWrite);
          im.save(&buf,"JPG");
          zipf.write(buf.buffer());
        }else zipf.write(page->getBody());
        zipf.close();
        if(zipf.getZipError()!=UNZ_OK){
          setError( tr( "Ошибка при добавлении страницы %1 в архив: ").arg(p+1)+
                    zipErrStr(zipf.getZipError()) );
          return false;
        }
//      emit dataTransferProgress(p+1,pages->count(),tr("Обработка: %p%"));
        emit dataTransferProgress( p+1, pages->count() );
      }
    }
  }
  ///////////////////////////////////////////////////////// сохраним страницы //

  zip.close();

  return true;
}

bool MFCDocumentZipper::addPDF(MFCDocument *doc, QByteArray data,
                               QSettings *requisites){
  Poppler::Document *pdf = Poppler::Document::loadFromData(data);
  if(!pdf){
    setError(tr("Ошибка загрузки данных"));
    return false;
  }
  int pageCount = pdf->numPages();
  for(int a = 0; a < pageCount; a++){
    Poppler::Page *pdfPage = pdf->page(a);
    QString label = requisites?requisites->value(
          tr("PDF/name%1").arg(a), pdfPage->label()).toString():pdfPage->label();
    MFCDocumentPage *page=new MFCDocumentPage(
          label.isEmpty() || label.toInt()!=0?
          tr("Страница %1 (Скан %1)").arg(a+1):label,
          QPixmap::fromImage(pdfPage->renderToImage(200, 200)));
    doc->addPage(*page);
    qApp->processEvents();
    emit dataTransferProgress( a+1, pageCount );
  }

  return true;
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
