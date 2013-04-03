#ifndef DBCATALOG_P_H
#define DBCATALOG_P_H

#include <QObject>


class DBCatalog;
class Widget_Configuration;
class QAction;
class DBCatalog_Interface;

class DBCatalog_P : public QObject
{
  Q_OBJECT
  friend class DBCatalog;


public:


signals:


public slots:


private:
  Widget_Configuration *m__Configuration;

  explicit DBCatalog_P( DBCatalog *parent );
  ~DBCatalog_P();

  DBCatalog * p_dptr() const;


private slots:
  void showPluginWidget( QWidget *widget );
};

#endif // DBCATALOG_P_H
