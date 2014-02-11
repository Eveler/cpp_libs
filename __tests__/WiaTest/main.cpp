#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include "amslogger.h"

int main(int argc, char *argv[])
{
  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  AMSLogger::setLogLevel(AMSLogger::LevelCritical |AMSLogger::LevelDebug
                         | AMSLogger::LevelFatal | AMSLogger::LevelWarn);

  return a.exec();
}
