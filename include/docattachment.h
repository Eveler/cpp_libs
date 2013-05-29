#ifndef DOCATTACHMENT_H
#define DOCATTACHMENT_H

#include <QString>
#include <QByteArray>
#include <QTemporaryFile>

class DocAttachment
{
public:
  DocAttachment(const QString fileName,const QString mimeType,
                const QByteArray &fileData);
  ~DocAttachment();
  QString fileName();
  QString mimeType();
  QByteArray data();
  QIODevice *device();
  bool isValid();

private:
  QString fName;
  QString mType;
  QTemporaryFile *m_File;

  void initFile();
};

#endif // DOCATTACHMENT_H
