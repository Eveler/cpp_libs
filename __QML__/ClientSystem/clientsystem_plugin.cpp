#include "clientsystem_plugin.h"

#include "user/userinfo.h"
#include "user/userloader.h"
/// ============================================================================
#include "procedure/procedureinfo.h"
#include "procedure/procedureloader.h"
/// ============================================================================
#include "recipient/recipientinfo.h"
#include "recipient/recipientloader.h"
/// ============================================================================
#include "department/departmentinfo.h"
#include "department/departmentloader.h"
/// ============================================================================
#include "doctype/doctypeinfo.h"
#include "doctype/doctypeloader.h"
/// ============================================================================
#include "callstatus/callstatusinfo.h"
#include "callstatus/callstatusloader.h"
/// ============================================================================
#include "human/humaninfo.h"
#include "human/humanloader.h"
/// ============================================================================
#include "organisation/organisationinfo.h"
#include "organisation/organisationloader.h"
/// ============================================================================
#include "client/clientinfo.h"
#include "client/clientloader.h"
/// ============================================================================
#include "service/serviceinfo.h"
#include "service/serviceloader.h"
/// ============================================================================
#include "trustee/trusteeinfo.h"
#include "trustee/trusteeloader.h"
/// ============================================================================
#include "declarclient/declarclientinfo.h"
#include "declarclient/declarclientloader.h"
/// ============================================================================
#include "declar/declarinfo.h"
#include "declar/declarloader.h"
/// ============================================================================
#include "result/resultinfo.h"
#include "result/resultloader.h"
/// ============================================================================
#include "resultway/resultwayinfo.h"
#include "resultway/resultwayloader.h"
/// ============================================================================
#include "assessment/assessmentinfo.h"
#include "assessment/assessmentloader.h"
/// ============================================================================
#include "assessmenttype/assessmenttypeinfo.h"
#include "assessmenttype/assessmenttypeloader.h"
/// ============================================================================
#include "clientprivatesystem.h"

#include <qqml.h>


void ClientSystemPlugin::initializeEngine( QQmlEngine *engine, const char *uri )
{
  Q_UNUSED(uri);
  ClientPrivateSystem *p = ClientPrivateSystem::instace();
  QQmlContext *context = engine->rootContext();
  Q_UNUSED(context);
}

void ClientSystemPlugin::registerTypes(const char *uri)
{
  // @uri com.mihail.clientsystem

  /// About users
  qmlRegisterType<UserInfo>( uri, 1, 0, "UserInfo" );
  qmlRegisterType<UserLoader>( uri, 1, 0, "UserLoader" );

  /// About procedures
  qmlRegisterType<ProcedureInfo>( uri, 1, 0, "ProcedureInfo" );
  qmlRegisterType<ProcedureLoader>( uri, 1, 0, "ProcedureLoader" );

  /// About recipients
  qmlRegisterType<RecipientInfo>( uri, 1, 0, "RecipientInfo" );
  qmlRegisterType<RecipientLoader>( uri, 1, 0, "RecipientLoader" );

  /// About departments
  qmlRegisterType<DepartmentInfo>( uri, 1, 0, "DepartmentInfo" );
  qmlRegisterType<DepartmentLoader>( uri, 1, 0, "DepartmentLoader" );

  /// About doctypes
  qmlRegisterType<DoctypeInfo>( uri, 1, 0, "DoctypeInfo" );
  qmlRegisterType<DoctypeLoader>( uri, 1, 0, "DoctypeLoader" );

  /// About callstatuses
  qmlRegisterType<CallstatusInfo>( uri, 1, 0, "CallstatusInfo" );
  qmlRegisterType<CallstatusLoader>( uri, 1, 0, "CallstatusLoader" );

  /// About humans
  qmlRegisterType<HumanInfo>( uri, 1, 0, "HumanInfo" );
  qmlRegisterType<HumanLoader>( uri, 1, 0, "HumanLoader" );

  /// About organisations
  qmlRegisterType<OrganisationInfo>( uri, 1, 0, "OrganisationInfo" );
  qmlRegisterType<OrganisationLoader>( uri, 1, 0, "OrganisationLoader" );

  /// About clients
  qmlRegisterType<ClientInfo>( uri, 1, 0, "ClientInfo" );
  qmlRegisterType<ClientLoader>( uri, 1, 0, "ClientLoader" );

  /// About services
  qmlRegisterType<ServiceInfo>( uri, 1, 0, "ServiceInfo" );
  qmlRegisterType<ServiceLoader>( uri, 1, 0, "ServiceLoader" );

  /// About trustees
  qmlRegisterType<TrusteeInfo>( uri, 1, 0, "TrusteeInfo" );
  qmlRegisterType<TrusteeLoader>( uri, 1, 0, "TrusteeLoader" );

  /// About declarclients
  qmlRegisterType<DeclarClientInfo>( uri, 1, 0, "DeclarClientInfo" );
  qmlRegisterType<DeclarClientLoader>( uri, 1, 0, "DeclarClientLoader" );

  /// About declars
  qmlRegisterType<DeclarInfo>( uri, 1, 0, "DeclarInfo" );
  qmlRegisterType<DeclarLoader>( uri, 1, 0, "DeclarLoader" );

  /// About results
  qmlRegisterType<ResultInfo>( uri, 1, 0, "ResultInfo" );
  qmlRegisterType<ResultLoader>( uri, 1, 0, "ResultLoader" );

  /// About resultways
  qmlRegisterType<ResultwayInfo>( uri, 1, 0, "ResultwayInfo" );
  qmlRegisterType<ResultwayLoader>( uri, 1, 0, "ResultwayLoader" );

  /// About assessments
  qmlRegisterType<AssessmentInfo>( uri, 1, 0, "AssessmentInfo" );
  qmlRegisterType<AssessmentLoader>( uri, 1, 0, "AssessmentLoader" );

  /// About assessmenttypes
  qmlRegisterType<AssessmenttypeInfo>( uri, 1, 0, "AssessmenttypeInfo" );
  qmlRegisterType<AssessmenttypeLoader>( uri, 1, 0, "AssessmenttypeLoader" );
}

