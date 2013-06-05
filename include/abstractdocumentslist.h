#ifndef ABSTRACTDOCUMENTSLIST_H
#define ABSTRACTDOCUMENTSLIST_H

#include <QObject>
#include <QSortFilterProxyModel>
#include "abstractdoclistloader.h"
#include "abstractdoclistsaver.h"

//#define DATA(idx,fName) doclistModel->index(idx,findColumn(doclistModel,fName)).data()

class AbstractDocumentsList : public QObject
{
  Q_OBJECT
public:
  explicit AbstractDocumentsList(const QVariant Id,QSqlDatabase db,
                                 QObject *parent = 0);
  ~AbstractDocumentsList();
  void setLoader(AbstractDocListLoader *l);
  void setSaver(AbstractDocListSaver *s);
  virtual QSortFilterProxyModel *model()=0;
  virtual DocumentsModel *documents()=0;
  QVariant id() const;

signals:
  void error(QString);
  void progress(qint64,qint64);
  void loadDone(bool);
  void documentLoadDone(MFCDocument*);
//  void saveDone(bool);

public slots:
  void clear();
  QList< MFCDocument* > findDocuments(QString doc_type,QDate doc_date,
                                    QString doc_number=QString(),
                                    QString doc_series=QString(),
                                    QString doc_name=QString(),
                                    QString doc_agency=QString(),
                                    QDateTime doc_created=QDateTime(),
                                    QDate doc_expires=QDate()) const;
  virtual void cancelDownload();
  virtual bool save(QSqlDatabase db, QString declar,
                    QDateTime saveTime=QDateTime::currentDateTime());
  virtual bool saveDocuments(QSqlDatabase db,QString declar)=0;
  virtual bool saveDocList(QSqlDatabase db,
                           QDateTime saveTime=QDateTime::currentDateTime(),
                           bool initial=false)=0;
  virtual bool saveDeleteDocuments(QSqlDatabase db)=0;

protected slots:
  void objectDestroyed();
  void setDocumentID(MFCDocument *doc,QVariant id);
  void showSaveProgress(qint64 val,qint64 total);

protected:
  AbstractDocListLoader *loader;
  AbstractDocListSaver *saver;
  bool ownLoader;
  bool ownSaver;
  QVariant ID;
  DocumentsModel *doclistModel;
  QSqlDatabase DB;

};

#endif // ABSTRACTDOCUMENTSLIST_H
