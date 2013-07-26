#ifndef DOCPATHSDOCUMENTS_H
#define DOCPATHSDOCUMENTS_H

#include <QSortFilterProxyModel>
#include "abstractdocumentslist.h"

class DocpathsDocuments : public AbstractDocumentsList
{
  Q_OBJECT
public:
  explicit DocpathsDocuments(const QVariant docpathsId, QSqlDatabase db,
                             QObject *parent = 0);
  ~DocpathsDocuments();
  virtual QSortFilterProxyModel* model();
  DocumentsModel* documents();
  void load(QSqlDatabase db);

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

#endif // DOCPATHSDOCUMENTS_H
