#ifndef MREPORTSOURCE_P_H
#define MREPORTSOURCE_P_H

#include <QObject>

#include "mreportsource.h"
#include "mreportdocument.h"


class MReportSource_P : public QObject
{
  Q_OBJECT
  friend class MReportSource;


public:


signals:


public slots:


private:
  QString m__Name;

  MReportSource::SourceType m__ST;

  QString m__DriverName;
  QString m__Host;
  int m__Port;
  QString m__DbName;
  QString m__UserName;
  QString m__Password;

  explicit MReportSource_P( const QString &name, MReportSource *parent );

  MReportSource * p_dptr() const;
  MReportDocument * reportDocument() const;
};

#endif // MREPORTSOURCE_P_H
