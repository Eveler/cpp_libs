#ifndef DECLARDOCSSAVER_H
#define DECLARDOCSSAVER_H

#include "abstractdoclistsaver.h"

class DeclarDocsSaver : public AbstractDocListSaver
{
  Q_OBJECT
public:
  explicit DeclarDocsSaver(QSqlDatabase db,QString id,QObject *parent = 0);

signals:

public slots:
  bool saveDocuments(DocumentsModel *docList, QString declar);
  bool saveDocList(DocumentsModel *docList, QDateTime saveTime, bool initial);

};

#endif // DECLARDOCSSAVER_H
