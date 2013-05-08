#include "amslogger.h"
#include <QFileInfo>
#include <QDir>
#include <QTextCodec>

bool AMSLogger::initialized=false;
bool AMSLogger::installed=false;
bool AMSLogger::space=true;
AMSLogger::LogLevels AMSLogger::loglevel=
    AMSLogger::LevelCritical | AMSLogger::LevelFatal;
QFile *AMSLogger::outFile=new QFile();
#if QT_VERSION >= 0x050000
QtMessageHandler AMSLogger::oldMsgHandler=NULL;
#else
QtMsgHandler AMSLogger::oldMsgHandler=NULL;
#endif
int AMSLogger::rotateCount=14;
QTextStream AMSLogger::stream(stderr);
int AMSLogger::oldMsgType=-1;

void AMSLogger::install(){
  initialyze();
#if QT_VERSION >= 0x050000
  oldMsgHandler=qInstallMessageHandler(messageOutput);
#else
  oldMsgHandler=qInstallMsgHandler(messageOutput);
#endif
  installed=true;
}

void AMSLogger::initialyze(){
  space=true;
  if(initialized) return;
//  loglevel=LevelCritical;
  QString logFile=prefix()+".log";
  outFile->setFileName(logFile);
  //"вращение" либо отправка по почте журнала//////////////////////////////////
  rotate();
  fprintf(stdout, "AMSLogger: logfile name: %s", qPrintable( outFile->fileName() ) );
  ////////////////////////////////////"вращение" либо отправка по почте журнала
  initialized=true;
}

void AMSLogger::writeToFile(const QByteArray &msg){
  QDir d=QDir();
  d.mkpath(QFileInfo(*outFile).absolutePath());
  if(!outFile->open(QFile::Append | QFile::WriteOnly | QFile::Text)){
    fprintf(stderr, "Warning: Error openning log file %s\n",
            qPrintable(outFile->fileName()));
    outFile->close();
    return;
  }

  QTextCodec *cfcs=QTextCodec::codecForUtfText(msg,QTextCodec::codecForLocale());
  if(cfcs){
    QString intenalMsg=cfcs->toUnicode(msg);
    QTextCodec *cfl=QTextCodec::codecForLocale();
    if(cfl && cfl->canEncode(intenalMsg))
      outFile->write(cfl->fromUnicode(intenalMsg));
    else outFile->write(msg);
  }else outFile->write(msg);

  outFile->close();
}

AMSLogger& AMSLogger::operator <<(const QVariant &msg){
  QString str;
  if(oldMsgType!=msgType){
    if(!msgFile.isEmpty()) str+=msgFile;
    if(msgLine>0 && !str.isEmpty()) str+=" ("+QVariant(msgLine).toString()+")";
    if(!str.isEmpty()) str+=": ";
  }
  str+=msg.toString();
#if QT_VERSION >= 0x050000
  QMessageLogContext c;
  messageOutput(msgType,c,qPrintable(str));
#else
  messageOutput(msgType,qPrintable(str));
#endif
  return maybeSpace();
}

AMSLogger& AMSLogger::operator <<(const void * ptr){
  QString str;
  QTextStream ts(&str);
  ts<<ptr;
  return (*this)<<str;
}

AMSLogger& AMSLogger::operator <<(const char *ptr){
  QString str(ptr);
  return (*this)<<str;
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

AMSLOGGER_EXPORT AMSLogger logDebug(QString file,int line) {
  return AMSLogger(QtDebugMsg,file,line);
}
AMSLOGGER_EXPORT AMSLogger logWarning(QString file,int line) {
  return AMSLogger(QtWarningMsg,file,line);
}
AMSLOGGER_EXPORT AMSLogger logCritical(QString file,int line) {
  return AMSLogger(QtCriticalMsg,file,line);
}
AMSLOGGER_EXPORT AMSLogger logFatal(QString file,int line) {
  return AMSLogger(QtFatalMsg,file,line);
}
