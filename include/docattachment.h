#ifndef DOCATTACHMENT_H
#define DOCATTACHMENT_H

#include "export/dossier_export.h"

#include <QString>
#include <QByteArray>
#include <QTemporaryFile>


class DOSSIER_EXPORT DocAttachment
{
public:
  DocAttachment(const QString fileName,const QString mimeType,
                const QByteArray &fileData);
  ~DocAttachment();
  QString fileName() const;
  QString mimeType() const;
  QByteArray data() const;
  QIODevice *device() const;
  bool isValid();

private:
  QString fName;
  QString mType;
  QTemporaryFile *m_File;

  void initFile();
};

#endif // DOCATTACHMENT_H
