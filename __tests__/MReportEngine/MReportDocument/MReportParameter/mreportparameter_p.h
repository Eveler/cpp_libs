#ifndef MREPORTPARAMETER_P_H
#define MREPORTPARAMETER_P_H

#include <QObject>

#include "mreportparameter.h"
#include "QVariant"


class MReportParameter_P : public QObject
{
  Q_OBJECT
  friend class MReportParameter;


public:
  explicit MReportParameter_P( const QString &name, MReportParameter *parent );

signals:

public slots:


private:
  QString m__Name;
  MReportParameter::ParameterType m__PT;
  MReportParameter::DataType m__DT;
  QString m__DataSource;
  QVariant m__Data;
  QListIterator<QVariant> m__DataIterator;

  MReportParameter * p_dptr() const;
};

#endif // MREPORTPARAMETER_P_H
