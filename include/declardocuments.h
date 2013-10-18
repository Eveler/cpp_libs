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
  bool load( MFCDocumentInfo *doc ) const;
  void set_clients_ids(QStringList& ids);
  void set_docpaths_ids(QStringList& ids);

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
  QStringList clients_ids;
  QStringList docpaths_ids;

};

#endif // DECLARDOCUMENTS_H
