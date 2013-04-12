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
  static QString parse( const QByteArray &data, MReportDocument *reportDocument );
  static QString parameters( const QDomNode &tagParameters, MReportDocument *reportDocument );
};

#endif // MREPORTLOADER_H
