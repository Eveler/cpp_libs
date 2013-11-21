#include "clientprivatesystem.h"

#include <QtGlobal>


ClientPrivateSystem *ClientPrivateSystem::m__Instance = NULL;

ClientPrivateSystem * ClientPrivateSystem::instace()
{
  if ( m__Instance == NULL ) m__Instance = new ClientPrivateSystem;

  return m__Instance;
}

void ClientPrivateSystem::setCallstatusLoader( CallstatusLoader *loader )
{
  m__CallStatusLoader = loader;
}

CallstatusLoader *ClientPrivateSystem::callStatusLoader() const
{
  return m__CallStatusLoader;
}

void ClientPrivateSystem::setDepartmentLoader( DepartmentLoader *loader )
{
  m__DepartmentLoader = loader;
}

DepartmentLoader * ClientPrivateSystem::departmentLoader() const
{
  return m__DepartmentLoader;
}

void ClientPrivateSystem::setDoctypeLoader( DoctypeLoader *loader )
{
  m__DoctypeLoader = loader;
}

DoctypeLoader * ClientPrivateSystem::doctypeLoader() const
{
  return m__DoctypeLoader;
}

void ClientPrivateSystem::setHumanLoader( HumanLoader *loader )
{
  m__HumanLoader = loader;
}

HumanLoader * ClientPrivateSystem::humanLoader() const
{
  return m__HumanLoader;
}

void ClientPrivateSystem::setProcedureLoader( ProcedureLoader *loader )
{
  m__ProcedureLoader = loader;
}

ProcedureLoader * ClientPrivateSystem::procedureLoader() const
{
  return m__ProcedureLoader;
}

void ClientPrivateSystem::setRecipientLoader( RecipientLoader *loader )
{
  m__RecipientLoader = loader;
}

RecipientLoader * ClientPrivateSystem::recipientLoader() const
{
  return m__RecipientLoader;
}

void ClientPrivateSystem::setUserLoader( UserLoader *loader )
{
  m__UserLoader = loader;
}

UserLoader * ClientPrivateSystem::userLoader() const
{
  return m__UserLoader;
}

ClientPrivateSystem::ClientPrivateSystem()
{
}
