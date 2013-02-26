#ifndef FTPCOMMANDSPOOL_H
#define FTPCOMMANDSPOOL_H

#include "ftpcommand.h"

#include <QList>

class FTPCommandsPool
{
public:
  FTPCommandsPool( FTPCommand *mainCommand );
  ~FTPCommandsPool();

  bool hasNextCommand() const;
  bool nextCommand();
  bool isValidCommand() const;
  bool isFinished() const;
  FTPCommand * currentCommand() const;
  FTPCommand * mainCommand() const;

  void appendAfter( FTPCommand *command );
  void appendBefore( FTPCommand *command );

private:
  QList<FTPCommand *> m__Commands;
  int m__CurrentIndex;
  int m__MainIndex;
};

#endif // FTPCOMMANDSPOOL_H
