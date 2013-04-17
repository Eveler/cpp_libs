#ifndef MREPORTKEY_P_H
#define MREPORTKEY_P_H

#include <QObject>

#include "mreportkey.h"


class MReportKey_P : public QObject
{
  Q_OBJECT
  friend class MReportKey;


public:
  explicit MReportKey_P( const QString &name, MReportKey *parent );

signals:

public slots:


private:
  QString m__Name;
  MReportKey::KeyType m__KT;
  MReportKey::DataType m__DT;
  QString m__DataSource;

  MReportKey * p_dptr() const;
};

#endif // MREPORTKEY_P_H
