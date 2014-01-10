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
  setExecExtension();
}

HtmlReportLoader::~HtmlReportLoader()
{
  clearPlugins();
  if(loader->isLoaded()) loader->unload();
  delete loader;
  loader = NULL;
}

QStringList HtmlReportLoader::list(const QUrl &url)
{
  QStringList pList;
  if(!url.isValid()){
    setError(tr("Ошибочный адрес: %1").arg(url.toString()));
    return pList;
  }

  clearPlugins();
  FtpLoader *ftpLoader = new FtpLoader(this);
  foreach(QFileInfo fi, ftpLoader->list(url)){
    QPluginLoader* pl = new QPluginLoader(fi.absoluteFilePath(), this);
    if(!pl->load()){
      setError(tr("Ошибка загрузки модуля \"%1\": %2")
               .arg(fi.baseName()).arg(pl->errorString()));
      continue;
    }
    AbstractHtmlReportPlugin* plugin =
        qobject_cast< AbstractHtmlReportPlugin* >(pl->instance());
    if(plugin){
      foreach(QString pName,plugin->names()){
        pList<<pName;
        plugins.insert(pName, pl);
      }
    }
  }

  if(!loader->fileName().isEmpty()){
    if(!loader->isLoaded()){
      if(!loader->load()){
        setError(tr("Ошибка загрузки модуля \"%1\": %2")
                 .arg(loader->fileName()).arg(loader->errorString()));
        return pList;
      }
    }
    AbstractHtmlReportPlugin* plugin =
        qobject_cast< AbstractHtmlReportPlugin* >(loader->instance());
    if(plugin){
      foreach(QString pName,plugin->names()){
        pList<<pName;
        plugins.insert(pName, loader);
      }
    }
  }

  return pList;
}

bool HtmlReportLoader::select(const QString &name)
{
  if(!plugins.contains(name)){
    setError(tr("Шаблон %1 отсутствует!").arg(name));
    return false;
  }

  QPluginLoader* plugin = plugins.value(name);
  if(!plugin->isLoaded())
    if(!plugin->load()){
      setError(tr("Ошибка загрузки модуля \"%1\": %2")
               .arg(plugin->fileName()).arg(plugin->errorString()));
      return false;
    }

  AbstractHtmlReportPlugin *rep = qobject_cast<AbstractHtmlReportPlugin*>(
        plugin->instance());
  if(rep){
    if(!rep->select(name)){
      setError(tr("Ошибка при выборе шаблона: %1").arg(name));
      return false;
    }
    rep->load();
  }

  loader = plugin;
  return true;
}

AbstractHtmlReportPlugin *HtmlReportLoader::load(const QUrl &url)
{
  if(!url.isValid()){
    setError(tr("Ошибочный адрес: %1").arg(url.toString()));
    return NULL;
  }

  QString fName;
  // parse url & load file locally
  if(url.scheme().toLower()=="ftp"){
    FtpLoader *ftpLoader = new FtpLoader(this);
    fName = ftpLoader->load(url);
    if(fName.isEmpty()) setError(ftpLoader->errorString());
    delete ftpLoader;
  }else if(url.scheme().toLower()=="http"){
    // TODO: QNetworkAccessManager
  }else fName=url.path();
  if(fName.isEmpty()) return NULL;
  QFileInfo fi(fName);

  if(loader->isLoaded()){
    if(loader->fileName().contains(fi.baseName())){
      return qobject_cast< AbstractHtmlReportPlugin* >(loader->instance());
    }else{
      loader = new QPluginLoader(fName,this);
      if(!loader->load()){
        setError(tr("Ошибка загрузки модуля \"%1\": %2")
                 .arg(fi.baseName()).arg(loader->errorString()));
        if(plugins.count()>0){
          delete loader;
          loader = plugins.values().first();
        }
        return NULL;
      }
//      if(!loader->unload()){
//      setError(tr("Ошибка выгрузки модуля: %1").arg(loader->errorString()));
//      return NULL;
    }
  }else{
    loader->setFileName(fName);
    if(!loader->load()){
      setError(tr("Ошибка загрузки модуля \"%1\": %2")
               .arg(fi.baseName()).arg(loader->errorString()));
      return NULL;
    }
  }

  AbstractHtmlReportPlugin *rep = qobject_cast< AbstractHtmlReportPlugin* >(
        loader->instance());
  if(rep){
    foreach(QString pName, rep->names()){
      if(!plugins.contains(pName)) plugins.insert(pName, loader);
    }
  }
  return rep;
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

void HtmlReportLoader::setExecExtension(QString e)
{
  ext=e;
}

QString HtmlReportLoader::lastError() const
{
  return errStr;
}

bool HtmlReportLoader::unload(/*AbstractHtmlReportPlugin *p*/)
{
//  QStringList names = instance()->names();
  bool res=loader->unload();
  if(!res && !loader->errorString().isEmpty())
    setError(tr("Ошибка выгрузки: %1").arg(loader->errorString()));
//  else foreach(QString name, names) plugins.remove(name);
  return res;
}

bool HtmlReportLoader::exec()
{
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
//  QString res=MFCCore::execFile(rep->report()->generate(), ext, false);
  QString res=MFCCore::startSoffice(rep->report()->generate(), ext/*, false*/);
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

void HtmlReportLoader::clearPlugins()
{
  QList<QPluginLoader*> values = plugins.values();
  plugins.clear();

  while(!values.isEmpty()){
    QPluginLoader *p = values.takeFirst();
    values.removeAll(p);
    if(p->isLoaded()) p->unload();
    delete p;
  }
}

FtpLoader::FtpLoader(QObject *parent):
  QObject(parent),
  loop(new QEventLoop(this)),
  engine(new FTPEngine(this)),
  file(NULL)
{
  connect(engine,SIGNAL(ftpAnswer(FTPEngine::Command,bool)),
          SLOT(ftpAnswer(FTPEngine::Command,bool)));
  connect(engine,SIGNAL(authenticationCompleted(bool)),
          SLOT(authenticationCompleted(bool)));
}

FtpLoader::~FtpLoader()
{
  delete engine;
  delete loop;
  if(file) delete file;
}

QFileInfoList FtpLoader::list(const QUrl &url)
{
  QFileInfoList fiList;
  if(!url.isValid() && url.scheme().toLower()!="ftp") return fiList;

  int res = 0;
  if(!engine->isConnected()){
    if(!engine->connectToHost(url)){
      errStr = tr("Ошибка соединения: %1").arg(engine->lastError());
      return fiList;
    }
    res = loop->exec();
    if(res<0){
      return fiList;
    }
  }

  if(!engine->cd(url.path())){
    errStr = tr("Ошибка смены папки: %1").arg(engine->lastError());
    return fiList;
  }
  res = loop->exec();
  if(res<0){
    return fiList;
  }

  if(!engine->list()){
    errStr = tr("Ошибка соединения: %1").arg(engine->lastError());
    return fiList;
  }
  res = loop->exec();
  if(res<0){
    return fiList;
  }

  foreach (FileInfo *fi, engine->listResult()){
    if(fi->isFile()){
      QUrl u(url);
      u.setPath(u.path()+"/"+fi->fileName());
      QString fName = load(u);
      if(fName.isEmpty()) continue;
      fiList<<fName;
    }// TODO: recurse into subdirs
  }

  return fiList;
}

QString FtpLoader::load(const QUrl &url)
{
  if(!url.isValid() && url.scheme().toLower()!="ftp") return QString();

  m_url = url;
  if(file){
    delete file;
    file = NULL;
  }

  int res = 0;
  if(!engine->isConnected()){
    if(!engine->connectToHost(url)){
      errStr = tr("Ошибка соединения: %1").arg(engine->lastError());
      return QString();
    }
    res = loop->exec();
    if(res<0){
      return QString();
    }
  }

  QDir d(qApp->applicationDirPath()+"/plugins");
  if(!d.exists()){
    if(!d.mkpath(d.absolutePath())){
      errStr = tr("Ошибка при создании папки \"%1\"").arg(d.absolutePath());
      return QString();
    }
  }

  QFileInfo fi(url.path());
  file = new QFile(d.absolutePath()+"/"+fi.fileName(), this);
  if(!file->open(QFile::WriteOnly)){
    errStr = tr("Ошибка открытия: %1").arg(file->errorString());
    return QString();
  }

  if(!engine->getFile(m_url.path(), file)){
    errStr = tr("Ошибка получения: %1").arg(engine->lastError());
    return QString();
  }
  res = loop->exec();
  engine->disconnectFromHost();
  file->close();
  if(res<0){
    file->remove();
    return QString();
  }
  return file->fileName();
}

QString FtpLoader::errorString() const
{
  return errStr;
}

void FtpLoader::authenticationCompleted(bool res)
{
  if(!res){
    errStr = tr("Ошибка подключения: %1").arg(engine->lastError());
    loop->exit(-1);
  }else loop->quit();
}

void FtpLoader::ftpAnswer(FTPEngine::Command cmd, bool result)
{
  switch (cmd) {
  case FTPEngine::Command_List:
    if(!result){
      errStr = tr("Ошибка получения списка модулей: %1").arg(engine->lastError());
      loop->exit(-1);
    }else loop->quit();
    return;
    break;
  case FTPEngine::Command_Cd:
    if(!result){
      errStr = tr("Ошибка смены папки: %1").arg(engine->lastError());
      loop->exit(-1);
    }else loop->quit();
    return;
    break;
  case FTPEngine::Command_GetFile:
    if(!result){
      errStr = tr("Ошибка загрузки: %1").arg(engine->lastError());
      loop->exit(-1);
    }else loop->quit();
    return;
  default:
    break;
  }
  if(!result){
    errStr = tr("Ошибка ftp: %1").arg(engine->lastError());
    loop->exit(-1);
  }
}
