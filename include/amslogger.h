#ifndef AMSLOGGER_H
#define AMSLOGGER_H

#include <QSettings>
#include <QObject>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include "smtp.h"

/** \brief Выводит сообщения, передаваемые при помощи qDebug(), qWarning() и т.д.
  либо прямых вызов методов данного класса на консоль и/или файл. При выводе в
файл может "вращать" журналы
\author Савенко М.Ю.*/
class AMSLogger/*:QObject*/ {
//  Q_OBJECT
public:
  /** Уровень журналирования. По умолчания LevelCritical - ошибки
\see setLogLevel() \see logLevel()*/
  enum LogLevel {LevelDebug=0,LevelWarn,LevelCritical,LevelFatal};
  Q_DECLARE_FLAGS(LogLevels,LogLevel)
  Q_FLAGS(LogLevels)
  Q_CORE_EXPORT_INLINE AMSLogger():msgFile(),msgLine(0){
    initialyze();
  }
  Q_CORE_EXPORT_INLINE AMSLogger(QtMsgType type,QString &file,int line){
    initialyze();
    msgType=type;
    oldMsgType=-1;
    msgFile=file;
    msgLine=line;
  }
  ~AMSLogger(){messageOutput(msgType,"\n");}
  /** Выводит сообщение \param msg и записывает его в файл журнала в зависимости от
 установленного уровня на основании типа сообщения \param type.
\see setLogLevel()*/
  Q_CORE_EXPORT_INLINE static void messageOutput(QtMsgType type, const char *msg);
  /** Устанавливает обработчик сообщений, уровень журналирования в LevelCritical
 и имя файла журнала в
\bold qApp->applicationDirPath()+"/"+QFileInfo(qApp->applicationFilePath()).completeBaseName()+".log"
и "вращает" его \see uninstall()*/
  static void install();
  /** Возвращает системный обработчик сообщений \see install()*/
  static void uninstall(){
    qInstallMsgHandler(oldMsgHandler);
  }
  /** Устанавливает уровень журналирования в LevelCritical и имя файла журнала в
\bold qApp->applicationDirPath()+"/"+QFileInfo(qApp->applicationFilePath()).completeBaseName()+".log"
и "вращает" его*/
  static void initialyze();
  /** Записывает сообщение msg в файл журнала*/
  Q_CORE_EXPORT_INLINE static void writeToFile(const QByteArray &msg);
  /** Устанавливает уровень журналирования в файл в \param level \see logLevel()*/
  static void setLogLevel(LogLevels level){
    loglevel=level;
  }
  /** Устанавливает количество хранимых файлов журнала при "вращении"*/
  static void setRotateCount(const int count){
    rotateCount=count;
  }
  /** Возвращает уровень журналирования в файл*/
  static LogLevels logLevel(){
    return loglevel;
  }
  /** Возвращает установлен ли AMSLogger в качестве обработчика QDebug*/
  static bool isInstalled(){
    return installed;
  }
  /** Выводит сообщение \param msg и записывает его в файл журнала в зависимости от
  установленного уровня на основании типа сообщения \param type.
  \see setLogLevel()*/
  AMSLogger& operator <<(const QVariant& msg);


private:
  static void rotate();
  static QString completeBaseName();
  static QString prefix();

  static bool initialized;
  static bool installed;
  static LogLevels loglevel;
  static QFile *outFile;
  static QtMsgHandler oldMsgHandler;
  static QTextStream stream;
  static int oldMsgType;

  Smtp *smtp;
  static int rotateCount;
  QtMsgType msgType;
  QString msgFile;
  int msgLine;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(AMSLogger::LogLevels)

Q_CORE_EXPORT_INLINE AMSLogger logDebug(QString file,int line) {
  return AMSLogger(QtDebugMsg,file,line);
}
Q_CORE_EXPORT_INLINE AMSLogger logWarning(QString file,int line) {
  return AMSLogger(QtWarningMsg,file,line);
}
Q_CORE_EXPORT_INLINE AMSLogger logCritical(QString file,int line) {
  return AMSLogger(QtCriticalMsg,file,line);
}
Q_CORE_EXPORT_INLINE AMSLogger logFatal(QString file,int line) {
  return AMSLogger(QtFatalMsg,file,line);
}
#define LogFatal() logFatal(__FILE__,__LINE__)
#define LogCritical() logCritical(__FILE__,__LINE__)
#define LogWarning() logWarning(__FILE__,__LINE__)
#define LogDebug() logDebug(__FILE__,__LINE__)

#endif // AMSLOGGER_H
