#include <QMetaProperty>
#include "documentsmodel.h"
#include "amslogger.h"

DocumentsModel::DocumentsModel(QObject *parent):QAbstractItemModel(parent),
  isNewVisible(true)
{
}

DocumentsModel::~DocumentsModel(){
  LogDebug()<<"~DocumentsModel() BEGIN";
  clear();
  LogDebug()<<"~DocumentsModel() END";
}

int DocumentsModel::rowCount(const QModelIndex &/*parent*/) const{
  if(!isNewVisible){
    int c=0;
    foreach(MFCDocument *doc,docs)
      if(!newDocs.contains(doc)) c++;
    return c;
  }
  return docs.count();
}

int DocumentsModel::columnCount(const QModelIndex &/*parent*/) const{
  if(rowCount()>0){
    int c=0;
    foreach(MFCDocument *doc,docs){
      int ind=doc->metaObject()->propertyOffset();
      // columnCount = obj.propertyCount()+"id"+dynamicPropertyNames().count()
      int cd=doc->metaObject()->propertyCount()+1-ind+
          doc->dynamicPropertyNames().count();
      if(cd>c) c=cd;
    }
    return c;
  }else return 0;
}

QVariant DocumentsModel::headerData(int section, Qt::Orientation orientation,
                                    int role) const{
  if(rowCount()==0) return QVariant();
  if(role!=Qt::DisplayRole && role!=Qt::EditRole) return QVariant();

  if(orientation==Qt::Vertical){
    if(section>=rowCount()) return QVariant();
    return QString::number(section+1);
  }

  int c=columnCount();
//  if(section==c-1) return "id";
  if(section>=c) return QVariant();

  MFCDocument *doc=docs.values().first();
  if(!doc) return QVariant();
  QString pName=propertyName(doc,section);

  if(pName=="type") return tr("Вид");
  else if(pName=="name") return tr("Наименование\n(крат. содержание)");
  else if(pName=="series") return tr("Серия");
  else if(pName=="number") return tr("№");
  else if(pName=="date") return tr("Дата выдачи");
  else if(pName=="expires") return tr("Действителен до");
  else if(pName=="agency") return tr("Выдан");
  else if(pName=="created") return tr("Создан в базе");
  else return pName;
}

QModelIndex DocumentsModel::index(int row, int column,
                                  const QModelIndex &/*parent*/) const{
  if(row<0 || column<0) return QModelIndex();
  if(rowCount()==0) return QModelIndex();
  if(row>=rowCount()) return QModelIndex();
  if(column>=columnCount()) return QModelIndex();
  if(!isNewVisible && newDocs.contains(docs.value(row))) return QModelIndex();
  return createIndex(row,column,docs.value(row));
}

QModelIndex DocumentsModel::parent(const QModelIndex &/*child*/) const{
  return QModelIndex();
}

QVariant DocumentsModel::data(const QModelIndex &index, int role) const{
  if(role!=Qt::DisplayRole && role!=Qt::EditRole) return QVariant();
  if(!index.isValid()) return QVariant();
//  if(rowCount()==0) return QVariant();
  if(!this->index(index.row(),index.column(),QModelIndex()).isValid())
    return QVariant();

//  if(index.column()==columnCount()-1) return ids.value(index.row());

  MFCDocument *doc=docs.value(index.row());
  if(!doc) return QVariant();
  return doc->property(propertyName(doc,index.column()));
}

Qt::ItemFlags DocumentsModel::flags(const QModelIndex &index) const{
  if(!index.isValid()) return Qt::NoItemFlags;
  return Qt::ItemIsEditable|Qt::ItemIsEnabled|Qt::ItemIsSelectable;
}

int DocumentsModel::findColumn(QString name) const{
  if(columnCount()<=0) return -1;

  for(int i=0;i<columnCount();i++){
    int r=0;
    QString pName;
    do{
      MFCDocument *doc=docs.value(r);
      if(!doc) return -1;
      pName=propertyName(doc,i);
      r++;
    }while(pName.isEmpty() || r<docs.count());
    if(headerData(i,Qt::Horizontal,Qt::DisplayRole).toString()==name ||
       pName==name)
      return i;
  }

  return -1;
}

void DocumentsModel::clear(){
  foreach(MFCDocument *doc,docs){
    if(!doc) continue;
    doc->disconnect();
    doc->deleteLater();
  }
  docs.clear();
//  ids.clear();
  newDocs.clear();
  removedIDs.clear();
}

QList< MFCDocument* > DocumentsModel::documents() const{
  return docs.values();
}

QList< MFCDocument* > DocumentsModel::newDocuments() const{
  return newDocs;
}

MFCDocument* DocumentsModel::document(const int row) const{
  if(row<0 || row>=rowCount()) return NULL;
  return docs.value(row);
}

MFCDocument* DocumentsModel::document(const QModelIndex &index) const{
  return document(index.row());
}

MFCDocument* DocumentsModel::document(const QVariant &id) const{
  if(id.isNull()) return NULL;
//  if(!ids.values().contains(id)) return NULL;
//  return document(ids.key(id));
  foreach(MFCDocument *doc,docs)
    if(documentID(doc)==id) return doc;
  return NULL;
}

QVariant DocumentsModel::documentID(MFCDocument *doc) const{
//  QVariant id;
//  if(!doc) return id;

//  foreach(int r,docs.keys(doc)){
//    QVariant rid=ids.value(r);
//    if(!rid.isNull()) id=rid;
//  }

//  LogDebug()<<"type ="<<doc->type()<<"id ="<<id;
//  return id;
  return doc->property("id");
}

bool DocumentsModel::isNew(MFCDocument *doc) const{
  return newDocs.contains(doc);
}

bool DocumentsModel::removeRows(int row, int count, const QModelIndex &/*parent*/){
  if(rowCount()<=0 || row<0 || count<1 || row+count>rowCount()) return false;
  bool res=true;
  beginRemoveRows(QModelIndex(),row,count);
  for(int r=row;r<row+count;r++){
    res=removeDocument(r);
    if(!res) return res;
  }
  recalc();
  endRemoveRows();
  return res;
}

bool DocumentsModel::isNewDocumentsVisible() const{
  return isNewVisible;
}

void DocumentsModel::setNewDocumentsVisible(bool v){
  isNewVisible=v;
}

QVariantList DocumentsModel::removedDocumentsIDs() const{
  return removedIDs;
}

void DocumentsModel::setDocumentID(MFCDocument *doc, QVariant id){
  if(!doc || id.isNull()) return;

//  foreach(int r,docs.keys(doc)){
//    ids[r]=id;
//  }
  doc->setProperty("id",id);
}

bool DocumentsModel::addDocument(MFCDocument *doc, const QVariant id,
                                 const bool isNew){
  if(!doc) return false;
  if(docs.values().contains(doc)){
    LogDebug()<<doc->type()<<"already exists: forbidden!";
    return false;
  }

  if(columnCount()==0){
    int ind=doc->metaObject()->propertyOffset();
    beginInsertColumns(QModelIndex(),0,doc->metaObject()->propertyCount()-ind);
    endInsertColumns();
  }

  int rCount=docs.count();
  if(isNewVisible || !isNew) beginInsertRows(QModelIndex(),rCount,rCount);

  QMap< int,MFCDocument* >::iterator i=docs.insert(rCount,doc);
  doc->setParent(this);
  connect(doc,SIGNAL(destroyed()),
          SLOT(documentDestroyed()),Qt::UniqueConnection);
//  QMap< int,QVariant >::iterator ii=ids.insert(rCount,id);
//  LogDebug()<<"r ="<<ii.key()<<"ID ="<<ii.value();
//  LogDebug()<<doc->type()<<"rCount ="<<rCount<<"r ="<<i.key()<<"id ="<<id<<
//              documentID(doc);
  setDocumentID(doc,id);
  if(isNew){
//    LogDebug()<<"as new";
    newDocs.append(doc);
  }

  if(isNewVisible || !isNew) endInsertRows();
  emit documentAdded(doc);
  return true;
}

bool DocumentsModel::addDocument(const QString doc_type, const QDate doc_date,
                                 const QString doc_name,
                                 const QString doc_series,
                                 const QString doc_number,
                                 const QDate doc_expires,
                                 const QString doc_agency,
                                 const QDateTime doc_created,
                                 const QVariant id, const bool isNew){
  MFCDocument *doc=new MFCDocument(this);
  doc->setType(doc_type);
  doc->setDate(doc_date);
  doc->setName(doc_name);
  doc->setSeries(doc_series);
  doc->setNumber(doc_number);
  doc->setExpiresDate(doc_expires);
  doc->setAgency(doc_agency);
  doc->setCreateDate(doc_created);

  return addDocument(doc,id,isNew);
}

bool DocumentsModel::removeDocument(MFCDocument *doc){
  if(!doc) return false;
  QList< int > i=docs.keys(doc);
  if(i.count()<=0) return false;

  foreach(int r,i){
    beginRemoveRows(QModelIndex(),r,r);
    newDocs.removeAll(doc);
//    QVariant id=ids.take(r);
    QVariant id=documentID(doc);
    if(!id.isNull()) removedIDs<<id;
    docs.remove(r);
    recalc();
    endRemoveRows();
  }
  emit documentRemoved(doc);
  return true;
}

bool DocumentsModel::removeDocument(const int row){
  if(row<0 || row>=rowCount()) return false;

  beginRemoveRows(QModelIndex(),row,row);
  MFCDocument *doc=docs.take(row);
//  QVariant id=ids.take(row);
  QVariant id=documentID(doc);
  if(!id.isNull()) removedIDs<<id;
  newDocs.removeAll(doc);
  recalc();
  endRemoveRows();
  emit documentRemoved(doc);
  return true;
}

void DocumentsModel::documentDestroyed(){
  MFCDocument *doc=static_cast< MFCDocument* >(sender());
  removeDocument(doc);
}

void DocumentsModel::recalc(){
  QList< int > keys=docs.keys();
  for(int r=0;r<rowCount();r++){
    int key=keys.value(r,-1);
    if(key>r){
      MFCDocument *doc=docs.take(key);
//      QVariant id=ids.take(key);
      docs.insert(r,doc);
//      ids.insert(r,id);
    }
  }
}

QByteArray DocumentsModel::propertyName(QObject *obj, int idx) const{
  if(obj->metaObject()->propertyCount()<=
     idx+obj->metaObject()->propertyOffset()){
    return obj->dynamicPropertyNames().value(
          obj->metaObject()->propertyOffset()+idx-
          obj->metaObject()->propertyCount());
  }
  return obj->metaObject()->property(
        idx+obj->metaObject()->propertyOffset()).name();
}
