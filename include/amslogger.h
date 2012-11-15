#ifndef AMSLOGGER_H
#define AMSLOGGER_H

#include <QSettings>
#include <QObject>
#include <QFile>
#include <QCoreApplication>
#include "smtp.h"

/** \brief Выводит сообщения, передаваемые припомощи qDebug(), qWarning() и т.д.
  либо прямых вызов методов данного класса на консоль и/или файл. При выводе в
файл может "вращать" журналы
\author Савенко М.Ю.*/
class AMSLogger:QObject {
  Q_OBJECT
public:
  /** Уровень журналирования. По умолчания LevelCritical - ошибки*/
  enum LogLevel {LevelDebug=0,LevelWarn,LevelCritical,LevelFatal};
  AMSLogger(){
    initialyze();
  }
  static void messageOutput(QtMsgType type, const char *msg);
  /** Устанавливает обработчик сообщений, уровень журналирования в LevelCritical
 и имя файла журнала в
\bold qApp->applicationDirPath()+"/"+QFileInfo(qApp->applicationFilePath()).completeBaseName()+".log"
и "вращает" его*/
  static void install();
  /** Возвращает системный обработчик сообщений*/
  static void uninstall(){
    qInstallMsgHandler(oldMsgHandler);
  }
  /** Записывает сообщение msg в файл журнала*/
  static void writeToFile(const char *msg);
  static void setLogLevel(LogLevel level){
    loglevel=level;
  }
  /** Устанавливает количество хранимых файлов журнала при "вращении"*/
  static void setRotateCount(const int count){
    rotateCount=count;
  }
  /** Возвращает уровень журналирования в файл*/
  static int logLevel(){
    return loglevel;
  }
  /** Возвращает установлен ли AMSLogger в качестве обработчика QDebug*/
  static bool isInstalled(){
    return initialized;
  }

private:
  /** Устанавливает обработчик сообщений и уровень журналирования в LevelCritical*/
  static void initialyze();

  static bool initialized;
  static int loglevel;
  static QFile *outFile;
  static QtMsgHandler oldMsgHandler;

  Smtp *smtp;
  static int rotateCount;
};

#endif // AMSLOGGER_H
