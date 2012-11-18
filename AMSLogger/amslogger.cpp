#include "amslogger.h"
#include <QFileInfo>
#include <QDateTime>
#include <QDir>
#include <QTextCodec>

bool AMSLogger::initialized=false;
bool AMSLogger::installed=false;
AMSLogger::LogLevels AMSLogger::loglevel=AMSLogger::LevelCritical;
QFile *AMSLogger::outFile=new QFile();
QtMsgHandler AMSLogger::oldMsgHandler=NULL;
int AMSLogger::rotateCount=14;

void AMSLogger::messageOutput(QtMsgType type, const char *msg){
  AMSLogger::initialyze();
  int len=strlen(msg);
  char* message=new char[len+14];
  memset(message,0,len+12);
  switch (type){
  case QtDebugMsg:
    strncpy(message,"Debug: ",8);
    strncat(message,msg,len);
    fprintf(stderr, "%s\n", message);
    if(AMSLogger::logLevel().testFlag(AMSLogger::LevelDebug))
      if(outFile->fileName().length()>0) writeToFile(message);
    break;
  case QtWarningMsg:
    strncpy(message,"Warning: ",10);
    strncat(message,msg,len);
    fprintf(stderr, "%s\n", message);
    if(AMSLogger::logLevel().testFlag(AMSLogger::LevelWarn))
      if(outFile->fileName().length()>0) writeToFile(message);
    break;
  case QtCriticalMsg:
    strncpy(message,"Critical: ",11);
    strncat(message,msg,len);
    fprintf(stderr, "%s\n", message);
    if(AMSLogger::logLevel().testFlag(AMSLogger::LevelCritical))
      if(outFile->fileName().length()>0) writeToFile(message);
    break;
  case QtFatalMsg:
    strncpy(message,"Fatal: ",8);
    strncat(message,msg,len);
    fprintf(stderr, "%s\n", message);
    if(AMSLogger::logLevel().testFlag(AMSLogger::LevelFatal))
      if(outFile->fileName().length()>0) writeToFile(message);
    abort();
  }
  delete[] message;
}

void AMSLogger::install(){
  initialyze();
  oldMsgHandler=qInstallMsgHandler(messageOutput);
  installed=true;
}

void AMSLogger::initialyze(){
  if(initialized) return;
//  loglevel=LevelCritical;
  QString logFile=prefix()+".log";
  outFile->setFileName(logFile);
  //"вращение" либо отправка по почте журнала//////////////////////////////////
#warning Log email realization mis (отправка по почте не реализована)
  rotate();
  qDebug()<<"AMSLogger: logfile name:"<<outFile->fileName();
  ////////////////////////////////////"вращение" либо отправка по почте журнала
  initialized=true;
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
//  QTextStream out(outFile);
//  out.setFieldAlignment(QTextStream::AlignLeft);
//#ifdef Q_OS_WIN
//  out.setCodec("Windows-1251");
////#else
////  out.setCodec("UTF-8");
//#endif
  QString strDateTime=
      QDateTime::currentDateTime().toString("[dd.MM.yyyy] [hh:mm:ss.zzz]: ");
  outFile->write(qPrintable(strDateTime));
//  out<<strDateTime;
  QTextCodec *cfcs=QTextCodec::codecForCStrings();
  if(cfcs){
    QString intenalMsg=cfcs->toUnicode(msg);
    QTextCodec *cfl=QTextCodec::codecForLocale();
    if(cfl) outFile->write(cfl->fromUnicode(intenalMsg));
    else outFile->write(msg);
  }else outFile->write(msg);
//  out<<qSetFieldWidth(55)<</*QString(*/msg/*)*/;
  outFile->write("\n");
//  out<<qSetFieldWidth(0)<<endl;
//  out.flush();
  outFile->close();
}

AMSLogger& AMSLogger::operator <<(const QVariant &msg){
  QString str;
  if(!msgFile.isEmpty()) str+=msgFile;
  if(msgLine>0 && !str.isEmpty()) str+=" ("+QVariant(msgLine).toString()+")";
  if(!str.isEmpty()) str+=": ";
  str+=msg.toString();
  messageOutput(msgType,qPrintable(str));
  return *this;
}

void AMSLogger::rotate(){
  if(outFile->fileName().isEmpty()) return;
  QString completeBN=completeBaseName();
  QString pfix=prefix();
  if(outFile->exists()){
    for(int i=rotateCount;i>0;i--){
      QFile::rename(pfix+"_"+QString::number(i)+".log",
                    pfix+"_"+QString::number(i+1)+".log");
    }
    QString pref=pfix;
    pref.chop(completeBN.length());
    QDir d=QDir(pref);
    d.setNameFilters(QStringList()<<(completeBN+"_*.log"));
    QStringList filesList=d.entryList(QDir::Files,QDir::Name);
    foreach(QString file,filesList){
      QString f=file;
      if(f.remove(completeBN+"_").remove(".log").toInt()>rotateCount){
        QFile::remove(d.absolutePath()+"/"+file);
        qDebug()<<file<<"removed";
      }
    }
    outFile->rename(pfix+"_1.log");
    outFile->setFileName(pfix+".log");
  }
}

QString AMSLogger::completeBaseName(){
  return QFileInfo(
        qApp->applicationFilePath()).completeBaseName();
}

QString AMSLogger::prefix(){
  QString completeBN=completeBaseName();
  return qApp->applicationDirPath()+"/"+completeBN+
      "_logger/"+completeBN;
}
