#include "htmlreportloader.h"
#include "amslogger.h"
#include "mfccore.h"
#include <QUrl>
#include <QFileInfo>

#define setError(str) set_error(__FILE__,__LINE__,str)

HtmlReportLoader::HtmlReportLoader(QObject *parent):
  QObject(parent),errStr()
{
  loader = new QPluginLoader(this);
  setExtension();
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
  if(url.scheme().toLower()=="ftp"){
    // TODO: FTPEngine
  }else if(url.scheme().toLower()=="http"){
    // TODO: QNetworkAccessManager
  }
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

AbstractHtmlReportPlugin *HtmlReportLoader::instance()
{
  if(loader->isLoaded())
    return qobject_cast< AbstractHtmlReportPlugin* >(loader->instance());
  return NULL;
}

bool HtmlReportLoader::isLoaded() const
{
  return loader->isLoaded();
}

void HtmlReportLoader::setExtension(QString e)
{
  ext=e;
}

QString HtmlReportLoader::lastError() const
{
  return errStr;
}

bool HtmlReportLoader::unload(/*AbstractHtmlReportPlugin *p*/)
{
//  if(p!=loader->instance()) return false;
  bool res=loader->unload();
  if(!res && !loader->errorString().isEmpty())
    setError(tr("Ошибка выгрузки: %1").arg(loader->errorString()));
  return res;
}

bool HtmlReportLoader::exec()
{
//  LogDebug()<<"isLoaded ="<<loader->isLoaded()<<"fileName ="<<loader->fileName();
  if(!loader->isLoaded()){
    if(loader->fileName().isEmpty()){
      setError(tr("Отчёт не загружен!"));
      return false;
    }else if(!loader->load()){
      setError(tr("Ошибка загрузки модуля \"%1\": %2")
               .arg(loader->fileName()).arg(loader->errorString()));
      return false;
    }
  }
  AbstractHtmlReportPlugin *rep=
      qobject_cast< AbstractHtmlReportPlugin* >(loader->instance());
  if(!rep){
    setError(tr("Ошибка отчёта: %1").arg(loader->errorString()));
    return false;
  }
  if(rep->report()->data().isEmpty()){
    if(!rep->load()){
      setError(rep->lastError());
      return false;
    }
  }
//  LogDebug()<<"data ="<<rep->report()->data();
  QString res=MFCCore::execFile(rep->report()->generate(),tr("odf"));
  if(res.isEmpty()) return true;
  setError(tr("Ошибка открытия отчёта: %1").arg(res));
  return false;
}

bool HtmlReportLoader::exec(QUrl &url)
{
  if(load(url)) return exec();
  else return false;
}

void HtmlReportLoader::set_error(const QString file, const int line,
                                 const QString &str)
{
  errStr=tr("%1 (%2 [%3])").arg(str).arg(file).arg(line);
  emit error(errStr);
  LogWarning()<<file<<"["<<line<<"]:"<<str;
}
