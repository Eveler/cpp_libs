#ifndef MREPORTSOURCE_H
#define MREPORTSOURCE_H

#include <QObject>

#include "export/mreport_engine_export.h"

#include <QVariant>
#include <QStringList>


class MReportSource;
class MReportSource_P;
class MReportDocument;

typedef QList<MReportSource *> MReportSourceList;

class EXPORT_MREPORTENGINE MReportSource : public QObject
{
  Q_OBJECT
  friend class MReportSource_P;
  friend class MReportDocument;


public:
  enum SourceType {ST_Undefined = -1, ST_SQL};

  ~MReportSource();

  const QString & name() const;

  void setSourceType( SourceType sourceType );
  SourceType sourceType() const;

  bool setDriverName( const QString & driverName );
  const QString & driverName() const;

  bool setHost( const QString & host );
  const QString & host() const;

  bool setPort( int port );
  int port() const;

  bool setDatabaseName( const QString & databaseName );
  const QString & databaseName() const;

  bool isValid() const;

  bool setUserName( const QString & userName );
  const QString & userName() const;

  void setPassword( const QString & password );
  const QString & password() const;

  void setUserList( const QStringList & userList );
  const QStringList & userList() const;

  bool check() const;

  QVariant executeQuery( const QString &query );


signals:


public slots:


protected:
  void setParent( QObject *parent );


private:
  MReportSource_P *p;

  explicit MReportSource( const QString &name, MReportDocument *parent );
};

#endif // MREPORTSOURCE_H
