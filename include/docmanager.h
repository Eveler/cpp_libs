#ifndef DOCMANAGER_H
#define DOCMANAGER_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QEventLoop>
#include "clientdocuments.h"
#include "declardocuments.h"
#include "docpathsdocuments.h"
#include "mfcdocument.h"
#include "docmanager_export.h"

class DOCMANAGER_EXPORT Docmanager : public QObject
{
  Q_OBJECT
public:
  explicit Docmanager(QSqlDatabase db,QObject *parent = 0);
  ~Docmanager();

//  void setDocumentsStorage(AbstractDocsStorage *storage);

  DocumentsModel *allDocuments() const;
//  QList< MFCDocument* > findAddedDocuments(const QVariant type) const;
  DocumentsModel *addedDocuments() const;
//  QList< MFCDocument* > addedDocumentsList() const;
//  QAbstractItemModel *documentsForRelease() const;
//  QList< MFCDocument* > documentsForReleaseList() const;

  QVariant currentClient() const;
  MFCDocument *clientDocument(const QModelIndex &index) const;
  DocumentsModel *clientDocuments() const;
  DocumentsModel *declarDocuments() const;

  void setSaveTime(QDateTime dt);

  QSqlDatabase database() const;

signals:
  void dataTransferProgress(qint64 val,qint64 total);
  void error(QString);
  void currentClientChanged(ClientDocuments*);
  void currentClientChanged(QAbstractItemModel*);
  void currentClientChanged(QVariant);
  void documentLoadDone(MFCDocument*);
  void documentAdded(DocumentsModel*);
  void currentDocpathsChanged(DocpathsDocuments*);
  void currentDocpathsChanged(QAbstractItemModel*);
  void currentDocpathsChanged(QVariant);

public slots:
  bool addClient(QVariant id);
  void setClientCurrent(QVariant id);
  void unsetCurrentClient();
  void removeClient(QVariant id);
  bool setDeclar(const QVariant id);
  void unsetDeclar();
  bool addDocpaths(QVariant id);
  void removeDocpaths(QVariant id);
  void setDocpathsCurrent(QVariant id);
  bool nextDocpaths();
  MFCDocument *newDocument(MFCDocument *doc);
  bool loadDocument(MFCDocument *doc);

//  bool loadDocument(MFCRecord *documentRec);

  bool save();
  bool saveDocuments();
  bool saveDocumentsLists(bool initial=false);

  void clear();
  void cancelDownload();

private slots:
  void allDocsAdd(MFCDocument *doc);
  void allDocsRemove(MFCDocument *doc);
  void set_error(QString str,QString file=QString(),int line=0);
  void objectDestroyed();
  void documentSaved(QString fileName);
  void timeout();
  void updateTimer();
  QVariant documentID(MFCDocument *doc) const;

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

};

#endif // DOCMANAGER_H
