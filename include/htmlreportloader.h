#ifndef HTMLREPORTLOADER_H
#define HTMLREPORTLOADER_H

#include "export/htmlreportloader_export.h"
#include "abstracthtmlreportplugin.h"
#include <QObject>
#include <QPluginLoader>

class HTMLREPORTLOADERSHARED_EXPORT HtmlReportLoader: public QObject
{
  Q_OBJECT
public:
  explicit HtmlReportLoader(QObject *parent=0);
  ~HtmlReportLoader();

  AbstractHtmlReportPlugin *load(QUrl &url);
  AbstractHtmlReportPlugin *instance();
  bool isLoaded() const;
  void setExtension(QString e="doc");
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
  void set_error(const QString file,const int line,const QString &str);
};

#endif // HTMLREPORTLOADER_H
