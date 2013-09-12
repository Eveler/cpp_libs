#include <QtQml>
#include <QtQuick/QQuickView>
#include <QtCore/QString>

#ifndef QT_NO_WIDGETS
#include <QtWidgets/QApplication>
#else
#include <QtGui/QGuiApplication>
#endif

#ifndef QT_NO_WIDGETS
#define Application QApplication
#else
#define Application QGuiApplication
#endif

#include <QTextCodec>
#include <QSqlDatabase>


int main(int argc, char *argv[])
{
  Application app(argc, argv);

  qApp->addLibraryPath( qApp->applicationDirPath() + "/plugins");
#ifdef Q_OS_WIN
  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#else
  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#endif

  QSqlDatabase db = QSqlDatabase::addDatabase( QObject::tr( "QPSQL" ) );
  db.setHostName( QObject::tr( "192.168.91.60" ) );
  db.setPort( 5432 );
  db.setDatabaseName( QObject::tr( "MFCs" ) );
  db.setUserName( QObject::tr( "mihail" ) );
  db.setPassword( QObject::tr( "me2db4con" ) );

  QQmlApplicationEngine engine(QUrl( "qrc:/main.qml" ));

  QObject *topLevel = engine.rootObjects().value(0);

  QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
  if ( !window ) {
    qWarning("Error: Your root item has to be a Window.");
    return -1;
  }
  window->show();

  return app.exec();
}

