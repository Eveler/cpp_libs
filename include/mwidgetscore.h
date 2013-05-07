#ifndef MWIDGETSCORE_H
#define MWIDGETSCORE_H

#include <QObject>

#include "export/mwidgets_export_lib.h"


class QAction;
class QMenu;

class EXPORT_MWIDGETS MWidgetsCore : public QObject
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
