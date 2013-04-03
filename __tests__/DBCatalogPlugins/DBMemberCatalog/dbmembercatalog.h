#ifndef DBMEMBERCATALOG_H
#define DBMEMBERCATALOG_H

#include "dbcatalog_interface.h"


class DBMemberCatalog : public DBCatalog_Interface
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID DBCatalog_Interface_iid FILE "dbmembercatalog.json")
  Q_INTERFACES(DBCatalog_Interface)


public:
  explicit DBMemberCatalog();

  QStringList categories() const;


signals:


public slots:


private:
  QWidget * createWidget( QWidget *parentWidget );
};

#endif // DBMEMBERCATALOG_H
