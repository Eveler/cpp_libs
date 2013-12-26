#include "logreader.h"

#include <QFile>
#include <QTextStream>


LogReader::LogReader( QObject * parent ):
    QObject(parent)
{
}

LogReader::~LogReader()
{
}

QList<TreeItem *> LogReader::load( QString filePath ) const
{
  QList<TreeItem *> result;

  QFile f( filePath );
  QTextStream ts( &f );
  while ( !ts.atEnd() )
  {
    QString logLine = ts.readLine();
    QStringList buf = logLine.split( ": " );
    QString navigation = buf.first();
    buf.removeFirst();
    QString message = buf.join( ": " );
    buf = navigation.split( ";" );
  }

  return result;
}
