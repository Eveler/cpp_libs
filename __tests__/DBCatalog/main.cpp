#include "dbcatalog.h"
#include <QApplication>

#include "mfccore.h"

#include <QTextCodec>


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

  MFCCore::appSettings( QObject::tr( "%1.ini" ).arg( qAppName() ) );

  DBCatalog w;
  w.showMaximized();

  return a.exec();
}
