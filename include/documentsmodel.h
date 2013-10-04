#ifndef DOCUMENTSMODEL_H
#define DOCUMENTSMODEL_H

#include <QAbstractItemModel>
#include "mfcdocument.h"
#include "export/docmanager_export.h"

class DOCMANAGER_EXPORT DocumentsModel : public QAbstractItemModel
{
  Q_OBJECT
public:
  DocumentsModel(QObject *parent=0);
  ~DocumentsModel();
  int rowCount(const QModelIndex &parent=QModelIndex()) const;
  int columnCount(const QModelIndex &parent=QModelIndex()) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  QModelIndex index(int row, int column,
                    const QModelIndex &parent=QModelIndex()) const;
  QModelIndex parent(const QModelIndex &child) const;
  QVariant data(const QModelIndex &index, int role) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  int findColumn(QString name) const;
  void clear();
  QList< MFCDocument* > documents() const;
  QList< MFCDocument* > newDocuments() const;
  MFCDocument* document(const int row) const;
  MFCDocument* document(const QModelIndex &index) const;
  MFCDocument* document(const QVariant &id) const;
  QVariant documentID(MFCDocument *doc) const;
  bool isNew(MFCDocument *doc) const;
  bool removeRows(int row, int count, const QModelIndex &parent=QModelIndex());

  bool isNewDocumentsVisible() const;
  void setNewDocumentsVisible(bool v=true);
  QVariantList removedDocumentsIDs() const;
  void setDocumentID(MFCDocument *doc,QVariant id);

signals:
  void documentAdded(MFCDocument *doc);
  void documentRemoved(MFCDocument *doc);

public slots:
  bool addDocument(MFCDocument *doc, const QVariant id=QVariant(),
                   const bool isNew=true);
  bool addDocument(const QString doc_type,const QDate doc_date,
                   const QString doc_name=QString(),
                   const QString doc_series=QString(),
                   const QString doc_number=QString(),
                   const QDate doc_expires=QDate(),
                   const QString doc_agency=QString(),
                   const QDateTime doc_created=QDateTime(),
                   const QVariant id=QVariant(),const bool isNew=true);
  bool removeDocument(MFCDocument *doc);

private slots:
  bool removeDocument(const int row);
  void documentDestroyed(QObject *obj);
  void recalc();

private:
  QMap< int,MFCDocument* > docs;
  QVariantList columnsNames;
//  QMap< int,QVariant > ids;
  QList< MFCDocument* > newDocs;
  QVariantList removedIDs;

  bool isNewVisible;

  bool removeDocument_p(MFCDocument *doc);
  QByteArray propertyName(QObject *obj,int idx) const;
  QString pnConvert(QString pn) const;
};

#endif // DOCUMENTSMODEL_H
