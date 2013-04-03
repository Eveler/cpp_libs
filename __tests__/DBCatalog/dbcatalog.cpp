#include "dbcatalog.h"
#include "ui_dbcatalog.h"

#include "dbcatalog_interface.h"


DBCatalog::DBCatalog(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::DBCatalog)
{
  ui->setupUi(this);
}

DBCatalog::~DBCatalog()
{
  delete ui;
}
