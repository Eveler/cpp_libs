#include "mwidgetscore_p.h"

#include <QMenu>


QAction * MWidgetsCore_P::createMenuTree( const QStringList &categories, int index, QMenu *currentMenu )
{
  QAction *result = NULL;

  QString categoryName = categories[index];
  if ( index+1 == categories.count() )
  {
    bool canAdd = true;
    foreach ( QAction *action, currentMenu->actions() )
      if ( action->text() == categoryName ) canAdd = false;
    if ( canAdd ) result = currentMenu->addAction( categoryName );
  }
  else
  {
    QMenu *menu = NULL;
    foreach ( QAction *action, currentMenu->actions() )
      if ( action->text() == categoryName ) menu = action->menu();
    if ( menu == NULL ) menu = currentMenu->addMenu( categoryName );
    result = createMenuTree( categories, index+1, menu );
  }

  return result;
}

void MWidgetsCore_P::removeMenuTree( const QStringList &categories, int index, QMenu *currentMenu )
{
  QString categoryName = categories[index];
  if ( index+1 == categories.count() )
  {
    foreach ( QAction *action, currentMenu->actions() )
      if ( action->text() == categoryName )
      {
        currentMenu->removeAction( action );
        delete action;
        action = NULL;
      }
  }
  else
    foreach ( QAction *action, currentMenu->actions() )
      if ( action->text() == categoryName )
      {
        removeMenuTree( categories, index+1, action->menu() );
        if ( action->menu()->actions().count() == 0 )
        {
          currentMenu->removeAction( action );
          delete action;
          action = NULL;
        }
      }
}
