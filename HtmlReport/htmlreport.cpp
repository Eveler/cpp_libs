#include <QFile>
#include <QFileInfo>
#include <QTemporaryFile>
#include <QProcess>
#include <QTextCodec>
#include <QTextStream>
#include <QDir>
#include "htmlreport.h"
#include "mfccore.h"
#include "amslogger.h"

#define setError(str) set_error(str,__FILE__,__LINE__)

HtmlReport::HtmlReport(QObject *parent) :
  QObject(parent),repModel(NULL),insertedSections(0)
{
}

void HtmlReport::setSection(const QString &name, const QString &data){
  if(name.simplified().isEmpty() || data.simplified().isEmpty()) return;

  if(repSections.contains(name)) repSections[name]=data;
  else repSections.insert(name,data);
}

bool HtmlReport::setData(const QString &data){
  if(data.simplified().isEmpty()) return false;

  repData=data;
  // заполняем списки ключей и секций
  return parse();
}

bool HtmlReport::load(const QString &name){
  if(name.isEmpty()) return false;

  QFile rep(name);

  QFileInfo fi(rep);
  QString path=fi.absoluteFilePath();
  path.chop(fi.fileName().size());

  if(!rep.open(QFile::ReadOnly)){
    setError(rep.errorString());
    return false;
  }

  QByteArray msg=rep.readAll();
  if(rep.error()!=QFile::NoError){
    setError(rep.errorString());
    rep.close();
    return false;
  }
  rep.close();

  QTextCodec *cfcs=QTextCodec::codecForHtml(msg,0);
  if(cfcs){
    QTextCodec *cfl=QTextCodec::codecForLocale();

    msg=replaceMeta(msg,cfl);

    if(cfcs!=cfl){
      QString intenalMsg=cfcs->toUnicode(msg);
      if(cfl && cfl->canEncode(intenalMsg)){
        repData=cfl->fromUnicode(intenalMsg);
      }else if(cfl->canEncode(msg)){
        repData=cfl->fromUnicode(msg);
      }else repData=msg;
    }else if(cfl->canEncode(msg)){
      repData=cfl->fromUnicode(msg);
    }else{
      QTextStream stream(msg);
      stream.setCodec(QTextCodec::codecForName("UTF-8"));
      repData=msg;
    }
  }else repData=msg;

  parse();

  int sCount=0;
  do{
    sCount=repSections.count();
    QMutableHashIterator< QString,QString > i(repSections);
    while(i.hasNext()){
      i.next();
      if(!i.value().isEmpty()) continue;

      rep.setFileName(path+"/"+i.key());
      if(!rep.open(QFile::ReadOnly)){
        setError(rep.errorString());
        return false;
      }

      QByteArray data=rep.readAll();
      if(rep.error()!=QFile::NoError){
        setError(rep.errorString());
        rep.close();
        return false;
      }
      rep.close();

      QTextCodec *cfcs=QTextCodec::codecForHtml(data,0);
      if(cfcs){
        QTextCodec *cfl=QTextCodec::codecForLocale();
        if(cfcs!=cfl){
          QString intenalMsg=cfcs->toUnicode(data);
          if(cfl && cfl->canEncode(intenalMsg)){
            i.setValue(cfl->fromUnicode(intenalMsg));
          }else if(cfl->canEncode(data)){
            i.setValue(cfl->fromUnicode(data));
          }else i.setValue(data);
        }else if(cfl->canEncode(data)){
          i.setValue(cfl->fromUnicode(data));
        }else{
          QTextStream stream(data);
          stream.setCodec(QTextCodec::codecForName("UTF-8"));
          i.setValue(data);
        }
      }else i.setValue(data);

      parse(i.key());
    }
  }while(sCount<repSections.count());

  if(sCount>0) return parse();

  return true;
}

QStringList HtmlReport::keys(const QString &section) const{
  if(section.isEmpty()) return repKeys.keys();

  return sectionsKeys.value(section).keys();
}

QStringList HtmlReport::sections() const{
  return repSections.keys();
}

void HtmlReport::assign(QAbstractItemModel *model){
  if(!model) return;

  repModel=model;
}

bool HtmlReport::assign(const QString &key, const QString &fieldName){
  if(!repModel){
    setError(tr("Модель данных отчёта не определена"));
    return false;
  }
  if(!repKeys.contains(key)){
    setError(tr("Ключ %1 отсутствует в отчёте").arg(key));
    return false;
  }
  if(fieldName.simplified().isEmpty()){
    setError(tr("Указано пустое наименование поля"));
    return false;
  }

  repKeys[key].field=fieldName;
  return true;
}

bool HtmlReport::assign(const QString &key, const QVariant &val){
  if(!repKeys.contains(key)){
    setError(tr("Ключ %1 отсутствует в отчёте").arg(key));
    return false;
  }
  if(!val.isValid()){
    setError(tr("Указано пустое значение"));
    return false;
  }

  repKeys[key].value=val.toString();
  return true;
}

bool HtmlReport::assign(const QString &section, QAbstractItemModel *model){
  if(!model) return false;
  if(!repSections.contains(section)){
    setError(tr("Секция %1 отсутствует в отчёте").arg(section));
    return false;
  }

  if(sectionsModels.contains(section)) sectionsModels[section]=model;
  else sectionsModels.insert(section,model);
  return true;
}

bool HtmlReport::assign(const QString &section, const QString &key,
                        const QString &fieldName){
  if(!repSections.contains(section)){
    setError(tr("Секция %1 отсутствует в отчёте").arg(section));
    return false;
  }
  if(!sectionsModels.contains(section)){
    setError(tr("Модель данных секции %1 не определена").arg(section));
    return false;
  }
  if(!sectionsKeys.value(section).contains(key)){
    setError(tr("Ключ %1 отсутствует в секции %2").arg(key).arg(section));
    return false;
  }
  if(fieldName.simplified().isEmpty()){
    setError(tr("Указано пустое наименование поля"));
    return false;
  }

  sectionsKeys[section][key].field=fieldName;
  return true;
}

bool HtmlReport::assign(const QString &section, const QString &key,
                        const QVariant &val){
  if(!repSections.contains(section)){
    setError(tr("Секция %1 отсутствует в отчёте").arg(section));
    return false;
  }
  if(!sectionsModels.contains(section)){
    setError(tr("Модель данных секции %1 не определена").arg(section));
    return false;
  }
  if(!sectionsKeys.value(section).contains(key)){
    setError(tr("Ключ %1 отсутствует в секции %2").arg(key).arg(section));
    return false;
  }
  if(val.isNull()){
    setError(tr("Указано пустое значение"));
    return false;
  }

  sectionsKeys[section][key].value=val.toString();
  return true;
}

void HtmlReport::reset(){
  parse();
  errStr.clear();
}

void HtmlReport::clear(){
  sectionsKeys.clear();
  sectionsModels.clear();
  repSections.clear();
  repKeys.clear();
  generated.clear();
  repModel=NULL;
  repData.clear();
  errStr.clear();
}

QString HtmlReport::generate(){
  if(repData.isEmpty()){
    setError(tr("Отчёт пуст"));
    return QString();
  }

  generated=repData;
  // убираем экранирующие символы
  generated.replace("$$","$");

  if(repModel){
    if(repModel->rowCount()==0){
      setError(tr("Модель данных для отчёта пуста"));
      return QString();
    }
    if(repModel->rowCount()>1)
      setError(tr("Модель данных для отчёта содержит более 1 строки. "
                  "Будет использована только первая"));
  }

  generated=fillKeys();

  QHashIterator< QString,QString > si(repSections);
  while(si.hasNext()){
    si.next();
    generated.replace(tr("<!--section \"%1\"-->").arg(si.key()),
                      fillSection(si.key()));
  }

  return generated;
}

bool HtmlReport::parse(const QString &sectionName){
  if(!sectionName.isEmpty()) insertedSections++;
  if(insertedSections>MAX_INSERTED_SECTIONS){
    setError(tr("Превышено максимальное число (%1) вложенных секций")
             .arg(MAX_INSERTED_SECTIONS));
    insertedSections--;
    return false;
  }

  // собираем ключи
  QString data=(sectionName.isEmpty()?repData:repSections.value(sectionName));
//  ReportKeys keys=(sectionName.isEmpty()?repKeys:sectionsKeys[sectionName]);

  while(data.contains("$")){
    data.remove(0,data.indexOf("$")+1);
    if(data.at(1)=='$'){
      data.remove(0,1);
      continue;
    }
    QString key="$"+data.left(data.indexOf("$")+1);
    if(!key.isEmpty()){
      data.prepend("$");
      data.remove(key);
    }
    if(!key.isEmpty() &&
       !(sectionName.isEmpty()?repKeys:sectionsKeys[sectionName]).contains(key))
      (sectionName.isEmpty()?repKeys:sectionsKeys[sectionName]).insert(key,ReportKey());
  }

  if(sectionName.isEmpty()) generated=repData;

  // собираем секции
  data=(sectionName.isEmpty()?repData:repSections.value(sectionName));
  if(!data.isEmpty() && !sectionName.isEmpty())
    generated.replace(tr("<!--section \"%1\"-->").arg(sectionName),data);

  while(data.contains("<!--section")){
//    data.remove(0,data.indexOf("<!--section"));
//    QString section=data.left(data.indexOf("-->"));
//    data.remove(section);
//    section.remove(0,section.indexOf("\""));
//    section.chop(section.lastIndexOf("\""));
    QString section=getFirstSectionName(data);
    data.remove(tr("<!--section \"%1\"-->").arg(section));

    if(!section.isEmpty() && !repSections.contains(section))
      repSections.insert(section,QString());

    if(!repSections.value(section).isEmpty()){
      generated.replace(tr("<!--section \"%1\"-->").arg(section),
                        repSections.value(section));
      if(insertedSections<=MAX_INSERTED_SECTIONS)
        if(!parse(section)) return false;
    }
  }

  if(insertedSections>0) insertedSections--;
  return true;
}

QString HtmlReport::fillKeys(const QString &section,
                             const QString &iData, const int row){
  ReportKeys keys=(section.isEmpty())?repKeys:sectionsKeys[section];
  QAbstractItemModel *model=(section.isEmpty())?repModel:sectionsModels[section];
  QString data=(iData.isEmpty()?
                  (section.isEmpty()?repData:repSections.value(section)):iData);

  QHashIterator< QString,ReportKey > ki(keys);
  while(ki.hasNext()){
    ki.next();
    if(!ki.value().field.isEmpty()){
      if(model){
        /*generated*/data.replace(ki.key(),
                          model->index(
                            row,MFCCore::findColumn(
                              model,ki.value().field)).data().toString());
      }else{
        setError(tr("Модель данных для ")+
                 (section.isEmpty()?tr("отчёта"):tr("секции %1").arg(section))+
                 tr(" пуста"));
      }
    }else /*generated*/data.replace(ki.key(),ki.value().value);
  }

  return data;
}

QString HtmlReport::fillSection(const QString &name){
  if(name.isEmpty()) return QString();
  insertedSections++;
  if(insertedSections>MAX_INSERTED_SECTIONS){
    setError(tr("Превышено максимальное число (%1) вложенных секций")
             .arg(MAX_INSERTED_SECTIONS));
    insertedSections--;
    return QString();
  }
  if(repSections.value(name).isEmpty()){
    setError(tr("Секция %1 пуста").arg(name));
    insertedSections--;
    return QString();
  }

  QString data=repSections.value(name);

  // проверяем наличие подсекции: generated.contains("<!--section ")
  if(data.contains("<!--section ")){
    QString section=getFirstSectionName(data);
    data.replace(tr("<!--section \"%1\"-->").arg(section),fillSection(section));
  }

  QString secData;
  // если с секцией связана модель, повторяем содержимое секции
  // model.rowCount() раз
  if(sectionsModels.value(name)){
    QAbstractItemModel *model=sectionsModels.value(name);
    for(int r=0;r<model->rowCount();r++){
      emit rowSelected(model,r);
      secData+=fillKeys(name,data,r);
    }
  }else secData=fillKeys(name,data);

  insertedSections--;
  return secData;
}

void HtmlReport::set_error(const QString &str, const QString file,
                           const int line){
  LogWarning()<<file<<tr("(")<<line<<tr("): ")<<str;
  emit error(str);
}

QString HtmlReport::getFirstSectionName(QString data){
  data.remove(0,data.indexOf("<!--section")+11);
  QString section=data.left(data.indexOf("-->"));
  section.remove(0,section.indexOf("\"")+1);
  section.truncate(section.lastIndexOf("\""));
  return section;
}

QByteArray HtmlReport::replaceMeta(const QByteArray &msg,QTextCodec *to){
  // <meta content="text/html; charset=UTF-8" http-equiv="content-type">
  QByteArray retMsg=msg.left(msg.toLower().indexOf("<meta"));
  QByteArray str=msg.mid(msg.toLower().indexOf("<meta"));
  if(retMsg.length()==msg.length()) return retMsg;
  if(retMsg.length()==0 && str.length()==0) return retMsg;
  retMsg+=tr("<meta content=\"text/html; charset=%1\" "
             "http-equiv=\"content-type\">").arg(QString(to->name()));

  // вырезаем оставшиеся <meta >
  while(str.toLower().contains("<meta")){
    QByteArray meta=str.left(str.indexOf(">")+1);
    str.replace(meta,"");
    retMsg+=str.left(str.toLower().indexOf("<meta"));
    str=str.mid(str.toLower().indexOf("<meta"));
  }
  if(str.length()>0) retMsg+=str;

  return retMsg;
}
