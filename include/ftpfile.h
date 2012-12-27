#ifndef FTPFILE_H
#define FTPFILE_H

#include <QObject>

#include <QTemporaryFile>

class FTPFile : public QObject
{
  Q_OBJECT
public:
  explicit FTPFile( QObject *parent = 0 );
  explicit FTPFile( QTemporaryFile *otherFile, QObject *parent = 0 );
  ~FTPFile();

  QTemporaryFile * file() const;

signals:

public slots:

private:
  QTemporaryFile *m__File;
};

#endif // FTPFILE_H
