#include "ftpfile.h"

FTPFile::FTPFile( QString fileName, quint64 maxSize, QObject *parent ) :
  QObject(parent),
  m__File(new QTemporaryFile( fileName )),
  byDef(false),
  m__MaxSize(maxSize)
{
}

FTPFile::FTPFile( QTemporaryFile *otherFile, QObject *parent ) :
  QObject(parent),
  m__File(otherFile),
  byDef(true),
  m__MaxSize(0)
{
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

quint64 FTPFile::maxSize() const
{
  if ( byDef ) return m__File->size();
  else return m__MaxSize;
}
