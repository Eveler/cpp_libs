#include "declarviewlib_plugin.h"
#include "singledeclar.h"

#include <qqml.h>

#include <QDebug>


void DeclarViewLibPlugin::registerTypes(const char *uri)
{
  // @uri com.mihail.declarviewlib
  qmlRegisterType<SingleDeclar>(uri, 1, 0, "SingleDeclar");
}


