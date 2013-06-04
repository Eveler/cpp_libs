#include "ftpdocsstorage.h"
#include <QUuid>
#include <QDataStream>
#include "quazipfile.h"
#include <QFileInfo>
#include <QSettings>
#include <QCoreApplication>
#include <QDir>
#include <QMetaProperty>
#include <QBuffer>
#include <QImageReader>
#include "amslogger.h"

#define setError(str) emitError(str,__FILE__,__LINE__)

QString FtpDocsStorage::errStr=QString();

FtpDocsStorage::FtpDocsStorage(const QString storageName,
                               const QString dataBaseName, QObject *parent) :
  AbstractDocsStorage(storageName,parent),curPath()
{
//  connected=false;
//  ftpBrowser=NULL;

  dbName=dataBaseName;
  rootPath="/";
  curDoc=NULL;
  docCount=1;
  docsDone=1;
  isDownloading=false;
  ftpPort=21;
  ftpEng=NULL;
}

FtpDocsStorage::~FtpDocsStorage(){
//  if(ftpBrowser!=NULL) delete ftpBrowser;
  if(ftpEng) ftpEng->deleteLater();
}

FtpDocsStorage &FtpDocsStorage::addStorage(const QString storageName){
  if(AbstractDocsStorage::contains(storageName)){
    return *qobject_cast< FtpDocsStorage* >(
          &AbstractDocsStorage::addStorage(storageName));
  }else{
    FtpDocsStorage *storage=new FtpDocsStorage(storageName);
    if(storage==NULL){
      errStr=tr("Ошибка при получении экземпляра DocsStorage");
      return *storage;
    }
//    storage->ftpBrowser=NULL;
    storage->setDataBaseName();
    storage->rootPath="/";
    storage->curDoc=NULL;
    storage->docCount=1;
    storage->docsDone=1;
//    storage->connected=false;

    return *storage;
  }
}

void FtpDocsStorage::setDataBaseName(const QString dataBaseName){
  dbName=dataBaseName;
}

bool FtpDocsStorage::connectToHost(const QString uName, const QString pass,
                                const QString host, const quint16 port){
//  if(connected) return true;
  userName=uName;
  userPass=pass;
  ftpHost=host;
  ftpPort=port;
//  connected=true;

  if(!ftpEng){
    ftpEng=new FTPEngine(this);
    connect(ftpEng,SIGNAL(authenticationCompleted(bool)),
            SLOT(authenticationCompleted(bool)));
    connect(ftpEng,SIGNAL(ftpAnswer(FTPEngine::Command,bool)),
            SLOT(ftpAnswer(FTPEngine::Command,bool)));
    connect(ftpEng,SIGNAL(loadProgress(qint64,qint64,QString)),
            SLOT(ftpTransferProgress(qint64,qint64)));
//    connect(ftpEng,SIGNAL(ftpAnswer(QString,int)),SLOT(ftpAnswer(QString,int)));
  }
  QUrl url;
  url.setScheme("ftp");
  url.setHost(ftpHost);
  url.setUserName(userName);
  url.setPassword(userPass);
  ftpEng->connectToHost(url,ftpPort);

//  setRoot();
  return true;
}

void FtpDocsStorage::setRoot(const QString dataBaseName, const QString path){
#ifndef QT_NO_DEBUG
  qDebug()<<"path:"<<path<<"dbName"<<dbName;
#endif
  rootPath="/"+path+"/"+(dbName!=dataBaseName?dataBaseName:dbName);
  rootPath.replace("//","/");
//  ftpBrowser->cd("/"+path+"/"+(dbName!=dataBaseName?dataBaseName:dbName));
  ftpEng->cd("/"+path+"/"+(dbName!=dataBaseName?dataBaseName:dbName));
}

QString FtpDocsStorage::errorString(){
  return errStr;
}

bool FtpDocsStorage::saveZip(MFCDocument* doc,const QString fileName){
  QuaZip zip(fileName);
  if(!zip.open(QuaZip::mdCreate)){
    errStr=tr("Ошибка при создании архива: ")+zipErrStr(zip.getZipError());
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
    errStr=tr("Ошибка при добавлении реквизитов в архив: ")+
        zipErrStr(zipf.getZipError());
    return false;
  }
  QTextStream stream(&zipf);
  stream.setCodec("UTF-8");
  stream<<"[FORMAT]\n";
  stream<<"version=1.0\n";
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
      DocAttachment *att=atts->getAttachment(a);
      stream<<"filename"<<a<<"="<<att->fileName()<<"\n";
      stream<<"mimetype"<<a<<"="<<att->mimeType()<<"\n";
      stream<<"file"<<a<<"="<<"attachment"<<a<<"\n";
    }
  }
  if(doc->havePages()){
    MFCDocumentPages *pages=doc->pages();
    stream<<"[PAGES]\n";
    stream<<"count="<<pages->count()<<"\n";
    for(int p=0;p<pages->count();p++){
      MFCDocumentPage *page=pages->getPage(p);
      stream<<"name"<<p<<"="<<page->getPageName()<<"\n";
      stream<<"file"<<p<<"="<<"page"<<p<<".jpg\n";
    }
  }
  stream.flush();
  zipf.close();
  if(zipf.getZipError()!=UNZ_OK){
    errStr=tr("Ошибка при добавлении реквизитов в архив: ")+
              zipErrStr(zipf.getZipError());
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
      DocAttachment *att=atts->getAttachment(a);
#ifndef QT_NO_DEBUG
      qDebug()<<"Archiving doc attachment"<<tr("attachment")+att->fileName()<<
             "size ="<<att->device()->size();
#endif
      zinfo=QuaZipNewInfo(tr("attachment%1").arg(a));
      zinfo.internalAttr=0660;
      zinfo.externalAttr=0660;
      if(!zipf.open(QIODevice::WriteOnly,
                    QuaZipNewInfo(zinfo))){
        errStr=tr("Ошибка при добавлении вложения в архив: ")+
                  zipErrStr(zipf.getZipError());
        return false;
      }
      zipf.write(att->data());
      zipf.close();
      if(zipf.getZipError()!=UNZ_OK){
        errStr=tr("Ошибка при добавлении вложения в архив: ")+
                  zipErrStr(zipf.getZipError());
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
        errStr=tr("Ошибка при добавлении страницы %1 в архив: ").arg(p+1)+
                  zipErrStr(zipf.getZipError());
        return false;
      }
      page->device()->seek(0);
      QImageReader ir(page->device());
      if(ir.format().toUpper()!="JPG" || ir.format().toUpper()!="JPEG"){
        QBuffer buf;
        QImage im;
        im=ir.read();
        if(im.isNull()){
          errStr=tr("Ошибка при обработке страницы %1: %2").arg(p+1).arg(ir.errorString());
          return false;
        }
        buf.open(QBuffer::ReadWrite);
        im.save(&buf,"JPG");
        zipf.write(buf.buffer());
      }else zipf.write(page->getBody());
      zipf.close();
      if(zipf.getZipError()!=UNZ_OK){
        errStr=tr("Ошибка при добавлении страницы %1 в архив: ").arg(p+1)+
                  zipErrStr(zipf.getZipError());
        return false;
      }
//      emit dataTransferProgress(p+1,pages->count(),tr("Обработка: %p%"));
      emit dataTransferProgress(p+1,pages->count(),doc);
      qApp->processEvents();
    }
  }
  ///////////////////////////////////////////////////////// сохраним страницы //

  zip.close();

  return true;
}

bool FtpDocsStorage::loadZip(QString fileName, MFCDocument *doc){
  if(fileName.isEmpty() || !doc) return false;
  // обрабатываем архив и создаём MFCDocument
  QuaZipFile zip(fileName,"requisites.ini");
  if(!zip.open(QIODevice::ReadOnly)){
    setError(tr("Ошибка при чтении архива: ")+zipErrStr(zip.getZipError()));
    return false;
  }
  QTemporaryFile reqFile("temp/requisites.ini");
  if(!reqFile.open()){
    setError(tr("Ошибка при создании временного файла реквизитов: ")+
              reqFile.errorString());
    return false;
  }
  reqFile.write(zip.readAll());
  zip.close();
  reqFile.seek(0);
  QSettings requisites(reqFile.fileName(),QSettings::IniFormat);
  requisites.setIniCodec("UTF-8");
  if(requisites.value("FORMAT/version","0").toString()!="1.0"){
    setError(tr("Не совместимый формат документа %1. Требуется 1.0").arg(
                requisites.value("FORMAT/version","0").toString()));
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
            fileName,
            requisites.value(tr("ATTACHMENTS/file%1").arg(a)).toString());
      if(!zip.open(QIODevice::ReadOnly)){
        setError(tr("Ошибка при чтении архива: ")+zipErrStr(zip.getZipError()));
        return false;
      }
      DocAttachment *att=new DocAttachment(
            requisites.value(tr("ATTACHMENTS/filename%1").arg(a)).toString(),
            requisites.value(tr("ATTACHMENTS/mimetype%1").arg(a)).toString(),
            zip.readAll());
      doc->addAttachment(*att);
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
            fileName,
            requisites.value(tr("PAGES/file%1").arg(a)).toString());
      if(!zip.open(QIODevice::ReadOnly)){
        setError(tr("Ошибка при чтении архива: ")+zipErrStr(zip.getZipError()));
        return false;
      }
      MFCDocumentPage *page=new MFCDocumentPage(
            requisites.value(tr("PAGES/name%1").arg(a)).toString(),
            zip.readAll());
      doc->addPage(*page);
      zip.close();
      emit dataTransferProgress(a+1,pageCount,doc);
    }
  }

#ifndef QT_NO_DEBUG
  qDebug()<<"document:"<<doc->name()<<doc->series()<<doc->number()<<doc->date()<<
         "- created";
#endif
  return true;
}

bool FtpDocsStorage::loadZip(QFile *file, MFCDocument *doc){
  if(!file) return false;
  if(file->isOpen()) file->close();
  return loadZip(file->fileName(),doc);
}

QString FtpDocsStorage::zipErrStr(int errn){
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

void FtpDocsStorage::putNextFile(){
  if(jobQueue.isEmpty() || !ftpEng->isAuthenticated()) return;
  arc=jobQueue.dequeue();
  ftpEng->beginCommands();
  setRoot();
  QString path=QDate::currentDate().toString("yyyy/MM/dd/");
  curPath=rootPath+path+QFileInfo(*arc).fileName();
  ftpEng->mkDir(path,true);
  if(!arc->isOpen()) arc->open(QFile::ReadOnly);
  ftpEng->putFile(QFileInfo(*arc).fileName(),arc);
  ftpEng->sendCommands();
}

void FtpDocsStorage::emitError(QString err,QString file,int line){
  errStr=tr("%1 (%2): %3").arg(file).arg(line).arg(err);
  emit error(errStr);
}

void FtpDocsStorage::ftpTransferProgress(qint64 done, qint64 total){
  emit dataTransferProgress(done*docsDone,total*docCount,curDoc);
}

void FtpDocsStorage::authenticationCompleted(bool res){
  if(!res){
    setError(tr("Ошибка подключения к серверу: %1").arg(ftpEng->lastError()));
    cancel();
    return;
  }

  if(isDownloading){
    isDownloading=true;
    ftpEng->beginCommands();
    QString path=QFileInfo(curPath).path();
    QString file=QFileInfo(curPath).fileName();
    ftpEng->cd(path);
    ftpEng->getFile(file,arc);
    ftpEng->sendCommands();
  }else{
    putNextFile();
  }
}

void FtpDocsStorage::ftpAnswer(FTPEngine::Command cmd, bool res){
  if(!res){
    if(cmd==FTPEngine::Command_GetFile){
      setError(tr("Ошибка загрузки: %1").arg(ftpEng->lastError()));
      cancel();
      return;
    }else if(cmd==FTPEngine::Command_PutFile){
      setError(tr("Ошибка сохранения: %1").arg(ftpEng->lastError()));
      cancel();
      return;
    }
  }

  if(cmd==FTPEngine::Command_GetFile){
    if(!curDoc) curDoc=new MFCDocument(this);
    if(!arc){
      arc=qobject_cast< QFile* >(ftpEng->buffer());
    }
    if(loadZip(arc,curDoc)) emit loaded(curDoc);
    if(arc){
      QString fileName=arc->fileName();
      arc->deleteLater();
      arc=NULL;
      QFile::remove(fileName);
    }
    isDownloading=false;
  }else if(cmd==FTPEngine::Command_PutFile){
    LogDebug()<<curPath<<arc;
    arc->remove();
    arc->deleteLater();
    arc=NULL;
    docsDone++;
    emit saved(curPath);
    putNextFile();
  }

  if(ftpEng && ftpEng->isFinished()){
    if(jobQueue.isEmpty()) cancel();
    else putNextFile();
  }
}

void FtpDocsStorage::ftpAnswer(QString text, int code){
  LogDebug()<<text;
  LogDebug()<<code;
}

bool FtpDocsStorage::save(MFCDocument *doc, QString declarNumber){
  // создаём архив и перемещаем его в хранилище
  curDoc=doc;
  QUuid uuid=QUuid::createUuid();
  QString arcName=tr("temp/")+declarNumber+"_"+
      uuid.toString().remove("{").remove("}")+".mdoc";

  if(!saveZip(doc,arcName)){
    emit error(errStr);
    return false;
  }

  curPath=rootPath+"/"+QDate::currentDate().toString("yyyy/MM/dd");
  curPath.replace("//","/");

  jobQueue.enqueue(new QFile(arcName));
  docCount=jobQueue.count();
  /// TODO: Check if file exists at the storage
  if(!ftpEng || !ftpEng->isConnected())
    connectToHost(userName,userPass,ftpHost,ftpPort);
  else if(ftpEng->isFinished()){
    putNextFile();
  }

  return true;
}

bool FtpDocsStorage::load(QString fileName){
//  if(!connected){
//    setError(tr("Необходимо подключение к ftp серверу"));
//    return false;
//  }
  if(fileName.isEmpty()){
    setError(tr("Необходимо указать имя файла"));
    return false;
  }
  if(isDownloading){
    setError(tr("Загрузка ещё в процессе. Необходимо дождаться её завершения"));
    return false;
  }
  if(ftpEng && !ftpEng->isFinished()){
    setError(tr("Сохранение ещё в процессе. Необходимо дождаться завершения"));
    return false;
  }

  QDir d=QDir();
  d.mkdir("temp");
  QTemporaryFile *dFile=new QTemporaryFile("temp/downloadedXXXXXX.zip",this);
//  dFile->setAutoRemove(false);
  if(!dFile->open()){
    setError(tr("Ошибка создания временного файла: %1").arg(
                dFile->errorString()));
    return false;
  }
  arc=dFile;
//  ftpBrowser->getFile(fileName,dFile);
  curPath=fileName;
  isDownloading=true;
  if(!ftpEng || !ftpEng->isConnected())
    connectToHost(userName,userPass,ftpHost,ftpPort);
  else{
    ftpEng->beginCommands();
    QString path=QFileInfo(curPath).path();
    QString file=QFileInfo(curPath).fileName();
    ftpEng->cd(path);
    ftpEng->getFile(file,arc);
    ftpEng->sendCommands();
  }

  return true;
}

bool FtpDocsStorage::load(QString fileName, MFCDocument *doc){
  if(doc==NULL) return false;
  if(isDownloading){
    setError(tr("Загрузка ещё в процессе. Необходимо дождаться её завершения"));
    return false;
  }

  curDoc=doc;
  return load(fileName);
}

void FtpDocsStorage::cancel(){
//  ftpBrowser->cancelDownload();
  if(ftpEng){
    ftpEng->deleteLater();
    ftpEng=NULL;
  }
  if(arc){
//    arc->remove();
    QString fileName=arc->fileName();
    arc->deleteLater();
    arc=NULL;
    QFile::remove(fileName);
  }
  while(!jobQueue.isEmpty()){
    QFile *file=jobQueue.dequeue();
    file->remove();
    file->deleteLater();
  }
  docsDone=1;
  docCount=1;
  isDownloading=false;
}
