#include "makcdataset_plugin.h"

#include "makcdataset.h"

#include <QQmlEngine>
#include <QQmlContext>


using namespace MAKCDataset;

void MAKCDatasetPlugin::initializeEngine( QQmlEngine *engine, const char *uri )
{
  Q_UNUSED(uri)
  initializeMAKC( engine );
  QQmlContext *context = engine->rootContext();

  context->setContextProperty( "MAKCDatabase", MAKC_Database() );
  context->setContextProperty( "MAKCClientHumans", MAKC_ClientDataSource() );
  context->setContextProperty( "MAKCOrgHumans", MAKC_OrgDataSource() );
}

void MAKCDatasetPlugin::registerTypes( const char *uri )
{
  // @uri extensions.mihail.makcdataset
  qmlRegisterType<MObjectModel>( uri, 1, 0, "MObjectModel" );
  qmlRegisterType<MDataSourceModel>( uri, 1, 0, "MDataSourceModel" );
  qmlRegisterUncreatableType<SafelyValue>( uri, 1, 0, "SafelyValue", "" );

  qmlRegisterUncreatableType<MDocument>( uri, 1, 0, "MDocument", "" );
  qmlRegisterUncreatableType<MHuman>( uri, 1, 0, "MHuman", "" );
}


