#include <QMetaProperty>
#include "documentsmodel.h"
#include "amslogger.h"

DocumentsModel::DocumentsModel(QObject *parent):QAbstractItemModel(parent),
  isNewVisible(true)
{
}

DocumentsModel::~DocumentsModel(){
//  LogDebug()<<"~DocumentsModel() BEGIN";
  clear();
//  LogDebug()<<"~DocumentsModel() END";
}

int DocumentsModel::rowCount(const QModelIndex &/*parent*/) const{
  if(!isNewVisible){
    int c=0;
    foreach(MFCDocumentInfo *doc,docs) if(!newDocs.contains(doc)) c++;
    return c;
  }
  return docs.count();
}

int DocumentsModel::columnCount(const QModelIndex &/*parent*/) const{
//  if(rowCount()>0){
//    int c=0;
//    foreach(MFCDocumentInfo *doc,docs){
//      int ind=doc->metaObject()->propertyOffset();
//      int cd=doc->metaObject()->propertyCount()+1-ind+
//          doc->dynamicPropertyNames().count();
//      if(cd>c) c=cd;
//    }
//    return c;
//  }else return 0;
  return columnsNames.count();
}

QVariant DocumentsModel::headerData(int section, Qt::Orientation orientation,
                                    int role) const{
  if(rowCount()==0) return QVariant();
  if(role!=Qt::DisplayRole/* && role!=Qt::EditRole*/) return QVariant();

  if(orientation==Qt::Vertical){
    if(section>=rowCount()) return QVariant();
    return QString::number(section+1);
  }

  int c=columnCount();
  if(section>=c) return QVariant();
  return columnsNames.value(section);

//  MFCDocumentInfo *doc=docs.values().first();
//  if(!doc) return QVariant();
//  QString pName=propertyName(doc,section);

//  if(pName=="type") return tr("Вид");
//  else if(pName=="name") return tr("Наименование\n(крат. содержание)");
//  else if(pName=="series") return tr("Серия");
//  else if(pName=="number") return tr("№");
//  else if(pName=="date") return tr("Дата выдачи");
//  else if(pName=="expires") return tr("Действителен до");
//  else if(pName=="agency") return tr("Выдан");
//  else if(pName=="created") return tr("Создан в базе");
//  else return pName;
}

QModelIndex DocumentsModel::index(int row, int column,
                                  const QModelIndex &/*parent*/) const{
  if(row<0 || column<0) return QModelIndex();
  if(rowCount()==0) return QModelIndex();
  if(row>=rowCount()) return QModelIndex();
  if(column>=columnCount()) return QModelIndex();
  if(!isNewVisible && newDocs.contains(docs.value(row))) return QModelIndex();
  return createIndex(row,column/*,docs.value(row)*/);
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

  int row=index.row();
  if(!isNewVisible) while(newDocs.contains(docs.value(row))) row++;
  MFCDocumentInfo *doc=docs.value(row);
  if(!doc) return QVariant();
  return doc->property(/*propertyName(doc,index.column())*/
                       pnConvert(columnsNames.value(index.column()).toString()).toLocal8Bit());
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
      MFCDocumentInfo *doc=docs.value(r);
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
//  LogDebug()<<"clear() "<<objectName()<<" BEGIN";
  foreach(MFCDocumentInfo *doc,docs){
//    LogDebug()<<"doc ="<<doc;
//    doc->disconnect(this);
    disconnect(doc,0,this,0);
//    MFCDocumentInfo::remove(doc);
  }
  docs.clear();
//  ids.clear();
  newDocs.clear();
  removedIDs.clear();
//  LogDebug()<<"clear() END";
}

QList< MFCDocumentInfo* > DocumentsModel::documents() const{
  return docs.values();
}

QList< MFCDocumentInfo* > DocumentsModel::newDocuments() const{
  return newDocs;
}

MFCDocumentInfo* DocumentsModel::document(const int row) const{
  if(row<0 || row>=rowCount()) return NULL;
  return docs.value(row);
}

MFCDocumentInfo* DocumentsModel::document(const QModelIndex &index) const{
  return document(index.row());
}

MFCDocumentInfo* DocumentsModel::document(const QVariant &id) const{
  if(id.isNull()) return NULL;
//  if(!ids.values().contains(id)) return NULL;
//  return document(ids.key(id));
  foreach(MFCDocumentInfo *doc,docs)
    if(documentID(doc)==id) return doc;
  return NULL;
}

QVariant DocumentsModel::documentID(MFCDocumentInfo *doc) const{
//  LogDebug()<<"documentID(MFCDocumentInfo*) BEGIN";
  if(!doc) return QVariant();
//  LogDebug()<<"doc="<<doc;
  if(!docs.values().contains(doc)){
//    LogDebug()<<"documentID("<<doc<<") END";
    return QVariant();
  }

  QVariant id=doc->property("id");
//  LogDebug()<<"documentID("<<doc<<") END";
  return id;
}

bool DocumentsModel::isNew(MFCDocumentInfo *doc) const{
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

void DocumentsModel::setDocumentID(MFCDocumentInfo *doc, QVariant id){
  if(!doc || id.isNull()) return;

//  foreach(int r,docs.keys(doc)){
//    ids[r]=id;
//  }
  doc->setProperty("id",id);
}

bool DocumentsModel::addDocument(MFCDocumentInfo *doc, const QVariant id,
                                 const bool isNew){
  if(!doc) return false;
  if(docs.values().contains(doc)){
    LogDebug()<<doc->type()<<"(doc ="<<doc<<") already exists: forbidden!";
    return false;
  }

  if(columnCount()==0){
    int ind=doc->metaObject()->propertyOffset();
    beginInsertColumns(QModelIndex(),0,doc->metaObject()->propertyCount()-ind);
    endInsertColumns();
  }

  int rCount=docs.count();
  int correction=isNewVisible?0:newDocs.count();
  if(isNewVisible || !isNew)
    beginInsertRows(QModelIndex(),rCount-correction,rCount-correction);

  /*QMap< int,MFCDocumentInfo* >::iterator i=*/docs.insert(rCount,doc);
//  doc->setParent(this);
  connect(doc,SIGNAL(destroyed(QObject*)),SLOT(documentDestroyed(QObject*)),
          Qt::UniqueConnection);
  connect(doc,SIGNAL(propertyChanged(QString,QVariant)),
          SLOT(documentChanged(QString,QVariant)),
          Qt::UniqueConnection);
//  QMap< int,QVariant >::iterator ii=ids.insert(rCount,id);
//  LogDebug()<<"r ="<<ii.key()<<"ID ="<<ii.value();
//  LogDebug()<<doc->type()<<"rCount ="<<rCount<<"r ="<<i.key()<<"id ="<<id<<
//              documentID(doc);
  setDocumentID(doc,id);
  if(isNew){
//    LogDebug()<<"as new";
    newDocs.append(doc);
  }

  if(doc->metaObject()->propertyCount()-doc->metaObject()->propertyOffset()+
     doc->dynamicPropertyNames().count()>columnsNames.count()
     && (isNewVisible || !isNew)){

    if(columnsNames.count()==0)
      for(int section=doc->metaObject()->propertyOffset();
          section<doc->metaObject()->propertyCount();section++){
        QString pName=pnConvert(doc->metaObject()->property(section).name());
        columnsNames<<pName;
      }

    foreach(QByteArray pn,doc->dynamicPropertyNames())
      if(!columnsNames.contains(pn)){
        beginInsertColumns(QModelIndex(),columnsNames.count(),
                           columnsNames.count());
//        LogDebug()<<"insert column"<<QLocale::system().quoteString(pn)
//                 <<"to"<<columnsNames.count()<<"section";
        columnsNames<<pn;
        endInsertColumns();
      }
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
  MFCDocumentInfo *doc=MFCDocumentInfo::instance(
        doc_type,doc_name,doc_series,doc_number,doc_date,doc_expires,doc_agency,
        doc_created,this);
//  doc->setProperty("created_in",tr("%1 (%2)").arg(__FILE__).arg(__LINE__));
  doc->setName(doc_name);
  doc->setSeries(doc_series);
  doc->setNumber(doc_number);
  doc->setExpiresDate(doc_expires);
  doc->setAgency(doc_agency);

  return addDocument(doc,id,isNew);
}

bool DocumentsModel::removeDocument(MFCDocumentInfo *doc){
//  LogDebug()<<"removeDocument()"<<objectName()<<"("<<this<<") BEGIN";
  QVariant id=documentID(doc);
  if(!id.isNull()) removedIDs<<id;
  bool res=removeDocument_p(doc);
  if(res) emit documentRemoved(doc);
//  LogDebug()<<"removeDocument("<<doc<<") END";
  return res;
}

bool DocumentsModel::removeDocument(const int row){
//  LogDebug()<<"removeDocument("<<row<<") BEGIN";
  if(row<0 || row>=rowCount()) return false;

  beginRemoveRows(QModelIndex(),row,row);
  MFCDocumentInfo *doc=docs.take(row);
  QVariant id=documentID(doc);
  if(!id.isNull()) removedIDs<<id;
  newDocs.removeAll(doc);
  recalc();
  endRemoveRows();
  emit documentRemoved(doc);
//  LogDebug()<<"removeDocument("<<row<<") ("<<doc<<") END";
  return true;
}

void DocumentsModel::documentDestroyed(QObject *obj){
//  LogDebug()<<"documentDestroyed(QObject*)"<<objectName()<<"("<<this<<") BEGIN";
  if(!obj) return;
//  LogDebug()<<"obj="<<obj;
  MFCDocumentInfo *doc=static_cast< MFCDocumentInfo* >(obj);
  if(doc && docs.values().contains(doc)){
    removeDocument_p(doc);
  }
//  LogDebug()<<"documentDestroyed("<<doc<<") "<<objectName()<<" END";
}

void DocumentsModel::recalc(){
//  LogDebug()<<"recalc() BEGIN";
  QList< int > keys=docs.keys();
  for(int r=0;r<rowCount();r++){
    int key=keys.value(r,-1);
    if(key>r){
      MFCDocumentInfo *doc=docs.take(key);
//      QVariant id=ids.take(key);
      docs.insert(r,doc);
//      ids.insert(r,id);
    }
  }
//  LogDebug()<<"recalc() END";
}

void DocumentsModel::documentChanged( QString propertyName, QVariant propertyValue )
{
  Q_UNUSED(propertyValue)
  MFCDocumentInfo *doc = qobject_cast<MFCDocumentInfo *>( sender() );
  int row = documents().indexOf( doc );
  emit dataChanged( QAbstractItemModel::createIndex( row, columnsNames.indexOf( propertyName ) ),
                    QAbstractItemModel::createIndex( row, columnsNames.indexOf( propertyName ) ) );
}

bool DocumentsModel::removeDocument_p(MFCDocumentInfo *doc){
  if(!doc) return false;
//  LogDebug()<<"doc="<<doc;
  QList< int > i=docs.keys(doc);
  if(i.count()<=0) return false;

  newDocs.removeAll(doc);
  foreach(int r,i){
    beginRemoveRows(QModelIndex(),r,r);
    docs.remove(r);
    endRemoveRows();
  }
  recalc();
  return true;
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

QString DocumentsModel::pnConvert(QString pn) const
{
  QString pName=pn;
  if(pName=="type") pName=tr("Вид");
  else if(pName=="name") pName=tr("Наименование\n(крат. содержание)");
  else if(pName=="series") pName=tr("Серия");
  else if(pName=="number") pName=tr("№");
  else if(pName=="date") pName=tr("Дата выдачи");
  else if(pName=="expires") pName=tr("Действителен до");
  else if(pName=="agency") pName=tr("Выдан");
  else if(pName=="originalExemplars") pName=tr("Экземпляров оригинала");
  else if(pName=="originalPages") pName=tr("Страниц оригинала");
  else if(pName=="copyExemplars") pName=tr("Экземпляров копии");
  else if(pName=="copyPages") pName=tr("Страниц копии");
  else if(pName=="created") pName=tr("Создан в базе");
  else if(pName==tr("Вид")) pName="type";
  else if(pName==tr("Наименование\n(крат. содержание)")) pName="name";
  else if(pName==tr("Серия")) pName="series";
  else if(pName==tr("№")) pName="number";
  else if(pName==tr("Дата выдачи")) pName="date";
  else if(pName==tr("Действителен до")) pName="expires";
  else if(pName==tr("Выдан")) pName="agency";
  else if(pName==tr("Экземпляров оригинала")) pName="originalExemplars";
  else if(pName==tr("Страниц оригинала")) pName="originalPages";
  else if(pName==tr("Экземпляров копии")) pName="copyExemplars";
  else if(pName==tr("Страниц копии")) pName="copyPages";
  else if(pName==tr("Создан в базе")) pName="created";
  return pName;
}
