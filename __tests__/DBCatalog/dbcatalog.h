#ifndef DBCATALOG_H
#define DBCATALOG_H

#include <QMainWindow>


namespace Ui {
class DBCatalog;
}

class DBCatalog_P;

class DBCatalog : public QMainWindow
{
  Q_OBJECT
  friend class DBCatalog_P;


public:
  explicit DBCatalog(QWidget *parent = 0);
  ~DBCatalog();


private:
  Ui::DBCatalog *ui;

  DBCatalog_P *p;
};

#endif // DBCATALOG_H
