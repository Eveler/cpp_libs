#include "mwidgetscore.h"

#include "mwidgetscore_p.h"


QAction * MWidgetsCore::createMenuTree( const QStringList &categories, QMenu *currentMenu )
{
  return MWidgetsCore_P::createMenuTree( categories, 0, currentMenu );
}

void MWidgetsCore::removeMenuTree( const QStringList &categories, QMenu *currentMenu )
{
  MWidgetsCore_P::removeMenuTree( categories, 0, currentMenu );
}
