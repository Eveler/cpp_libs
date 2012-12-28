#ifndef FILEINFO_H
#define FILEINFO_H

#include "ftpengine_export.h"

#include <QString>
#include <QDateTime>

class FTPENGINE_EXPORT FileInfo
{
public:
  FileInfo();
  ~FileInfo();

  void reset();

  void setFileName( QString fileName );
  void setIsFile( bool isFile );
  void setIsSymLink( bool isSymLink );
  void setOwner( QString owner );
  void setGroup( QString group );
  void setSize( qlonglong size );
  void setLastModified( QDateTime lastModified );
  void setPermissions( int permissions );
  void setReadable( bool readable );
  void setWritable( bool writable );

  const QString & fileName() const;
  bool isFile() const;
  bool isSymLink() const;
  const QString & owner() const;
  const QString & group() const;
  const qlonglong & size() const;
  const QDateTime & lastModified() const;
  int permissions() const;
  bool readable() const;
  bool writable() const;

private:
  QString m__FileName;
  bool m__IsFile;
  bool m__IsSymLink;
  QString m__Owner;
  QString m__Group;
  qlonglong m__Size;
  QDateTime m__LastModified;
  int m__Permissions;
  bool m__Readable;
  bool m__Writable;
};

#endif // FILEINFO_H
