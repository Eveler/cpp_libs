#ifndef MREPORTDOCUMENT_H
#define MREPORTDOCUMENT_H

#include <QObject>

#include <export/mreport_engine_export.h>


namespace MReport {
 class MReportDocument;
}

class MReportDocument_P;

class EXPORT_MREPORTENGINE MReportDocument : public QObject
{
  Q_OBJECT
  friend class MReportDocument_P;


public:
  explicit MReportDocument( const QString &fileName, QObject *parent = 0 );
  ~MReportDocument();

  const QString & lastError() const;


signals:


public slots:


private:
  MReportDocument_P *p;
};

#endif // MREPORTDOCUMENT_H
