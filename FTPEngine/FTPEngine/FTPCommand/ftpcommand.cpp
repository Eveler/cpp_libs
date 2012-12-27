#include "ftpcommand.h"

#include <QObject>

QString FTPCommand::name( Type type )
{
  switch ( type )
  {
  case Type_User:
    return QString( "user" );
  case Type_Pass:
    return QString( "pass" );
  case Type_Type:
    return QString( "type" );
  case Type_Pwd:
    return QString( "pwd" );
  case Type_Cdup:
    return QString( "cdup" );
  case Type_Cwd:
    return QString( "cwd" );
  case Type_List:
    return QString( "list" );
  case Type_Mkd:
    return QString( "mkd" );
  case Type_Rmd:
    return QString( "rmd" );
  case Type_Retr:
    return QString( "retr" );
  case Type_Stor:
    return QString( "stor" );
  case Type_Port:
    return QString( "port" );
  case Type_Quit:
    return QString( "quit" );
  }

  return QString();
}

bool FTPCommand::canAdd( Type type, const QString &arg1 )
{
  switch ( type )
  {
  case Type_User:
    return !arg1.isEmpty();
  case Type_Pass:
    return !arg1.isEmpty();
  case Type_Type:
    return !arg1.isEmpty();
  case Type_Cwd:
    return !arg1.isEmpty();
  case Type_Mkd:
    return !arg1.isEmpty();
  case Type_Rmd:
    return !arg1.isEmpty();
  case Type_Retr:
    return !arg1.isEmpty();
  case Type_Stor:
    return !arg1.isEmpty();
  case Type_Port:
    return !arg1.isEmpty();
  }

  return false;
}

FTPCommand::FTPCommand( Type type, const QString &arg1 ) :
  m__Type(type),
  m__Name(name(m__Type)),
  m__Argument(arg1)
{
}

FTPCommand::Type FTPCommand::type() const
{
  return m__Type;
}

const QString & FTPCommand::name() const
{
  return m__Name;
}

const QString & FTPCommand::argument() const
{
  return m__Argument;
}

