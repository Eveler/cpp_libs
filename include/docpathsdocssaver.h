#ifndef DOCPATHSDOCSSAVER_H
#define DOCPATHSDOCSSAVER_H

#include "abstractdoclistsaver.h"

class DocpathsDocsSaver : public AbstractDocListSaver
{
  Q_OBJECT
public:
  explicit DocpathsDocsSaver(QSqlDatabase db,QString id,QObject *parent = 0);
  bool saveDocuments(DocumentsModel *docList, QString declar);
  bool saveDocList(DocumentsModel *docList, QDateTime saveTime,bool initial);
  bool saveDeleteDocuments(DocumentsModel *docList);

signals:

public slots:

};

#endif // DOCPATHSDOCSSAVER_H
