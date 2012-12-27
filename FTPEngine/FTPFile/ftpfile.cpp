#include "ftpfile.h"

FTPFile::FTPFile( QObject *parent ) :
  QObject(parent),
  m__File(new QTemporaryFile)
{
}

FTPFile::FTPFile( QTemporaryFile *otherFile, QObject *parent ) :
  QObject(parent)
{
  m__File = otherFile;
}

FTPFile::~FTPFile()
{
  if ( m__File->parent() == 0 ) delete m__File;
  m__File = NULL;
}

QTemporaryFile * FTPFile::file() const
{
  return m__File;
}
