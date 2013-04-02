#include "dbcatalog.h"
#include "ui_dbcatalog.h"

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
