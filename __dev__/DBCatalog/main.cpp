#include "dbcatalog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  DBCatalog w;
  w.show();
  
  return a.exec();
}
