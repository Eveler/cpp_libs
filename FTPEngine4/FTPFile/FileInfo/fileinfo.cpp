#include "fileinfo.h"

FileInfo::FileInfo()
{
  reset();
}

FileInfo::~FileInfo()
{
  reset();
}

void FileInfo::reset()
{
  setFileName( QString() );
  setIsFile( false );
  setIsSymLink( false );
  setOwner( QString() );
  setGroup( QString() );
  setSize( -1 );
  setLastModified( QDateTime() );
  setPermissions( -1 );
  setReadable( false );
  setWritable( false );
}

void FileInfo::setFileName( QString fileName )
{
  m__FileName = fileName;
}

void FileInfo::setIsFile( bool isFile )
{
  m__IsFile = isFile;
}

void FileInfo::setIsSymLink( bool isSymlink )
{
  m__IsSymLink = isSymlink;
}

void FileInfo::setOwner( QString owner )
{
  m__Owner = owner;
}

void FileInfo::setGroup( QString group )
{
  m__Group = group;
}

void FileInfo::setSize( qlonglong size )
{
  m__Size = size;
}

void FileInfo::setLastModified( QDateTime lastModified )
{
  m__LastModified = lastModified;
}

void FileInfo::setPermissions( int permissions )
{
  m__Permissions = permissions;
}

void FileInfo::setReadable( bool readable )
{
  m__Readable = readable;
}

void FileInfo::setWritable( bool writable )
{
  m__Writable = writable;
}

const QString & FileInfo::fileName() const
{
  return m__FileName;
}

bool FileInfo::isFile() const
{
  return m__IsFile;
}

bool FileInfo::isSymLink() const
{
  return m__IsSymLink;
}

const QString & FileInfo::owner() const
{
  return m__Owner;
}

const QString & FileInfo::group() const
{
  return m__Group;
}

const qlonglong & FileInfo::size() const
{
  return m__Size;
}

const QDateTime & FileInfo::lastModified() const
{
  return m__LastModified;
}

int FileInfo::permissions() const
{
  return m__Permissions;
}

bool FileInfo::readable() const
{
  return m__Readable;
}

bool FileInfo::writable() const
{
  return m__Writable;
}

