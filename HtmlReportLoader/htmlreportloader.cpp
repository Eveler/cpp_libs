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
  if(loader->isLoaded()) loader->unload();
  delete loader;
}

AbstractHtmlReportPlugin *HtmlReportLoader::load(QUrl url)
{
//  LogDebug()<<"url ="<<url<<"isLocalFile ="<<url.isLocalFile();
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
  QString res=MFCCore::execFile(rep->report()->generate(),ext);
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

QString FtpLoader::load(QUrl &url)
{
  if(!url.isValid() && url.scheme().toLower()!="ftp") return QString();

  m_url = url;
  if(file){
    delete file;
    file = NULL;
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

  if(!engine->connectToHost(url)){
    errStr = tr("Ошибка соединения: %1").arg(engine->lastError());
    return QString();
  }

  int res = loop->exec();
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
  if(res){
    if(!engine->getFile(m_url.path(), file)){
      errStr = tr("Ошибка получения: %1").arg(engine->lastError());
      loop->exit(-1);
    }
  }else{
    errStr = tr("Ошибка подключения: %1").arg(engine->lastError());
    loop->exit(-1);
  }
}

void FtpLoader::ftpAnswer(FTPEngine::Command cmd, bool result)
{
    switch (cmd) {
    case FTPEngine::Command_List:
      break;
    case FTPEngine::Command_SizeOf:
      break;
    case FTPEngine::Command_GetFile:
      if(!result){
        errStr = tr("Ошибка загрузки: %1").arg(engine->lastError());
        loop->exit(-1);
      }
      loop->quit();
      return;
    default:
      break;
    }
    if(!result){
      errStr = tr("Ошибка ftp: %1").arg(engine->lastError());
      loop->exit(-1);
    }
}
