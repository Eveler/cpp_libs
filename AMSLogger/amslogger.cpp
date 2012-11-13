#include "amslogger.h"
#include <QFileInfo>
#include <QDateTime>
#include <QDir>

bool AMSLogger::initialized=false;
int AMSLogger::loglevel=AMSLogger::LevelCritical;
QFile *AMSLogger::outFile=new QFile();
QtMsgHandler AMSLogger::oldMsgHandler=NULL;
int AMSLogger::rotateCount=7;

void AMSLogger::messageOutput(QtMsgType type, const char *msg){
//  if(!AMSLoggerInitialized) AMSLogger::initialyze();
  int len=strlen(msg);
  char* message=new char[len+14];
  memset(message,0,len+12);
  switch (type){
  case QtDebugMsg:
    strncpy(message,"Debug: ",8);
    strncat(message,msg,len);
    fprintf(stderr, "%s\n", message);
    if(AMSLogger::logLevel()<=AMSLogger::LevelDebug)
      if(outFile->fileName().length()>0) writeToFile(message);
    break;
  case QtWarningMsg:
    strncpy(message,"Warning: ",10);
    strncat(message,msg,len);
    fprintf(stderr, "%s\n", message);
    if(AMSLogger::logLevel()<=AMSLogger::LevelWarn)
      if(outFile->fileName().length()>0) writeToFile(message);
    break;
  case QtCriticalMsg:
    strncpy(message,"Critical: ",11);
    strncat(message,msg,len);
    fprintf(stderr, "%s\n", message);
    if(AMSLogger::logLevel()<=AMSLogger::LevelCritical)
      if(outFile->fileName().length()>0) writeToFile(message);
    break;
  case QtFatalMsg:
    strncpy(message,"Fatal: ",8);
    strncat(message,msg,len);
    fprintf(stderr, "%s\n", message);
    if(AMSLogger::logLevel()<=AMSLogger::LevelFatal)
      if(outFile->fileName().length()>0) writeToFile(message);
    abort();
  }
  delete[] message;
}

void AMSLogger::install(){
  QString completeBaseName=QFileInfo(
        qApp->applicationFilePath()).completeBaseName();
  QString prefix=qApp->applicationDirPath()+"/"+completeBaseName+
      "_logger/"+completeBaseName;
  QString logFile=prefix+".log";
  outFile->setFileName(logFile);
  //"вращение" либо отправка по почте журнала//////////////////////////////////
#warning Log email realization mis (отправка по почте не реализована)
  if(outFile->exists()){
    for(int i=rotateCount;i>0;i--){
      QFile::rename(prefix+"_"+QString::number(i)+".log",
                    prefix+"_"+QString::number(i+1)+".log");
    }
//    QFile::remove(prefix+"_"+QString::number(rotateCount+1)+".log");
    QString pref=prefix;
    pref.chop(completeBaseName.length());
    QDir d=QDir(pref);
    d.setNameFilters(QStringList()<<(completeBaseName+"_*.log"));
    QStringList filesList=d.entryList(QDir::Files,QDir::Name);
    foreach(QString file,filesList){
      QString f=file;
      if(f.remove(completeBaseName+"_").remove(".log").toInt()>rotateCount){
        QFile::remove(d.absolutePath()+"/"+file);
        qDebug()<<file<<"removed";
      }
    }
    outFile->rename(prefix+"_1.log");
    outFile->setFileName(prefix+".log");
  }
  qDebug()<<"AMSLogger: logfile name:"<<outFile->fileName();
  ////////////////////////////////////"вращение" либо отправка по почте журнала
  initialyze();
}

void AMSLogger::writeToFile(const char *msg){
  QDir d=QDir();
  d.mkpath(QFileInfo(*outFile).absolutePath());
  if(!outFile->open(QFile::Append | QFile::WriteOnly | QFile::Text)){
    fprintf(stderr, "Warning: Error openning log file %s\n",
            qPrintable(outFile->fileName()));
    outFile->close();
    return;
  }
  QTextStream out(outFile);
  out.setFieldAlignment(QTextStream::AlignLeft);
#ifdef Q_OS_WIN
  out.setCodec("Windows-1251");
//#else
//  out.setCodec("UTF-8");
#endif
  QString strDateTime=
      QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz: ");
//  outFile->write(qPrintable(strDateTime));
  out<<strDateTime;
//  outFile->write(msg);
  out<<qSetFieldWidth(55)<<QString(msg);
//  outFile->write("\n");
  out<<qSetFieldWidth(0)<<endl;
  out.flush();
  outFile->close();
}

void AMSLogger::initialyze(){
  loglevel=LevelCritical;
  oldMsgHandler=qInstallMsgHandler(messageOutput);
  initialized=true;
}
