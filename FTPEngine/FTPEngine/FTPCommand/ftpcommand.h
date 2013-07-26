#ifndef FTPCOMMAND_H
#define FTPCOMMAND_H

#include <QString>

class FTPCommand
{
public:
  enum Type {Type_Noop = 0, Type_Help, Type_User, Type_Pass, Type_Type,
             Type_Pwd, Type_Cdup, Type_Cwd, Type_List, Type_Mkd, Type_Rmd, Type_Allo,
             Type_Size, Type_Retr, Type_Stor, Type_Dele, Type_Port, Type_Quit,
            Type_Pasv};

  static QString name( Type type );

  static bool canAdd( Type type, const QString &arg1 );

  FTPCommand();
  FTPCommand( Type type, const QString &arg1 = QString(), bool ignoreError = false );

  bool isValid() const;

  Type type() const;
  const QString & name() const;
  const QString & argument() const;
  bool ignoreError() const;

private:
  Type m__Type;
  QString m__Name;
  QString m__Argument;
  bool m__IgnoreError;
};

#endif // FTPCOMMAND_H
