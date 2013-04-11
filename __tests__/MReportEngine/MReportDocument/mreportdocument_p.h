#ifndef MREPORTDOCUMENT_P_H
#define MREPORTDOCUMENT_P_H

#include <QObject>


class MReportDocument;

class MReportDocument_P : public QObject
{
  Q_OBJECT
  friend class MReportDocument;


public:
  explicit MReportDocument_P( MReportDocument *parent );


signals:

public slots:


private:
  QString m__LastError;

  MReportDocument * p_dptr() const;
};

#endif // MREPORTDOCUMENT_P_H
