#ifndef FTPFILE_H
#define FTPFILE_H

#include <QObject>

#include "ftpengine_export.h"

#include <QTemporaryFile>

class FTPENGINE_EXPORT FTPFile : public QObject
{
  Q_OBJECT
public:
  explicit FTPFile( QString fileName, qint64 maxSize, QObject *parent = 0 );
  explicit FTPFile( QTemporaryFile *otherFile, QObject *parent = 0 );
  ~FTPFile();

  QTemporaryFile * file() const;
  qint64 maxSize() const;

signals:

public slots:

private:
  QTemporaryFile *m__File;
  bool byDef;
  qint64 m__MaxSize;
};

#endif // FTPFILE_H
