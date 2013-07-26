#ifndef MFCDOCUMENTPAGE_H
#define MFCDOCUMENTPAGE_H

#include <QString>
#include <QByteArray>
#include <QTemporaryFile>
#include <QPixmap>
#include "export/dossier_export.h"

class DOSSIER_EXPORT MFCDocumentPage
{
public:
  MFCDocumentPage( QString pageName, const QByteArray &body );
  MFCDocumentPage( QString pageName, const QPixmap &pixmap);
  ~MFCDocumentPage();

  bool isValid();

  const QString & getPageName();
  QByteArray getBody();
  QIODevice *device();

private:
  QString *m_PageName;
  QTemporaryFile *m_File;

  void init(const QString pageName);
};

#endif // MFCDOCUMENTPAGE_H
