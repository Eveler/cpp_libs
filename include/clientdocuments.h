#ifndef CLIENTDOCUMENTS_H
#define CLIENTDOCUMENTS_H

#include <QSortFilterProxyModel>
#include "abstractdocumentslist.h"

class ClientDocuments : public AbstractDocumentsList
{
  Q_OBJECT
public:
  explicit ClientDocuments(const QVariant clientId, QSqlDatabase db,
                           QObject *parent = 0);
  ~ClientDocuments();
  virtual QSortFilterProxyModel* model();
  DocumentsModel* documents();
  void load(QSqlDatabase db);
  bool load( MFCDocumentInfo *doc );

signals:

public slots:
  bool saveDocuments(QSqlDatabase db, QString declar);
  bool saveDocList(QSqlDatabase db,
                   QDateTime saveTime=QDateTime::currentDateTime(),
                   bool initial=false);
  bool saveDeleteDocuments(QSqlDatabase db);

private slots:
  void modelDestroyed();

private:
  QSortFilterProxyModel *sortedModel;

};

#endif // CLIENTDOCUMENTS_H
