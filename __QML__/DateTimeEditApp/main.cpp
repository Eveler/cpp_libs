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


int main(int argc, char *argv[])
{
  Application app(argc, argv);

  qApp->addLibraryPath( qApp->applicationDirPath() + "/plugins");
#ifdef Q_OS_WIN
  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#else
  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#endif

  QQmlApplicationEngine engine(QUrl( "qrc:/content/DateTimeEditApp.qml" ));

  QObject *topLevel = engine.rootObjects().value(0);

  QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
  if ( !window ) {
    qWarning("Error: Your root item has to be a Window.");
    return -1;
  }
  window->show();

  return app.exec();
}
