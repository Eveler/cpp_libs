#ifndef FTPCOMMAND_H
#define FTPCOMMAND_H

#include <QString>

class FTPCommand
{
public:
  enum Type {Type_Noop = 0, Type_User, Type_Pass, Type_Type,
             Type_Pwd, Type_Cdup, Type_Cwd, Type_List, Type_Mkd,
             Type_Rmd, Type_Retr, Type_Stor, Type_Port, Type_Quit};

  static QString name( Type type );

  static bool canAdd( Type type, const QString &arg1 );

  FTPCommand( Type type, const QString &arg1 = QString(), bool automatically = false );

  Type type() const;
  const QString & name() const;
  const QString & argument() const;
  bool isAutomatically() const;

private:
  Type m__Type;
  QString m__Name;
  QString m__Argument;
  bool m__Automatically;
};

#endif // FTPCOMMAND_H
