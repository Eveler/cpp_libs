#include "ftpcommandspool.h"

FTPCommandsPool::FTPCommandsPool( FTPCommand *mainCommand ) :
  m__Commands(QList<FTPCommand *>()),
  m__CurrentIndex(-1),
  m__MainIndex(0)
{
  m__Commands << mainCommand;
}

FTPCommandsPool::~FTPCommandsPool()
{
  while ( !m__Commands.isEmpty() )
  {
    FTPCommand *command = m__Commands.takeFirst();
    delete command;
  }
}

bool FTPCommandsPool::hasNextCommand() const
{
  return ( m__CurrentIndex < m__Commands.count()-1 );
}

bool FTPCommandsPool::nextCommand()
{
  m__CurrentIndex++;
  if ( m__CurrentIndex >= m__Commands.count() )
  {
    m__CurrentIndex = m__Commands.count();
    return false;
  }

  return true;
}

bool FTPCommandsPool::isValidCommand() const
{
  return ( m__CurrentIndex > -1 && m__CurrentIndex < m__Commands.count() );
}

bool FTPCommandsPool::isFinished() const
{
  return ( m__CurrentIndex == m__Commands.count() );
}

FTPCommand * FTPCommandsPool::currentCommand() const
{
  return m__Commands.value( m__CurrentIndex, NULL );
}

FTPCommand * FTPCommandsPool::mainCommand() const
{
  return m__Commands.value( m__MainIndex, NULL );
}

void FTPCommandsPool::appendAfter( FTPCommand *command )
{
  m__Commands << command;
}

void FTPCommandsPool::appendBefore( FTPCommand *command )
{
  m__Commands.insert( m__MainIndex, command );
  m__MainIndex++;
}
