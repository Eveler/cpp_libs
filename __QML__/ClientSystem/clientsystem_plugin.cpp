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
#include "service/service.h"
#include "service/servicelist.h"
#include "service/serviceloader.h"
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

  /// About services
  ServiceLoader *serviceLoader = new ServiceLoader;
  p->setServiceLoader( serviceLoader );
  context->setContextProperty( "ServiceLoader", serviceLoader );
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

  /// About services
  qmlRegisterType<Service>( uri, 1, 0, "Service" );
  qmlRegisterType<ServiceList>( uri, 1, 0, "ServiceList" );
}

