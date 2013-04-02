#ifndef DBCATALOG_H
#define DBCATALOG_H

#include <QMainWindow>

namespace Ui {
class DBCatalog;
}

class DBCatalog : public QMainWindow
{
  Q_OBJECT
  
public:
  explicit DBCatalog(QWidget *parent = 0);
  ~DBCatalog();
  
private:
  Ui::DBCatalog *ui;
};

#endif // DBCATALOG_H
