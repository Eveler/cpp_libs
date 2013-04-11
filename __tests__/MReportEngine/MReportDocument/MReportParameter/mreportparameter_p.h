#ifndef MREPORTPARAMETER_P_H
#define MREPORTPARAMETER_P_H

#include <QObject>

#include "mreportparameter.h"


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

  MReportParameter * p_dptr() const;
};

#endif // MREPORTPARAMETER_P_H
