#ifndef DECLARDOCUMENTS_H
#define DECLARDOCUMENTS_H

#include "abstractdocumentslist.h"

class DeclarDocuments : public AbstractDocumentsList
{
  Q_OBJECT
public:
  explicit DeclarDocuments(const QVariant declarId, QSqlDatabase db,
                           QObject *parent = 0);
  ~DeclarDocuments();
  virtual QSortFilterProxyModel* model();
  DocumentsModel* documents();
  void load(QSqlDatabase db);

signals:

public slots:
  bool saveDocuments(QSqlDatabase db, QString declar);
  bool saveDocList(QSqlDatabase db,
                   QDateTime saveTime=QDateTime::currentDateTime(),
                   bool initial=false);

private slots:
  void modelDestroyed();

private:
  QSortFilterProxyModel *sortedModel;

};

#endif // DECLARDOCUMENTS_H
