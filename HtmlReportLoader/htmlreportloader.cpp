#include "htmlreportloader.h"
#include "amslogger.h"
#include <QUrl>
#include <QFileInfo>

#define setError(str) set_error(__FILE__,__LINE__,str)

HtmlReportLoader::HtmlReportLoader(QObject *parent):
  QObject(parent),errStr()
{
  loader = new QPluginLoader(this);
}

HtmlReportLoader::~HtmlReportLoader()
{
  if(loader->isLoaded()) loader->unload();
  delete loader;
}

AbstractHtmlReportPlugin *HtmlReportLoader::load(QUrl &url)
{
  LogDebug()<<"url ="<<url<<"isLocalFile ="<<url.isLocalFile();
  if(!url.isValid()){
    setError(tr("Ошибочный адрес: %1").arg(url.toString()));
    return NULL;
  }

  QString fName;
  // TODO: parse url & load file locally
  fName=url.path();
  QFileInfo fi(fName);

  if(loader->isLoaded()){
    if(loader->fileName().contains(fi.baseName()))
      return qobject_cast< AbstractHtmlReportPlugin* >(loader->instance());
    else if(!loader->unload()){
      setError(tr("Ошибка выгрузки модуля: %1").arg(loader->errorString()));
      return NULL;
    }
  }
  loader->setFileName(fName);
  if(!loader->load()){
    setError(tr("Ошибка загрузки модуля \"%1\": %2")
             .arg(fi.baseName()).arg(loader->errorString()));
    return NULL;
  }
  return qobject_cast< AbstractHtmlReportPlugin* >(loader->instance());
}

QString HtmlReportLoader::lastError() const
{
  return errStr;
}

void HtmlReportLoader::set_error(const QString file, const int line,
                                 const QString &str)
{
  errStr=tr("%1 (%2 [%3])").arg(str).arg(file).arg(line);
  emit error(errStr);
  LogWarning()<<file<<"["<<line<<"]:"<<str;
}
