#include "abstractdocsstorage.h"
//#include "macros.h"
#include "amslogger.h"

QHash< QString,QPair< AbstractDocsStorage*,int > > AbstractDocsStorage::instances=
    QHash< QString,QPair< AbstractDocsStorage*,int > >();
QString AbstractDocsStorage::errStr=QString();

AbstractDocsStorage::AbstractDocsStorage(const QString storageName,
                                         QObject *parent) :
    QObject(parent)
{
  instanceName=storageName;
  connected=false;
  registerStorage(storageName,this);
}

AbstractDocsStorage::~AbstractDocsStorage(){
  if(instances.count(instanceName)>0){
    emit error(tr("Существуют ещё использумые экземпляры класса "
                  "AbstractDocsStorage"));
    LogDebug()<<tr("AbstractDocsStorage: There is instances in use. "
                              "Use removeStorage to free them");
  }
  instances.remove(instanceName);
}

bool AbstractDocsStorage::registerStorage(const QString storageName,
                                          QObject *instance){
  if(instances.contains(storageName)) return false;
  AbstractDocsStorage* obj=qobject_cast< AbstractDocsStorage* >(instance);
  if(!obj) return false;
  instances.insert(
        storageName,qMakePair< AbstractDocsStorage*,int >(obj,1));
  obj->instanceName=storageName;
  LogDebug()<<storageName<<"registered";
  return true;
}

void AbstractDocsStorage::setError(const QString str){
  errStr=tr("%3(%2): %1").arg(str).arg(metaObject()->className()).arg(objectName());
  LogDebug()<<errStr;
  emit error(errStr);
}

AbstractDocsStorage &AbstractDocsStorage::addStorage(const QString storageName){
  if(instances.contains(storageName)){
    instances[storageName].second++;
    return *instances.value(storageName).first;
  }else{
//    AbstractDocsStorage *instance=new AbstractDocsStorage(storageName);
//    if(instance==NULL){
//      errStr=tr("Ошибка при создании объекта DocsStorage");
//      return *instance;
//    }
//    instance->instanceName=storageName;
//    registerStorage(storageName,instance);
//    return *instance;
    AbstractDocsStorage *instance=NULL;
    return *instance;
  }
}

void AbstractDocsStorage::removeStorage(const QString storageName){
  if(instances.contains(storageName)){
    instances[storageName].second--;
    LogDebug()<<storageName<<"instance count ="<<instances[storageName].second;
    if(instances.value(storageName).second<=0){
      QPair< AbstractDocsStorage*,int > pair=instances.take(storageName);
      delete pair.first;
      LogDebug()<<storageName<<"removed";
    }
  }
}

void AbstractDocsStorage::removeStorage(){
  removeStorage(instanceName);
}

QStringList AbstractDocsStorage::storagesNames(){
  return instances.keys();
}

bool AbstractDocsStorage::contains(const QString storageName){
  return instances.contains(storageName);
}

int AbstractDocsStorage::references(){
  return instances.value(instanceName).second;
}

QString AbstractDocsStorage::errorString(){
  return errStr;
}
