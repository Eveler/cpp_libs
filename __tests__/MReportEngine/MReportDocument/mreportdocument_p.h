#ifndef MREPORTDOCUMENT_P_H
#define MREPORTDOCUMENT_P_H

#include <QObject>

#include "mreportdocument.h"


class MReportDocument_P : public QObject
{
  Q_OBJECT
  friend class MReportDocument;


public:


signals:

public slots:


private:
  QString m__FileName;

  MReportDocument *m__ParentDocument;
  MReportDocumentList m__ChildDocuments;

  QList<MReportParameter *> m__Parameters;

  QString m__LastError;

  explicit MReportDocument_P( const QString &fileName, MReportDocument *parent );
  ~MReportDocument_P();

  QString filePath() const;
  QString alias() const;

  MReportDocument * p_dptr() const;
};

#endif // MREPORTDOCUMENT_P_H
