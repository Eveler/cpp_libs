#ifndef DOCMANAGER_H
#define DOCMANAGER_H

#include <QObject>
//#include <QStyledItemDelegate>
#include <QEventLoop>
#include "clientdocuments.h"
#include "declardocuments.h"
#include "docpathsdocuments.h"
#include "mfcdocumentinfo.h"
#include "export/docmanager_export.h"

class DOCMANAGER_EXPORT Docmanager : public QObject
{
  Q_OBJECT
public:
  explicit Docmanager(QSqlDatabase db,QObject *parent = 0);
  ~Docmanager();

  DocumentsModel *allDocuments() const;
//  QList< MFCDocumentInfo* > findAddedDocuments(const QVariant type) const;
  DocumentsModel *addedDocuments() const;
//  QAbstractItemModel *documentsForRelease() const;
//  QList< MFCDocumentInfo* > documentsForReleaseList() const;

  QVariant currentClient() const;
  MFCDocumentInfo *clientDocument(const QModelIndex &index) const;
  DocumentsModel *clientDocuments() const;
  DocumentsModel *clientDocuments( QVariant id ) const;
  QAbstractItemModel * sortedClientDocuments() const;
  MFCDocumentInfo *docpathsDocument(const QModelIndex &index) const;
  DocumentsModel *docpathsDocuments() const;
  DocumentsModel *docpathsDocuments(QVariant id) const;
  QAbstractItemModel * sortedDocpathsDocuments() const;
  MFCDocumentInfo *declarDocument(const QModelIndex &index) const;
  DocumentsModel *declarDocuments() const;
  QAbstractItemModel * sortedDeclarDocuments() const;

  void setSaveTime(QDateTime dt);

  QSqlDatabase database() const;

  QVariant declar() const;
  QVariantList docpaths() const;
  QVariant currentDocpath() const;

signals:
  void dataTransferProgress(qint64 val,qint64 total);
  void error(QString);
  void currentClientChanged(DocumentsModel*);
  void currentClientChanged(QAbstractItemModel*);
  void currentClientChanged(QVariant);
  void documentLoadDone(MFCDocumentInfo*);
  void documentAdded(DocumentsModel*);
  void currentDocpathsChanged(DocumentsModel*);
  void currentDocpathsChanged(QAbstractItemModel*);
  void currentDocpathsChanged(QVariant);
  void declarSet(DocumentsModel*);
  void declarSet(QAbstractItemModel*);
  void declarSet(QVariant);

public slots:
  bool addClient(QVariant id);
  void setClientCurrent(QVariant id);
  void unsetCurrentClient();
  void removeClient(QVariant id);
  bool removeClientDocument(MFCDocumentInfo *doc);
  bool setDeclar(const QVariant id);
  void unsetDeclar();
  bool removeDeclarDocument(MFCDocumentInfo *doc);
  bool addDocpaths(QVariant id);
  void unsetCurrentDocpaths();
  void removeDocpaths(QVariant id);
  void setDocpathsCurrent(QVariant id);
  bool nextDocpaths();
  bool removeDocpathsDocument(MFCDocumentInfo *doc);
  MFCDocumentInfo *newDocument(MFCDocumentInfo *doc);
  bool loadDocument( MFCDocumentInfo *doc ) const;
  bool removeNewDocument(MFCDocumentInfo *doc);

  bool save(QString declarNumber=QString());
  bool saveDocuments(QString declarNumber=QString());
  bool saveDocumentsLists();
  bool saveDeleteDocuments();

  void clear();
  void cancelDownload();

private slots:
  void allDocsAdd(MFCDocumentInfo *doc);
  void allDocsRemove(MFCDocumentInfo *doc);
  void set_error(QString str,QString file=QString(),int line=0);
  void objectDestroyed();
  void timeout();
  void updateTimer();
  QVariant documentID(MFCDocumentInfo *doc) const;

private:
  QSqlDatabase DB;
  QHash< ClientDocuments*,QVariant > clientsDocs;
  DocumentsModel *allDocs;
  ClientDocuments *curClientDocs;
  QEventLoop *loop;
  QTimer *timer;
  DeclarDocuments *declarDocs;
  DocumentsModel *newDocs;
  QHash< DocpathsDocuments*,QVariant > docpathsDocs;
  DocpathsDocuments *curDocpathsDocs;
  QDateTime saveTime;

  QString errStr;

  bool toAdd2All(MFCDocumentInfo *doc) const;
};

#endif // DOCMANAGER_H
