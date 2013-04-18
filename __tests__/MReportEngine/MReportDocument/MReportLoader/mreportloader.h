#ifndef MREPORTLOADER_H
#define MREPORTLOADER_H

#include "QtGlobal"
#include "QDomNode"


class MReportDocument;

class MReportLoader
{
public:
  static QString load( MReportDocument *reportDocument );


private:
  static void addError( const QString &error, QStringList &errors );
  static QString parse( const QByteArray &data, MReportDocument *reportDocument );
  static QString parameters( const QDomNode &tag, MReportDocument *reportDocument );
  static QString keys( const QDomNode &tag, MReportDocument *reportDocument );
};

#endif // MREPORTLOADER_H
