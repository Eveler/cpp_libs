#ifndef DECLARDOCSSAVER_H
#define DECLARDOCSSAVER_H

#include "abstractdoclistsaver.h"

class DeclarDocsSaver : public AbstractDocListSaver
{
  Q_OBJECT
public:
  explicit DeclarDocsSaver(QSqlDatabase db,QString id,QObject *parent = 0);
  void set_clients_ids(QStringList& ids);
  void set_docpaths_ids(QStringList& ids);

signals:

public slots:
  bool saveDocuments(DocumentsModel *docList, QString declar);
  bool saveDocList(DocumentsModel *docList, QDateTime saveTime, bool initial);
  bool saveDeleteDocuments(DocumentsModel *docList);

private:
  QStringList clients_ids;
  QStringList docpaths_ids;
};

#endif // DECLARDOCSSAVER_H
