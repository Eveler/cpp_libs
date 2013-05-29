#ifndef CLIENTDOCSSAVER_H
#define CLIENTDOCSSAVER_H

#include "abstractdoclistsaver.h"

class ClientDocsSaver : public AbstractDocListSaver
{
  Q_OBJECT
public:
  explicit ClientDocsSaver(QSqlDatabase db,QString id,QObject *parent = 0);

signals:

public slots:
  bool saveDocuments(DocumentsModel *docList, QString declar);
  bool saveDocList(DocumentsModel *docList, QDateTime saveTime,bool initial);

};

#endif // CLIENTDOCSSAVER_H
