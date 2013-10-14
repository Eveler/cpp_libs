#ifndef FTPDOCSSTORAGE_H
#define FTPDOCSSTORAGE_H

#include <QObject>
#include <QStringList>
#include <QQueue>
#include <QHash>
#include <QEventLoop>
#include "ftpengine.h"
#include "abstractdocsstorage.h"
#include "export/dossier_export.h"

class DOSSIER_EXPORT FtpDocsStorage : public AbstractDocsStorage
{
  Q_OBJECT
protected:
  explicit FtpDocsStorage(const QString storageName="__default_ftp_storage",
                          const QString dataBaseName=QString(),
                          QObject *parent = 0);
  ~FtpDocsStorage();
public:
  static FtpDocsStorage &addStorage(const QString storageName="__default_ftp_storage");
  void setDataBaseName(const QString dataBaseName="MFCs");
  bool connectToHost(const QString uName,const QString pass,const QString host,
                     const quint16 port=21);
  void setRoot(const QString dataBaseName=QString(),const QString path="/docs");
  static QString errorString();
  int port() const {return ftpPort;}

private:
  QString dbName;
  static QString errStr;
//  QString arcName;
  QString rootPath;
  QString curPath;
//  bool connected; // DPERECATED
  QQueue< QFile* > jobQueue;
  bool isDownloading;
  QFile *arc;
  MFCDocumentInfo* curDoc;
  int docCount;
  int docsDone;

  QString userName;
  QString userPass;
  QString ftpHost;
  quint16 ftpPort;
  FTPEngine *ftpEng;

  QEventLoop *loop;

  static QString zipErrStr(int errn);
  void putNextFile();

private slots:
//  void loadDone(QFile *file);
//  void saveDone(QString fileName);
  void emitError(QString err, QString file, int line);
  void ftpTransferProgress(qint64 done,qint64 total);
  void authenticationCompleted(bool res);
  void ftpAnswer(FTPEngine::Command cmd,bool res);
  void ftpAnswer(QString text,int code);

signals:
  void done(bool);
  virtual void error(QString);
  void saved(QString);
  void loaded(MFCDocumentInfo*);

public slots:
  bool save(MFCDocumentInfo* doc,QString declarNumber=QString());
  bool load( MFCDocumentInfo *doc );
  void cancel();

};

#endif // FTPDOCSSTORAGE_H
