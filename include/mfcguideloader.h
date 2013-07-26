#ifndef MFCGUIDELOADER_H
#define MFCGUIDELOADER_H

#include <QtCore>

#include "export/mfcguideloader_export_lib.h"


class Direction;
class Post;

class EXPORT_MFCGUIDELOADER MFCGuideLoader
{
public:
  static bool setConnectionName(QString connectionName );
  static QString connectionName();

  static Direction * loadDirection( int id, QString *error = NULL );

  static Post * loadPost( int id, QString *error = NULL );


private:
  static QString m__ConnectionName;
};

#endif // MFCGUIDELOADER_H
