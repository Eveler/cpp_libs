#ifndef MWIDGETSCORE_H
#define MWIDGETSCORE_H

#include <QObject>

#include "lib_export.h"


class QAction;
class QMenu;

class EXPORT MWidgetsCore : public QObject
{
  Q_OBJECT


public:
  static QAction * createMenuTree( const QStringList &categories, QMenu *currentMenu );
  static void removeMenuTree( const QStringList &categories, QMenu *currentMenu );


signals:


public slots:


private:
};

#endif // MWIDGETSCORE_H
