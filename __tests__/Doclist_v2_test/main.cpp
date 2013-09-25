#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
#ifdef Q_OS_WIN
  /*QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));
  QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));
  QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));*/
  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#if QT_VERSION < 0x050000
  QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
  QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif
#else
  /*QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
  QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));
  QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));*/
  QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
  QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif
  MainWindow w;
  w.show();

  return a.exec();
}
