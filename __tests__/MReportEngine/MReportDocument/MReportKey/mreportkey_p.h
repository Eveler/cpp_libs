#ifndef MREPORTKEY_P_H
#define MREPORTKEY_P_H

#include <QObject>

#include "mreportkey.h"


class MReportKey_P : public QObject
{
  Q_OBJECT
  friend class MReportKey;


public:


signals:


public slots:


private:
  QString m__Name;
  MReportKey::KeyType m__KT;
  MReportKey::DataType m__DT;
  QString m__Source;
  QString m__DataSource;

  explicit MReportKey_P( const QString &name, MReportKey *parent );

  MReportKey * p_dptr() const;
};

#endif // MREPORTKEY_P_H
