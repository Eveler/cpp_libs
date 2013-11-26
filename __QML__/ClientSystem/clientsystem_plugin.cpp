#include "clientsystem_plugin.h"

#include "user/user.h"
#include "user/userlist.h"
#include "user/userloader.h"
/// ============================================================================
#include "procedure/procedure.h"
#include "procedure/procedurelist.h"
#include "procedure/procedureloader.h"
/// ============================================================================
#include "recipient/recipient.h"
#include "recipient/recipientlist.h"
#include "recipient/recipientloader.h"
/// ============================================================================
#include "department/department.h"
#include "department/departmentlist.h"
#include "department/departmentloader.h"
/// ============================================================================
#include "doctype/doctype.h"
#include "doctype/doctypelist.h"
#include "doctype/doctypeloader.h"
/// ============================================================================
#include "callstatus/callstatus.h"
#include "callstatus/callstatuslist.h"
#include "callstatus/callstatusloader.h"
/// ============================================================================
#include "human/human.h"
#include "human/humanlist.h"
#include "human/humanloader.h"
/// ============================================================================
#include "organisation/organisation.h"
#include "organisation/organisationlist.h"
#include "organisation/organisationloader.h"
/// ============================================================================
#include "client/client.h"
#include "client/clientlist.h"
#include "client/clientloader.h"
/// ============================================================================
#include "service/service.h"
#include "service/servicelist.h"
#include "service/serviceloader.h"
/// ============================================================================
#include "trustee/trustee.h"
#include "trustee/trusteelist.h"
#include "trustee/trusteeloader.h"
/// ============================================================================
#include "declarclient/declarclient.h"
#include "declarclient/declarclientlist.h"
#include "declarclient/declarclientloader.h"
/// ============================================================================
#include "declar/declar.h"
#include "declar/declarlist.h"
#include "declar/declarloader.h"
/// ============================================================================
#include "result/result.h"
#include "result/resultlist.h"
#include "result/resultloader.h"
/// ============================================================================
#include "resultway/resultway.h"
#include "resultway/resultwaylist.h"
#include "resultway/resultwayloader.h"
/// ============================================================================
#include "assessment/assessment.h"
#include "assessment/assessmentlist.h"
#include "assessment/assessmentloader.h"
/// ============================================================================
#include "assessmenttype/assessmenttype.h"
#include "assessmenttype/assessmenttypelist.h"
#include "assessmenttype/assessmenttypeloader.h"
/// ============================================================================
#include "clientprivatesystem.h"

#include <qqml.h>


void ClientSystemPlugin::initializeEngine( QQmlEngine *engine, const char *uri )
{
  Q_UNUSED(uri)
  ClientPrivateSystem *p = ClientPrivateSystem::instace();
  QQmlContext *context = engine->rootContext();

  /// About users
  UserLoader *userLoader = new UserLoader;
  p->setUserLoader( userLoader );
  context->setContextProperty( "UserLoader", userLoader );

  /// About procedures
  ProcedureLoader *procedureLoader = new ProcedureLoader;
  p->setProcedureLoader( procedureLoader );
  context->setContextProperty( "ProcedureLoader", procedureLoader );

  /// About recipients
  RecipientLoader *recipientLoader = new RecipientLoader;
  p->setRecipientLoader( recipientLoader );
  context->setContextProperty( "RecipientLoader", recipientLoader );

  /// About departments
  DepartmentLoader *departmentLoader = new DepartmentLoader;
  p->setDepartmentLoader( departmentLoader );
  context->setContextProperty( "DepartmentLoader", departmentLoader );

  /// About doctypes
  DoctypeLoader *doctypeLoader = new DoctypeLoader;
  p->setDoctypeLoader( doctypeLoader );
  context->setContextProperty( "DoctypeLoader", doctypeLoader );

  /// About callstatuses
  CallstatusLoader *callstatusLoader = new CallstatusLoader;
  p->setCallstatusLoader( callstatusLoader );
  context->setContextProperty( "CallstatusLoader", callstatusLoader );

  /// About humans
  HumanLoader *humanLoader = new HumanLoader;
  p->setHumanLoader( humanLoader );
  context->setContextProperty( "HumanLoader", humanLoader );

  /// About organisations
  OrganisationLoader *organisationLoader = new OrganisationLoader;
  p->setOrganisationLoader( organisationLoader );
  context->setContextProperty( "OrganisationLoader", organisationLoader );

  /// About clients
  ClientLoader *clientLoader = new ClientLoader;
  p->setClientLoader( clientLoader );
  context->setContextProperty( "ClientLoader", clientLoader );

  /// About services
  ServiceLoader *serviceLoader = new ServiceLoader;
  p->setServiceLoader( serviceLoader );
  context->setContextProperty( "ServiceLoader", serviceLoader );

  /// About trustees
  TrusteeLoader *trusteeLoader = new TrusteeLoader;
  p->setTrusteeLoader( trusteeLoader );
  context->setContextProperty( "TrusteeLoader", trusteeLoader );

  /// About declarclients
  DeclarClientLoader *declarClientLoader = new DeclarClientLoader;
  p->setDeclarClientLoader( declarClientLoader );
  context->setContextProperty( "DeclarClientLoader", declarClientLoader );

  /// About declars
  DeclarLoader *declarLoader = new DeclarLoader;
  p->setDeclarLoader( declarLoader );
  context->setContextProperty( "DeclarLoader", declarLoader );

  /// About results
  ResultLoader *resultLoader = new ResultLoader;
  p->setResultLoader( resultLoader );
  context->setContextProperty( "ResultLoader", resultLoader );

  /// About resultways
  ResultwayLoader *resultwayLoader = new ResultwayLoader;
  p->setResultwayLoader( resultwayLoader );
  context->setContextProperty( "ResultwayLoader", resultwayLoader );

  /// About assessments
  AssessmentLoader *assessmentLoader = new AssessmentLoader;
  p->setAssessmentLoader( assessmentLoader );
  context->setContextProperty( "AssessmentLoader", assessmentLoader );

  /// About assessmenttypes
  AssessmenttypeLoader *assessmenttypeLoader = new AssessmenttypeLoader;
  p->setAssessmenttypeLoader( assessmenttypeLoader );
  context->setContextProperty( "AssessmenttypeLoader", assessmenttypeLoader );
}

void ClientSystemPlugin::registerTypes(const char *uri)
{
  // @uri com.mihail.clientsystem

  /// About users
  qmlRegisterType<User>( uri, 1, 0, "User" );
  qmlRegisterType<UserList>( uri, 1, 0, "UserList" );

  /// About procedures
  qmlRegisterType<Procedure>( uri, 1, 0, "Procedure" );
  qmlRegisterType<ProcedureList>( uri, 1, 0, "ProcedureList" );

  /// About recipients
  qmlRegisterType<Recipient>( uri, 1, 0, "Recipient" );
  qmlRegisterType<RecipientList>( uri, 1, 0, "RecipientList" );

  /// About departments
  qmlRegisterType<Department>( uri, 1, 0, "Department" );
  qmlRegisterType<DepartmentList>( uri, 1, 0, "DepartmentList" );

  /// About doctypes
  qmlRegisterType<Doctype>( uri, 1, 0, "Doctype" );
  qmlRegisterType<DoctypeList>( uri, 1, 0, "DoctypeList" );

  /// About callstatuses
  qmlRegisterType<Callstatus>( uri, 1, 0, "Callstatus" );
  qmlRegisterType<CallstatusList>( uri, 1, 0, "CallstatusList" );

  /// About humans
  qmlRegisterType<Human>( uri, 1, 0, "Human" );
  qmlRegisterType<HumanList>( uri, 1, 0, "HumanList" );

  /// About organisations
  qmlRegisterType<Organisation>( uri, 1, 0, "Organisation" );
  qmlRegisterType<OrganisationList>( uri, 1, 0, "OrganisationList" );

  /// About clients
  qmlRegisterType<Client>( uri, 1, 0, "Client" );
  qmlRegisterType<ClientList>( uri, 1, 0, "ClientList" );

  /// About services
  qmlRegisterType<Service>( uri, 1, 0, "Service" );
  qmlRegisterType<ServiceList>( uri, 1, 0, "ServiceList" );

  /// About trustees
  qmlRegisterType<Trustee>( uri, 1, 0, "Trustee" );
  qmlRegisterType<TrusteeList>( uri, 1, 0, "TrusteeList" );

  /// About declarclients
  qmlRegisterType<DeclarClient>( uri, 1, 0, "DeclarClient" );
  qmlRegisterType<DeclarClientList>( uri, 1, 0, "DeclarClientList" );

  /// About declars
  qmlRegisterType<Declar>( uri, 1, 0, "Declar" );
  qmlRegisterType<DeclarList>( uri, 1, 0, "DeclarList" );

  /// About results
  qmlRegisterType<Result>( uri, 1, 0, "Result" );
  qmlRegisterType<ResultList>( uri, 1, 0, "ResultList" );

  /// About resultways
  qmlRegisterType<Resultway>( uri, 1, 0, "Resultway" );
  qmlRegisterType<ResultwayList>( uri, 1, 0, "ResultwayList" );

  /// About assessments
  qmlRegisterType<Assessment>( uri, 1, 0, "Assessment" );
  qmlRegisterType<AssessmentList>( uri, 1, 0, "AssessmentList" );

  /// About assessmenttypes
  qmlRegisterType<Assessmenttype>( uri, 1, 0, "Assessmenttype" );
  qmlRegisterType<AssessmenttypeList>( uri, 1, 0, "AssessmenttypeList" );
}

