#ifndef DOCPATHSDOCSLOADER_H
#define DOCPATHSDOCSLOADER_H

#include "abstractdoclistloader.h"

class DocpathsDocsLoader : public AbstractDocListLoader
{
  Q_OBJECT
public:
  explicit DocpathsDocsLoader(QSqlDatabase db,QObject *parent = 0);
  ~DocpathsDocsLoader();
  virtual DocumentsModel* load(QVariant foreignID);

signals:

public slots:

private:

};

#endif // DOCPATHSDOCSLOADER_H
