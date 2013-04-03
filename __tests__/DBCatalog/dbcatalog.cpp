#include "dbcatalog.h"
#include "ui_dbcatalog.h"

#include "dbcatalog_p.h"


DBCatalog::DBCatalog(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::DBCatalog)
{
  ui->setupUi(this);

  p = new DBCatalog_P( this );
  connect( ui->action_Update, SIGNAL(triggered()), p, SLOT(updatePlugins()) );
}

DBCatalog::~DBCatalog()
{
  delete p;
  p = NULL;

  delete ui;
  ui = NULL;
}

