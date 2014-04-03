#include "makcdataset_plugin.h"

#include "makcdataset.h"
#include "msortmodel.h"

#include <QQmlEngine>
#include <QQmlContext>


using namespace MAKCDataset;

void MAKCDatasetPlugin::initializeEngine( QQmlEngine *engine, const char *uri )
{
  Q_UNUSED(uri)
  initializeMAKC( engine );
  QQmlContext *context = engine->rootContext();

  context->setContextProperty( "MAKCDatabase", MDatabase::instance( engine ) );
  context->setContextProperty( "MAKCDoctypes", MAKC_DoctypeDataSource() );
  context->setContextProperty( "MAKCDocuments", MAKC_DocumentDataSource() );
  context->setContextProperty( "MAKCClientHumans", MAKC_HumanDataSource() );
  context->setContextProperty( "MAKCClientOrgs", MAKC_OrgDataSource() );
  context->setContextProperty( "MAKCProcedures", MAKC_ProcedureDataSource() );
  context->setContextProperty( "MAKCRecipients", MAKC_RecipientDataSource() );
  context->setContextProperty( "MAKCDepartments", MAKC_DepartmentDataSource() );
  context->setContextProperty( "MAKCDirections", MAKC_DirectionDataSource() );
}

void MAKCDatasetPlugin::registerTypes( const char *uri )
{
  // @uri extensions.mihail.makcdataset
  qmlRegisterType<MObjectModel>( uri, 1, 0, "MObjectModel" );
  qmlRegisterType<MSortModel>( uri, 1, 0, "MSortModel" );
  qmlRegisterUncreatableType<MSortProperties>( uri, 1, 0, "MSortProperties", "" );

  qmlRegisterType<MDataSourceModel>( uri, 1, 0, "MDataSourceModel" );
  qmlRegisterUncreatableType<SafelyValue>( uri, 1, 0, "SafelyValue", "" );

  qmlRegisterUncreatableType<MDoctype>( uri, 1, 0, "MDoctype", "" );
  qmlRegisterUncreatableType<MDocument>( uri, 1, 0, "MDocument", "" );
  qmlRegisterUncreatableType<MHuman>( uri, 1, 0, "MHuman", "" );
  qmlRegisterUncreatableType<MOrganization>( uri, 1, 0, "MOrganization", "" );
  qmlRegisterUncreatableType<MProcedure>( uri, 1, 0, "MProcedure", "" );
  qmlRegisterUncreatableType<MRecipient>( uri, 1, 0, "MRecipient", "" );
  qmlRegisterUncreatableType<MDepartment>( uri, 1, 0, "MDepartment", "" );
  qmlRegisterUncreatableType<MDirection>( uri, 1, 0, "MDirection", "" );
}


