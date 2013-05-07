#ifndef MREPORTKEY_H
#define MREPORTKEY_H

#include <QObject>

#include "export/mreport_engine_export.h"

#include <QVariant>


class MReportKey;
class MReportKey_P;
class MReportDocument;

typedef QList<MReportKey *> MReportKeyList;

class EXPORT_MREPORTENGINE MReportKey : public QObject
{
  Q_OBJECT
  friend class MReportKey_P;
  friend class MReportDocument;


public:
  enum KeyType {KT_Undefined = -1, KT_Parameter,
                KT_SQL, KT_SQLWithParameters, KT_Attachment};
  enum DataType {DT_Undefined = -1, DT_String, DT_StringList,
                 DT_Date, DT_DateTime, DT_Time,
                 DT_Integer, DT_Double};

  ~MReportKey();

  MReportDocument *reportDocument() const;

  const QString & name() const;

  void setKeyType( KeyType keyType );
  KeyType keyType() const;

  void setDataType( DataType dataType );
  DataType dataType() const;

  void setSource( const QString &source );
  const QString & source() const;

  void setDataSource( const QString &dataSource );
  const QString & dataSource() const;

  QString data() const;


signals:


public slots:


protected:
  void setParent( QObject *parent );


private:
  MReportKey_P *p;

  explicit MReportKey( const QString &name, MReportDocument *parent );
};

#endif // MREPORTKEY_H
