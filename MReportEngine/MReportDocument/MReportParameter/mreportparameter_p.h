#ifndef MREPORTPARAMETER_P_H
#define MREPORTPARAMETER_P_H

#include <QObject>

#include "mreportparameter.h"


class MReportParameter_P : public QObject
{
  Q_OBJECT
  friend class MReportParameter;


public:


signals:


public slots:


private:
  QString m__Name;
  MReportParameter::ParameterType m__PT;
  MReportParameter::DataType m__DT;
  QString m__DialogTitle;
  QString m__DialogText;
  QString m__Source;
  QString m__DataSource;
  QVariant m__Data;
  QListIterator<QVariant> m__DataIterator;
  int m__ListIndex;
  int m__Count;

  QList<MReportParameter *> m__ParameterExecuted;

  explicit MReportParameter_P( const QString &name, MReportParameter *parent );

  MReportParameter * p_dptr() const;
};

#endif // MREPORTPARAMETER_P_H
