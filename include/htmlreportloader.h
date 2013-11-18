#ifndef HTMLREPORTLOADER_H
#define HTMLREPORTLOADER_H

#include "export/htmlreportloader_export.h"
#include "abstracthtmlreportplugin.h"
#include "ftpengine.h"
#include <QObject>
#include <QPluginLoader>
#include <QEventLoop>

class HTMLREPORTLOADERSHARED_EXPORT HtmlReportLoader: public QObject
{
  Q_OBJECT

public:
  explicit HtmlReportLoader(QObject *parent=0);
  ~HtmlReportLoader();

  QStringList list(const QUrl &url);
  bool select(const QString &name);
  AbstractHtmlReportPlugin *load(const QUrl &url);
  AbstractHtmlReportPlugin *instance();
  bool isLoaded() const;
  void setExecExtension(QString e="odt");
  QString lastError() const;

public slots:
  bool unload();
  bool exec();
  bool exec(QUrl &url);

signals:
  void error(QString);

private:
  QString errStr;
  QPluginLoader *loader;
  QString ext;
  QMap<QString, QPluginLoader*> plugins;
//  FtpLoader *ftpLoader;
  void set_error(const QString file, const int line, const QString &str);
  void clearPlugins();
};

class FtpLoader: public QObject
{
  Q_OBJECT
public:
  explicit FtpLoader(QObject *parent=0);
  ~FtpLoader();
  QFileInfoList list(const QUrl &url);
  QString load(const QUrl &url);
  QString errorString() const;
private slots:
  void authenticationCompleted(bool res);
  void ftpAnswer(FTPEngine::Command cmd, bool result);
private:
  QEventLoop *loop;
  FTPEngine *engine;
  QString errStr;
  QUrl m_url;
  QFile *file;
};

#endif // HTMLREPORTLOADER_H
