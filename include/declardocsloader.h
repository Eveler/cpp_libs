#ifndef DECLARDOCSLOADER_H
#define DECLARDOCSLOADER_H

#include "abstractdoclistloader.h"

class DeclarDocsLoader : public AbstractDocListLoader
{
  Q_OBJECT
public:
  explicit DeclarDocsLoader(QSqlDatabase db,QObject *parent = 0);
  ~DeclarDocsLoader();
  virtual DocumentsModel* load(QVariant foreignID);

signals:

public slots:

private:

};

#endif // DECLARDOCSLOADER_H
