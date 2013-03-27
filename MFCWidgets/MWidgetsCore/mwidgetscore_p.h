#ifndef MWIDGETSCORE_P_H
#define MWIDGETSCORE_P_H

#include <QStringList>


class MWidgetsCore;
class QAction;
class QMenu;

class MWidgetsCore_P
{
  friend class MWidgetsCore;

private:
  static QAction * createMenuTree( const QStringList &categories, int index, QMenu *currentMenu );
  static void removeMenuTree( const QStringList &categories, int index, QMenu *currentMenu );
};

#endif // MWIDGETSCORE_P_H
