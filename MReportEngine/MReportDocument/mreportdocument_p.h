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
  QString m__Body;

  MReportDocument *m__ParentDocument;
  MReportDocumentList m__ChildDocuments;

  MReportSourceList m__Sources;
  MReportParameterList m__Parameters;
  MReportKeyList m__Keys;

  QHash<MReportDocument *, MReportKey *> m__DocumentKey;

  QString m__LastError;

  double m__BufProgress;
  double m__Progress;
  int m__Units;

  explicit MReportDocument_P( const QString &fileName, MReportDocument *parent );
  ~MReportDocument_P();

  QString filePath() const;
  QString alias() const;

  MReportDocument * p_dptr() const;

  void increaseProgressValue( double progress = 10000. );
};

#endif // MREPORTDOCUMENT_P_H
