#ifndef ABSTRACTDOCLISTSAVER_H
#define ABSTRACTDOCLISTSAVER_H

#include <QObject>
#include <QSqlDatabase>
#include <QDateTime>
#include <QEventLoop>
#include <QTimer>
#include "documentsmodel.h"
#include "abstractdocsstorage.h"

class AbstractDocListSaver : public QObject
{
  Q_OBJECT
public:
  explicit AbstractDocListSaver(QSqlDatabase db,QString id,QObject *parent = 0);
  ~AbstractDocListSaver();
  void setStorage(AbstractDocsStorage *s);
  AbstractDocsStorage *storage() const;
  virtual bool saveDocuments(DocumentsModel *docList, QString declar);
  virtual bool saveDocList(DocumentsModel *docList,
                           QDateTime saveTime=QDateTime::currentDateTime(),
                           bool initial=false)=0;
  virtual void clear();

signals:
  void error(QString);
  void progress(qint64,qint64);
  void documentSaved(MFCDocument *doc,QVariant id);

public slots:
  virtual void cancelUpload();

protected slots:
  void objectDestroyed();
  virtual void documentSaveDone(QString path);
  void storTimeout();

protected:
  QSqlDatabase DB;
  QString errStr;
  AbstractDocsStorage *docStorage;
  bool ownStorage;
  QEventLoop *loop;
  QTimer *timer;
  MFCDocument *curDoc;
  QString foreign_id;

  void set_error(QString str,QString file,int line);

};

#endif // ABSTRACTDOCLISTSAVER_H
