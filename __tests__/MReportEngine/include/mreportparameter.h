#ifndef MREPORTPARAMETER_H
#define MREPORTPARAMETER_H

#include <QObject>

#include "export/mreport_engine_export.h"

#include <QVariant>


class MReportParameter;
class MReportParameter_P;
class MReportDocument;

typedef QList<MReportParameter *> MReportParameterList;

class EXPORT_MREPORTENGINE MReportParameter : public QObject
{
  Q_OBJECT
  friend class MReportParameter_P;
  friend class MReportDocument;


public:
  enum ParameterType {PT_Undefined = -1, PT_PlainData,
                      PT_InputData, PT_SQL, PT_Repeater,
                      PT_ForeignParameter, PT_ForeignKey};
  enum DataType {DT_Undefined = -1, DT_Date, DT_DatePeriod};

  ~MReportParameter();

  MReportDocument *reportDocument() const;

  const QString & name() const;

  void setParameterType( ParameterType parameterType );
  ParameterType parameterType() const;

  void setDataType( DataType dataType );
  DataType dataType() const;

  void setDataSource( const QString &dataSource );
  const QString & dataSource() const;

  bool setData( const QVariant &data );
  const QVariant & data() const;


signals:


public slots:


protected:
  void setParent( QObject *parent );


private:
  MReportParameter_P *p;

  explicit MReportParameter( const QString &name, MReportDocument *parent );

  bool hasNext() const;
  void next() const;
};

#endif // MREPORTPARAMETER_H
