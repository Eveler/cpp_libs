#include "reqdocsmodel.h"
#include "amslogger.h"

bool ReqItem::operator <(const ReqItem &other) const{
  LogDebug()<<isRequired()<<other.isRequired()<<priority<<other.priority;
  if(isRequired() && !other.isRequired()) return true;
  return priority<other.priority;
}

QString ReqItem::type() const{
  return data.value(0).toString();
}

void ReqItem::setRequired(bool r){
  if(data.value(1).isValid()) data[1]=r;
}

bool ReqItem::isRequired() const{
  return !data.value(1).isNull() && data.value(1).toBool();
}

void ReqItem::setAmount(int a){
  if(data.value(2).isValid()) data[2]=a;
}

int ReqItem::amount() const{
  return data.value(2).toInt();
}

void ReqItem::use(){
  if(data.value(3).isValid()) data[3]=data.value(3).toInt()+1;
}

int ReqItem::used() const{
  return data.value(3).toInt();
}

void ReqItem::setSample(QString s){
  if(data.value(4).isValid()) data[4]=s;
}

QString ReqItem::sample() const{
  return data.value(4).toString();
}

void ReqItem::reset(){
  if(data.value(3).isValid()) data[3]=0;
}

ReqDocsModel::ReqDocsModel(QObject *parent):QAbstractItemModel(parent){
  headerLabels<<tr("Наименование")<<tr("Необходимый")<<tr("Количество")<<
                tr("Добавлено")<<tr("Образец")<<tr("Требования")<<
                tr("Предоставляющий орган")<<tr("Контакты органа");
}

ReqDocsModel::~ReqDocsModel(){
  qDeleteAll(items);
}

bool lessThen(const ReqItem *i1,const ReqItem *i2){
  if(!i1) return true;
  if(!i2) return false;
  if(i1->isRequired() && !i2->isRequired()) return true;
  return i1->priority<i2->priority;
}

bool ReqDocsModel::addDocument(const QString &type, bool required, int amount,
                               const QString &category,
                               const QString &requirements,
                               const QString &organ, const QString &organ_addr,
                               int priority){
//  if(type.isEmpty()) return false;
//  LogDebug()<<"type ="<<type;
  if(findDocument(type)>=0) return false;

  ReqItem *item=new ReqItem();
  if(category.isEmpty()){
    item->data<<type<<required<<amount<<0<<tr("Образец")<<requirements<<
                organ<<organ_addr;
    item->priority=priority;
    item->parent=NULL;
    items<<item;
//    LogDebug()<<"added as root element";
  }else{
    ReqItem *parent=items.value(findDocument(category));
    if(!parent){
      parent=new ReqItem();
      parent->data<<category<<required<<amount<<0<<QString()<<QString()<<
                  QString()<<QString();
      parent->priority=priority;
      parent->parent=NULL;
      items<<parent;
//      LogDebug()<<"    "<<category<<"added as root element";
    }

    if(!type.isEmpty()){
      item=new ReqItem();
      item->data<<type<<required<<amount<<0<<tr("Образец")<<requirements<<
                  organ<<organ_addr;
      item->priority=priority;
      item->parent=parent;
      parent->children<<item;
      recalc(parent);
//      LogDebug()<<"added as child element";
    }
  }

//  foreach(ReqItem *i,items) LogDebug()<<i->priority<<i->isRequired()<<i->type();
  qStableSort(items.begin(),items.end(),lessThen);
//  foreach(ReqItem *i,items) LogDebug()<<i->priority<<i->isRequired()<<i->type();

  QModelIndex idx;
  int row=0;
  if(item->parent){
    row=visibleRow(item);
    idx=createIndex(visibleRow(item->parent),0,item->parent);
  }else{
    row=visibleRow(item);
//    LogDebug()<<"row ="<<row<<type;
  }
  beginInsertRows(idx,row,row);
  endInsertRows();

  return true;
}

bool ReqDocsModel::removeDocument(const QString &type){
  foreach(ReqItem *parent,items){
    foreach(ReqItem *item,parent->children){
      if(item->type()==type){
        int parentRow=visibleRow(parent);
        QModelIndex parentIdx=index(parentRow,0);
        int row=visibleRow(item);
        beginRemoveRows(parentIdx,row,row);
        parent->children.removeAll(item);
        delete item;
        endRemoveRows();
        if(parent->children.count()==0){
          beginRemoveRows(QModelIndex(),parentRow,parentRow);
          items.removeAll(parent);
          delete parent;
          endRemoveRows();
        }else recalc(parent);
        qStableSort(items.begin(),items.end(),lessThen);
        return true;
      }
    }

    if(parent->type()==type){
      if(parent->children.count()==0){
        int row=visibleRow(parent);
        beginRemoveRows(QModelIndex(),row,row);
        items.removeAll(parent);
        delete parent;
        qStableSort(items.begin(),items.end(),lessThen);
        endRemoveRows();
        return true;
      }else return false;
    }
  }
  return false;
}

int ReqDocsModel::columnCount(const QModelIndex &parent) const{
  Q_UNUSED(parent);
  return headerLabels.count();
}

Qt::ItemFlags ReqDocsModel::flags(const QModelIndex &index) const{
  if(!index.isValid()) return 0;
  return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

QVariant ReqDocsModel::data(const QModelIndex &index, int role) const{
  if(role!=Qt::DisplayRole || !index.isValid()) return QVariant();
  if(index.row()>=rowCount(index.parent())) return QVariant();
  if(index.column()>=columnCount(index.parent())) return QVariant();

  ReqItem *item=static_cast< ReqItem* >(index.internalPointer());
  if(!item) return QVariant();
  return item->data.value(index.column());
}

QVariant ReqDocsModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const{
  if(role!=Qt::DisplayRole) return QVariant();
  if(orientation==Qt::Vertical) return section+1;
  else return headerLabels.value(section);
}

int ReqDocsModel::rowCount(const QModelIndex &parent) const{
  if(parent.isValid()){
    int count=0;
    ReqItem *item=static_cast< ReqItem* >(parent.internalPointer());
    if(!item || !items.contains(item)) return 0;
    foreach(ReqItem* i,item->children){
      if(!i) continue;
      if(i->used()<i->amount() || i->amount()==0) count++;
    }
    return count;
  }else{
    int count=0;
    foreach(ReqItem* i,items){
      if(!i) continue;
      if(i->used()<i->amount() || i->amount()==0) count++;
    }
    return count;
  }
}

QModelIndex ReqDocsModel::index(int row, int column,
                                const QModelIndex &parent) const{
  if(row>=rowCount(parent) || row<0) return QModelIndex();
  if(column>=columnCount(parent) || column<0) return QModelIndex();

  int r=-1;
  int i=0;

  if(parent.isValid()){
    ReqItem *item=static_cast< ReqItem* >(parent.internalPointer());
    if(!item || !items.contains(item)) return QModelIndex();
    do{
      ReqItem *child=item->children.value(i);
      if(child && (child->used()<child->amount() || child->amount()==0)) r++;
      if(r==row) return createIndex(row,column,child);
      i++;
    }while(i<item->children.count());
    return QModelIndex();
  }

  do{
    ReqItem *item=items.value(i);
    if(item && (item->used()<item->amount() || item->amount()==0)) r++;
    if(r==row) return createIndex(row,column,item);
    i++;
  }while(i<items.count());
  return QModelIndex();
}

QModelIndex ReqDocsModel::parent(const QModelIndex &child) const{
  if(!child.isValid()) return QModelIndex();
  ReqItem *item=static_cast< ReqItem* >(child.internalPointer());
  if(!item) return QModelIndex();
  if(!item->parent) return QModelIndex();
  int row=visibleRow(item->parent);
  if(row<0) return QModelIndex();
  return createIndex(row,0,item->parent);
}

//bool ReqDocsModel::hasChildren(const QModelIndex &parent) const{
//  if(!parent.isValid()) return false;
//  ReqItem *item=static_cast< ReqItem* >(parent.internalPointer());
//  if(!item || !items.contains(item)) return false;
//  return item->children.count()>0;
//}

void ReqDocsModel::useDocType(const QString &type){
  foreach(ReqItem *parent,items){
    if(!parent) continue;
    if(parent->type()==type && parent->children.count()==0){
      int row=visibleRow(parent);
      beginRemoveRows(QModelIndex(),row,row);
      parent->use();
      endRemoveRows();
      return;
    }

    foreach(ReqItem *item,parent->children){
      if(item && item->type()==type){
        int row=visibleRow(item);
        QModelIndex idx=createIndex(visibleRow(parent),0,parent);
        beginRemoveRows(idx,row,row);
        item->use();
        endRemoveRows();
        recalc(parent);
        return;
      }
    }
  }
}

void ReqDocsModel::useDocIndex(const QModelIndex &index){
  if(!index.isValid()) return;
  ReqItem *item=static_cast< ReqItem* >(index.internalPointer());
  if(!item) return;
  beginRemoveRows(index.parent(),index.row(),index.row());
  item->use();
  endRemoveRows();
  if(item->parent) recalc(item->parent);
}

QStringList ReqDocsModel::requiredDocTypes() const{
  QStringList list;

  foreach(ReqItem *parent,items){
    if(!parent) continue;
    if(parent->isRequired() && parent->children.count()==0 &&
       parent->used()<parent->amount()){
      list<<parent->type();
      continue;
    }

    foreach(ReqItem *item,parent->children){
      if(item && item->isRequired() && item->used()<item->amount())
        list<<item->type();
    }
  }

  return list;
}

QStringList ReqDocsModel::allDocTypes() const{
  QStringList list;

  foreach(ReqItem *parent,items){
    if(!parent) continue;
    if(parent->children.count()==0 && !parent->sample().isEmpty()){
      list<<parent->type();
      continue;
    }

    foreach(ReqItem *item,parent->children){
      if(item) list<<item->type();
    }
  }

  return list;
}

QStringList ReqDocsModel::categories() const{
  QStringList list;

  foreach(ReqItem *parent,items){
//    if(parent->children.count()==0){
    if(parent->sample().isEmpty()){
      list<<parent->type();
    }
  }

  return list;
}

int ReqDocsModel::requiredDocAmount(const QString &type) const{
  int a=0;

  foreach(ReqItem *parent,items){
    if(parent->isRequired() && parent->children.count()==0 &&
       parent->used()<parent->amount() &&
       (type.isEmpty() || parent->type()==type)){
      a+=parent->amount();
      continue;
    }

    foreach(ReqItem *item,parent->children){
      if(item->isRequired() && item->used()<item->amount() &&
         (type.isEmpty() || item->type()==type))
        a+=item->amount();
    }
  }

  return a;
}

int ReqDocsModel::remainDocAmount(const QString &type) const{
  int a=0;

  foreach(ReqItem *parent,items){
    if(parent->isRequired() && parent->children.count()==0 &&
       parent->used()<parent->amount() &&
       (type.isEmpty() || parent->type()==type)){
      a+=parent->amount()-parent->used();
      continue;
    }

    foreach(ReqItem *item,parent->children){
      if(item->isRequired() && item->used()<item->amount() &&
         (type.isEmpty() || item->type()==type))
        a+=item->amount()-item->used();
    }
  }

  return a;
}

bool ReqDocsModel::setAmount(const QString &type,int amount){
  if(type.isEmpty()) return false;

  foreach(ReqItem *parent,items){
    if(parent->type()==type && parent->children.count()==0){
      parent->setAmount(amount);
      return true;
    }

    foreach(ReqItem *item,parent->children){
      if(item->type()==type){
        item->setAmount(amount);
        recalc(parent);
        return true;
      }
    }
  }

  return false;
}

bool ReqDocsModel::setRequired(const QString &type, bool b){
  if(type.isEmpty()) return false;

  foreach(ReqItem *parent,items){
    if(parent->type()==type && parent->children.count()==0){
      parent->setRequired(b);
      return true;
    }

    foreach(ReqItem *item,parent->children){
      if(item->type()==type){
        item->setRequired(b);
        recalc(parent);
        return true;
      }
    }
  }

  return false;
}

void ReqDocsModel::reset(){
  foreach(ReqItem *parent,items){
    if(parent->children.count()==0){
      parent->reset();
      continue;
    }

    foreach(ReqItem *item,parent->children)
      item->reset();
    recalc(parent);
  }
}

int ReqDocsModel::findDocument(const QString &type, ReqItem *parent) const{
  if(parent){
    foreach(ReqItem *item,parent->children)
      if(item->type()==type) return parent->children.indexOf(item);
  }else{
    foreach(ReqItem *item,items)
      if(item->type()==type) return items.indexOf(item);
  }
  return -1;
}

void ReqDocsModel::recalc(ReqItem *parent){
  int p=0;int a=0;int u=0;
  foreach(ReqItem *i,parent->children){
    if(i->amount()>0){
      if(p==0 || p>i->priority) p=i->priority;
    }
    a+=i->amount();
    u+=i->used();
    if(i->isRequired()) parent->setRequired();
    if(i->used()>=i->amount()){
      int row=visibleRow(i);
      beginRemoveRows(QModelIndex(),row,row);
      endRemoveRows();
    }
  }
  parent->priority=p;
  parent->setAmount(a);
  parent->reset();
  for(int i=0;i<u;i++) parent->use();
  if(parent->used()>=parent->amount()){
    int row=visibleRow(parent);
    beginRemoveRows(QModelIndex(),row,row);
    endRemoveRows();
  }
}

int ReqDocsModel::visibleRow(ReqItem *item) const{
  int row=-1;
  if(!item) return row;

  QList< ReqItem* > list=items;
  if(item->parent) list=item->parent->children;

  row=list.indexOf(item);
  foreach(ReqItem *i,list){
    if(i->used()>=i->amount() && i->amount()>0) row--;
    if(i==item) return row;
  }
  return row;
}
