#include "clientprivatesystem.h"

#include <QtGlobal>


ClientPrivateSystem *ClientPrivateSystem::m__Instance = NULL;

ClientPrivateSystem * ClientPrivateSystem::instace()
{
  if ( m__Instance == NULL ) m__Instance = new ClientPrivateSystem;

  return m__Instance;
}

void ClientPrivateSystem::setAssessmentLoader( AssessmentLoader *loader )
{
  m__AssessmentLoader = loader;
}

AssessmentLoader *ClientPrivateSystem::assessmentLoader() const
{
  return m__AssessmentLoader;
}

void ClientPrivateSystem::setAssessmenttypeLoader( AssessmenttypeLoader *loader )
{
  m__AssessmenttypeLoader = loader;
}

AssessmenttypeLoader *ClientPrivateSystem::assessmenttypeLoader() const
{
  return m__AssessmenttypeLoader;
}

void ClientPrivateSystem::setCallstatusLoader( CallstatusLoader *loader )
{
  m__CallStatusLoader = loader;
}

CallstatusLoader *ClientPrivateSystem::callStatusLoader() const
{
  return m__CallStatusLoader;
}

void ClientPrivateSystem::setClientLoader( ClientLoader *loader )
{
  m__ClientLoader = loader;
}

ClientLoader * ClientPrivateSystem::clientLoader() const
{
  return m__ClientLoader;
}

void ClientPrivateSystem::setDeclarLoader( DeclarLoader *loader )
{
  m__DeclarLoader = loader;
}

DeclarLoader * ClientPrivateSystem::declarLoader() const
{
  return m__DeclarLoader;
}

void ClientPrivateSystem::setDeclarClientLoader( DeclarClientLoader *loader )
{
  m__DeclarClientLoader = loader;
}

DeclarClientLoader * ClientPrivateSystem::declarClientLoader() const
{
  return m__DeclarClientLoader;
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

void ClientPrivateSystem::setOrganisationLoader( OrganisationLoader *loader )
{
  m__OrganisationLoader = loader;
}

OrganisationLoader * ClientPrivateSystem::organisationLoader() const
{
  return m__OrganisationLoader;
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

void ClientPrivateSystem::setResultLoader( ResultLoader *loader )
{
  m__ResultLoader = loader;
}

ResultLoader * ClientPrivateSystem::resultLoader() const
{
  return m__ResultLoader;
}

void ClientPrivateSystem::setResultwayLoader( ResultwayLoader *loader )
{
  m__ResultwayLoader = loader;
}

ResultwayLoader * ClientPrivateSystem::resultwayLoader() const
{
  return m__ResultwayLoader;
}

void ClientPrivateSystem::setServiceLoader( ServiceLoader *loader )
{
  m__ServiceLoader = loader;
}

ServiceLoader * ClientPrivateSystem::serviceLoader() const
{
  return m__ServiceLoader;
}

void ClientPrivateSystem::setTrusteeLoader( TrusteeLoader *loader )
{
  m__TrusteeLoader = loader;
}

TrusteeLoader * ClientPrivateSystem::trusteeLoader() const
{
  return m__TrusteeLoader;
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
