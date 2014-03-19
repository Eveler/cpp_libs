#ifndef CLIENTDOCSLOADER_H
#define CLIENTDOCSLOADER_H

#include "abstractdoclistloader.h"

class ClientDocsLoader : public AbstractDocListLoader
{
  Q_OBJECT
public:
  explicit ClientDocsLoader(QSqlDatabase db,QObject *parent = 0);
  ~ClientDocsLoader();
  virtual DocumentsModel* load(QVariant foreignID);

signals:

public slots:

private:
};

#endif // CLIENTDOCSLOADER_H
