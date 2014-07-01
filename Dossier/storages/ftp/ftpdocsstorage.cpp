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

  dbName=dataBaseName;
  rootPath="/";
  curDoc=NULL;
  docCount=1;
  docsDone=1;
  isDownloading=false;
  ftpPort=21;
  ftpEng=NULL;
  arc=NULL;
  loop = new QEventLoop( this );
}

FtpDocsStorage::~FtpDocsStorage(){
//  LogDebug()<<"~FtpDocsStorage() BEGIN";
//  if(ftpEng) ftpEng->deleteLater();
  cancel();
//  LogDebug()<<"~FtpDocsStorage() END";
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
//  LogDebug()<<Q_FUNC_INFO<<"BEGIN: param1 ="<<uName<<"param2 ="<<pass<<"param3 ="<<host<<"param4 ="<<port;
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
  bool res=ftpEng->connectToHost(url,ftpPort);
  if(!res){
    setError(tr("Ошибка соединения: %1").arg(ftpEng->lastError()));
    return res;
  }

//  setRoot();
//  LogDebug()<<Q_FUNC_INFO<<"END";
  return ( loop->exec() == 0 );
}

void FtpDocsStorage::setRoot(const QString dataBaseName, const QString path){
#ifndef QT_NO_DEBUG
  qDebug()<<"path:"<<path<<"dbName"<<dbName;
#endif
  rootPath="/"+path+"/"+(dbName!=dataBaseName?dataBaseName:dbName);
  rootPath.replace("//","/");
  ftpEng->cd("/"+path+"/"+(dbName!=dataBaseName?dataBaseName:dbName));
}

QString FtpDocsStorage::errorString(){
  return errStr;
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
  LogDebug()<<errStr;
  emit error(errStr);
}

void FtpDocsStorage::ftpTransferProgress(qint64 done, qint64 total){
  emit dataTransferProgress(done*docsDone,total*docCount,curDoc);
}

void FtpDocsStorage::authenticationCompleted(bool res){
  if(!res){
    loop->exit( -1 );
    setError(tr("Ошибка подключения к серверу: %1").arg(ftpEng->lastError()));
    cancel();
    return;
  }
  else loop->exit();

  if(isDownloading){
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
    isDownloading=false;
  }

  if(cmd==FTPEngine::Command_GetFile){
    if(!curDoc){
      curDoc=MFCDocumentInfo::instance(
            QString(),QString(),QString(),QString(),QDate(),QDate(),QString(),
               QDateTime(),QString(),QDateTime(),this);
//      curDoc->setProperty("created_in",tr("%1 (%2)").arg(__FILE__).arg(__LINE__));
    }
    if(!arc){
      arc=qobject_cast< QFile* >(ftpEng->buffer());
    }
    curDoc->setLocalFile( QFileInfo( arc->fileName() ).absoluteFilePath() );
    delete arc;
    arc=NULL;
    emit loaded(curDoc);
//      QString fileName=arc->fileName();
//      arc->deleteLater();
    isDownloading=false;
  }else if(cmd==FTPEngine::Command_PutFile){
    arc->remove();
//    arc->deleteLater();
    delete arc;
    arc=NULL;
    docsDone++;
    emit saved(curPath);
    putNextFile();
  }

  if(ftpEng && ftpEng->isFinished()){
    if(jobQueue.isEmpty())
    {
      if(ftpEng){
    //    ftpEng->deleteLater();
        delete ftpEng;
        ftpEng=NULL;
      }
      docsDone=1;
      docCount=1;
      isDownloading=false;
      loop->exit();
    }
    else putNextFile();
  }
}

void FtpDocsStorage::ftpAnswer(QString text, int code){
  LogDebug()<<tr("ftpAnswer: %1 (%2)").arg(text).arg(code);
}

bool FtpDocsStorage::save(MFCDocumentInfo *doc, QString declarNumber){
  QFileInfo fi( doc->localFile() );
  if( !fi.exists() )
  {
    setError(tr( "Файла документа [%1] не существует!" ).arg( doc->localFile() ));
    return false;
  }
  curDoc=doc;

  QString arcName = tr( "%1/%2_%3" ).arg( fi.absolutePath(), declarNumber, fi.fileName() );
  QFile::rename( fi.absoluteFilePath(), arcName );
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

bool FtpDocsStorage::load( MFCDocumentInfo *doc ){
//  if(!connected){
//    setError(tr("Необходимо подключение к ftp серверу"));
//    return false;
//  }
  if(doc==NULL) return false;
  QString fileName = doc->url();
  if(fileName.isEmpty()){
    return true;
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
  QFile *dFile=new QFile( "temp/"+QFileInfo( fileName ).fileName(), this );
//  dFile->setAutoRemove(false);
  if(!dFile->open( QFile::ReadWrite )){
    setError(tr("Ошибка создания файла: %1").arg(
                dFile->errorString()));
    return false;
  }
  curDoc=doc;
  arc=dFile;
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

void FtpDocsStorage::cancel(){
//  LogDebug()<<"cancel() BEGIN";
  if(ftpEng){
//    ftpEng->deleteLater();
    delete ftpEng;
    ftpEng=NULL;
  }
  if(arc){
//    arc->remove();
    QString fileName=arc->fileName();
//    arc->deleteLater();
    delete arc;
    arc=NULL;
    QFile::remove(fileName);
  }
  while(!jobQueue.isEmpty()){
    QFile *file=jobQueue.dequeue();
    file->remove();
//    file->deleteLater();
    delete file;
  }
  docsDone=1;
  docCount=1;
  isDownloading=false;
//  LogDebug()<<"cancel() END";
}
