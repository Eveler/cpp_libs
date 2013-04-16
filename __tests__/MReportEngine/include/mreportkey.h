#ifndef MREPORTKEY_H
#define MREPORTKEY_H

#include <QObject>

#include "export/mreport_engine_export.h"


class MReportKey_P;
class MReportDocument;

class EXPORT_MREPORTENGINE MReportKey : public QObject
{
  Q_OBJECT
  friend class MReportKey_P;
  friend class MReportDocument;


public:
  enum KeyType {KT_Undefined = -1, KT_PlainData,
                KT_ForeignParameter, KT_Attachment};
  enum DataType {DT_Undefined = -1, DT_Text,
                 DT_Date, DT_DatePeriod,
                 DT_DateTime, DT_Time};

  ~MReportKey();


signals:


public slots:


protected:
  void setParent( QObject *parent );


private:
  MReportKey_P *p;

  explicit MReportKey( const QString &name, MReportDocument *parent );
};

#endif // MREPORTKEY_H
