#ifndef MREPORTPARAMETER_H
#define MREPORTPARAMETER_H

#include <QObject>

#include "export/mreport_engine_export.h"


class MReportParameter_P;
class MReportDocument;

class EXPORT_MREPORTENGINE MReportParameter : public QObject
{
  Q_OBJECT
  friend class MReportParameter_P;
  friend class MReportDocument;


public:
  ~MReportParameter();

  MReportDocument *reportDocument() const;

  const QString & name() const;


signals:


public slots:


protected:
  void setParent( QObject *parent );


private:
  MReportParameter_P *p;

  explicit MReportParameter( const QString &name, MReportDocument *parent );
};

#endif // MREPORTPARAMETER_H
