#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlField>
#include "requireddocs.h"
#include "amslogger.h"
#include "mfccore.h"

RequiredDocs::RequiredDocs(QSqlDatabase db, QObject *parent):
  QObject(parent),mdl(new ReqDocsModel(this)),m_DB(db)
{
  init();
}

RequiredDocs::RequiredDocs(QVariant serviceID,
                           QSqlDatabase db, QString se_alias,
                           QObject *parent) :
  QObject(parent),mdl(new ReqDocsModel(this)),
  m_DB(db),srv_id(serviceID)
{
  Q_UNUSED(se_alias)

  init();

  // dt.aname as \"Наименование\"
  // sd.required as \"Необходимый\"
  // dt.organ as \"Предоставляющий орган\"
  // dt.organ_addr as \"Контакты органа\"
  // dt.requirements as \"Требования\"
  QSqlQuery qry(m_DB);

  QString qryStr=tr(
//        "SELECT sd.id,sd.result,sd.required,sd.service_id,sd.priority,"
//        "    (SELECT dtc.doc_categories_id"
//        "      FROM doctypes_categories dtc"
//        "      WHERE dt.id=dtc.doctypes_id) as doc_categories_id,"
//        "    dt.id as doctypes_id,"
//        "    (SELECT dc.category"
//        "      FROM doctypes_categories dtc, doc_categories dc"
//        "      WHERE dt.id=dtc.doctypes_id AND dtc.doc_categories_id=dc.id) as category,"
//        "    dt.aname,dt.organ,dt.organ_addr,dt.direction_id,dt.requirements"
//        "  FROM servicedocs sd, doctypes dt"
//        "  WHERE sd.service_id=%1 AND sd.iddoctypes=dt.id"
//        "  ORDER BY sd.priority");
        "SELECT sd.id,sd.result,sd.required,sd.service_id,sd.priority,"
        "  (SELECT dtc.doc_categories_id"
        "    FROM doctypes_categories dtc"
        "    WHERE (sd.iddoctypes=dtc.doctypes_id "
        "        OR sd.doc_categories_id=dtc.doc_categories_id) "
        "      AND NOT sd.doc_categories_id IS NULL) as doc_categories_id,"
        "  (SELECT dt.id FROM doctypes dt WHERE sd.iddoctypes=dt.id) as doctypes_id,"
        "  (SELECT dc.category"
        "    FROM doc_categories dc"
        "    WHERE sd.doc_categories_id=dc.id) as category,"
        "  (SELECT dt.aname FROM doctypes dt WHERE sd.iddoctypes=dt.id) as aname,"
        "  (SELECT dt.organ FROM doctypes dt WHERE sd.iddoctypes=dt.id) as organ,"
        "  (SELECT dt.organ_addr FROM doctypes dt WHERE sd.iddoctypes=dt.id) as organ_addr,"
        "  (SELECT dt.direction_id FROM doctypes dt WHERE sd.iddoctypes=dt.id) as direction_id,"
        "  (SELECT dt.requirements FROM doctypes dt WHERE sd.iddoctypes=dt.id) as requirements "
        "FROM servicedocs sd "
        "WHERE sd.service_id=%1 "
        "ORDER BY sd.priority");
  qryStr=qryStr.simplified().arg(serviceID.toString());
  if(!qry.exec(qryStr)){
    setError(tr("Ошибка получения списка требуемых документов: %1 QUERY: %2")
             .arg(qry.lastError().text()).arg(qry.lastQuery()));
    return;
  }
  while(qry.next()){
    addRequiredDoc(qry.record().value("aname"),
                   qry.record().value("required").toBool(),1,
                   qry.record().value("category"),
                   qry.record().value("requirements"),
                   qry.record().value("organ"),
                   qry.record().value("organ_addr"),
                   qry.record().value("priority").toInt());
  }
}

RequiredDocs::~RequiredDocs(){
//  mdl->deleteLater();
  delete mdl;
  while(!categories.isEmpty()){
    DocType *dt = categories.key( categories.values().first() );
    categories.remove( dt );
    delete dt;
  }
}

bool RequiredDocs::addRequiredDoc(const QVariant &type, const bool required,
                                  const int amount,const QVariant &category,
                                  const QVariant &requirements,
                                  const QVariant &organ,
                                  const QVariant &organ_addr,int priority){
//  if(type.isNull()) return false;

  QVariant cat=category;
  if(cat.isNull()){
    QMapIterator< DocType*,QString > i(categories);
    while(i.hasNext()){
      i.next();
      if(i.key()->name==type.toString()){
        cat=i.value();
        break;
      }
    }
  }

  return mdl->addDocument(type.toString(),required,amount,cat.toString(),
                   requirements.toString(),organ.toString(),
                   organ_addr.toString(),priority);
}

bool RequiredDocs::setRequiredDocAmount(const QVariant &type, const int amount){
  return mdl->setAmount(type.toString(),amount);
}

bool RequiredDocs::setDocTypeRequired(const QVariant &type, const bool required){
  return mdl->setRequired(type.toString(),required);
}

void RequiredDocs::useDocType(const QVariant &type){
  if(type.isNull()) return;
  mdl->useDocType(type.toString());
}

void RequiredDocs::useDocIndex(const QModelIndex &index){
  mdl->useDocIndex(index);
}

bool RequiredDocs::removeRequiredDoc(const QVariant &type){
  return mdl->removeDocument(type.toString());
}

QAbstractItemModel *RequiredDocs::model() const{
  return mdl;
}

QVariantList RequiredDocs::requiredDocTypes() const{
  QVariantList list=QVariantList();

  foreach(QString type,mdl->requiredDocTypes()) list<<type;

  return list;
}

QVariantList RequiredDocs::allDocTypes() const{
  QVariantList list=QVariantList();

  foreach(QString type,mdl->allDocTypes()) list<<type;

  return list;
}

int RequiredDocs::requiredDocAmount(const QVariant &type) const{
  return mdl->requiredDocAmount(type.toString());
}

int RequiredDocs::remainDocAmount(const QVariant &type) const{
  return mdl->remainDocAmount(type.toString());
}

QString RequiredDocs::errorString() const{
  return errStr;
}

QVariant RequiredDocs::serviceID() const{
  return srv_id;
}

void RequiredDocs::init(){
//  QStringList labels;
//  labels<<tr("Наименование")<<tr("Необходимый")<<tr("Количество")<<
//          tr("Добавлено")<<tr("Образец")<<tr("Требования")<<
//          tr("Предоставляющий орган")<<tr("Контакты органа");
//  mdl->setHorizontalHeaderLabels(labels);
//  int_mdl->setHorizontalHeaderLabels(labels);

  QSqlQuery qry(m_DB);
  QString qryStr=tr("SELECT dc.category,dt.aname,dt.requirements,dt.organ,"
                    "  dt.organ_addr "
                    "FROM doctypes_categories dtc,doc_categories dc,doctypes dt "
                    "WHERE dt.id=dtc.doctypes_id "
                    "  AND dc.id=dtc.doc_categories_id");
  if(!qry.exec(qryStr.simplified())){
    setError(tr("Ошибка получения списка категорий документов: %1 QUERY: %2")
             .arg(qry.lastError().text()).arg(qry.lastQuery()));
    return;
  }
  while(qry.next()){
    DocType *dt=new DocType;
    dt->name=qry.record().value("aname").toString();
    dt->requirements=qry.record().value("requirements").toString();
    dt->organ=qry.record().value("organ").toString();
    dt->organ_addr=qry.record().value("organ_addr").toString();
    categories.insert(dt,qry.record().value("category").toString());
  }
}

void RequiredDocs::reset(){
  mdl->reset();

  // добавим документы, входящие в категории уже добавленных
  QStringList types=mdl->allDocTypes();
  foreach(QString type,types){
    QString cat;
    QMapIterator< DocType*,QString > i(categories);

    while(i.hasNext()){
      i.next();
      if(i.key()->name==type){
        cat=i.value();
        break;
      }
    }

    i.toFront();
    while(i.hasNext()){
      i.next();
      if(i.value()==cat && !types.contains(i.key()->name))
        mdl->addDocument(i.key()->name,false,0,cat,"","","");
    }
  }
}

void RequiredDocs::setError(const QString &str){
  LogDebug()<<str;
  errStr="RequiredDocs: "+str;
  emit error(errStr);
}
