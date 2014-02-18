#include "mainwindow.h"
#include <QApplication>
#include "amslogger.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;

  AMSLogger::setLogLevel(AMSLogger::LevelCritical | AMSLogger::LevelDebug | AMSLogger::LevelFatal | AMSLogger::LevelWarn);

  w.show();

  return a.exec();
}
