#include "makcdataset_plugin.h"

#include "mdatabase.h"
#include "mhumandatasource.h"
#include "mhumandbwrapper.h"

#include <QQmlEngine>
#include <QQmlContext>


void MAKCDatasetPlugin::initializeEngine( QQmlEngine *engine, const char *uri )
{
  Q_UNUSED(uri)
  QQmlContext *context = engine->rootContext();
  context->setContextProperty( "MDatabase", new MDatabase );
  context->setContextProperty( "DSHumans", new MHumanDataSource );
}

void MAKCDatasetPlugin::registerTypes( const char *uri )
{
  // @uri extensions.mihail.makcdataset
  qmlRegisterType<MObjectModel>( uri, 1, 0, "MObjectModel" );
  qmlRegisterType<MDataSourceModel>( uri, 1, 0, "MDataSourceModel" );
  qmlRegisterUncreatableType<SafelyValue>( uri, 1, 0, "SafelyValue", "" );

  qmlRegisterType<MHuman>( uri, 1, 0, "MHuman" );
}


