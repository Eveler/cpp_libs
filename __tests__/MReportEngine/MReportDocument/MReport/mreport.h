#ifndef MREPORT_H
#define MREPORT_H

#include <QObject>
#include <QtGlobal>
#include <QDomNode>


class MReportDocument;

class MReport
{
public:
  static MReportDocument * load( const QString &filePath, QString *errorStr, QObject *parent );
  static MReportDocument * create( const QString &alias , const QString &dirPath, QObject *parent );
  static bool save( MReportDocument *reportDocument );


private:
  static void load( MReportDocument *reportDocument );

  static void addError( const QString &error, QStringList &errors );
  static QString parse( const QByteArray &data, MReportDocument *reportDocument );
  static QString sources( const QDomNode &tag, MReportDocument *reportDocument );
  static QString parameters( const QDomNode &tag, MReportDocument *reportDocument );
  static QString keys( const QDomNode &tag, MReportDocument *reportDocument );
};

#endif // MREPORT_H
