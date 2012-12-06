#include "pgdb.h"

PgDB::~PgDB(){
  QMapIterator< QString,PgTable* > mp(pgTables);
  while(mp.hasNext()){
    mp.next();
    delete mp.value();
  }
}

QStringList PgDB::tables(){
  errText.clear();
  if(pgTables.count()<1)
    if(!collect()){
      return QStringList();
    }
  return pgTables.keys();
}

PgTable *PgDB::table(const QString tblName){
  errText.clear();
  if(pgTables.count()<1)
    if(!collect()){
      return NULL;
    }
  return pgTables.value(tblName);
}

QStringList PgDB::views(){
  if(viewsLst.isEmpty()){
    if(!DB.isOpen())
      if(!DB.open()){
        errText=tr("Cannot open db: ")+DB.lastError().text()+tr("\nDB: ")+
            DB.databaseName()+" ["+DB.hostName()+"]";
        emit error(errText);
        return QStringList();
      }
    QSqlQuery qry(DB);
    if(!qry.exec("SELECT viewname,definition FROM pg_views WHERE "
                 "schemaname<>'information_schema' AND "
                 "schemaname<>'pg_catalog'")){
      errText=tr("Cannot retrieve views: "
                 "Error: ")+qry.lastError().text()+tr("\nDB: ")+
              DB.databaseName()+" ["+DB.hostName()+"]"+
              tr("\nQuery: ")+qry.lastQuery();
      emit error(errText);
      return QStringList();
    }
    while(qry.next()){
      viewsLst.insert(qry.record().field("viewname").value().toString(),
                      qry.record().field("definition").value().toString());
    }
  }
  return viewsLst.keys();
}

bool PgDB::refresh(){
  errText.clear();
  QMapIterator< QString,PgTable* > mp(pgTables);
  while(mp.hasNext()){
    mp.next();
    delete mp.value();
  }
  pgTables.clear();
  viewsLst.clear();
  return collect();
}

bool PgDB::collect(){
  bool result=true;
  if(!DB.isOpen())
    if(!(result=DB.open())){
      errText=tr("Cannot open db: ")+DB.lastError().text()+tr("\nDB: ")+
          DB.databaseName()+" ["+DB.hostName()+"]";
      emit error(errText);
      return false;
    }
  QSqlQuery qry(DB);

  if(!qry.exec(STRUCT_QUERY)){
    errText=tr("Cannot retrieve table structure: "
               "Error: ")+qry.lastError().text()+tr("\nDB: ")+
            DB.databaseName()+" ["+DB.hostName()+"]"+
            tr("\nQuery: ")+qry.lastQuery();
    emit error(errText);
    return false;
  }
  QString tblName="";
  PgTable *tbl=0;
  while(qry.next()){
    if(tblName!=qry.record().field("relname").value().toString()){
      tblName=qry.record().field("relname").value().toString();
      tbl=new PgTable(tblName,this);
      tbl->setNamespace(qry.record().field("nspname").value().toString());
      pgTables.insert(tblName,tbl);
    }
    if(tbl==0){
      errText=tr("PgDB: Something wrong O_o - table is null but record here");
      emit error(errText);
      return false;
    }
    QString fldName=qry.record().field("attname").value().toString();
    QString fldType=qry.record().field("typname").value().toString();
    fldType.replace("varchar","text");
    tbl->addField(fldName,fldType,
                  qry.record().field("adsrc").value(),
                  qry.record().field("contype").value().toString().contains("p"),
                  qry.record().field("attnotnull").value().toBool());
    QStringList indexes=qry.record().field("indexnames").value().toString().split(";");
    QStringList indexDefs=qry.record().field("indexdefs").value().toString().split(";");
    for(int idx=0;idx<indexes.count();idx++){
      tbl->addIndex(indexes.at(idx),fldName,indexDefs.value(idx));
    }
  }
  qry.clear();

  if(!qry.exec(CONSTRAINT_QUERY)){
    errText=tr("Cannot retrieve table constraints: "
               "Error: ")+qry.lastError().text()+tr("\nDB: ")+
            DB.databaseName()+" ["+DB.hostName()+"]"+
            tr("\nQuery: ")+qry.lastQuery();
    emit error(errText);
    return false;
  }
  while(qry.next()){
    QString tblName=qry.record().field("relname").value().toString();
    if(pgTables.contains(tblName))
      if(pgTables.value(tblName)->tableNameSpace()==
          qry.record().field("nspname").value().toString()){
        QString tblName_f = qry.record().field( tr( "relname_f" ) ).value().toString();
        QString cName=qry.record().field("conname").value().toString();
        QStringList fields=
            qry.record().field("fields").value().toString().split(";");
        QStringList fields_f =
            qry.record().field( tr( "fields_f" ) ).value().toString().split(";");
        PgConstraint::ConstraintType cType = PgConstraint::UndefinedType;
        if ( qry.record().field( tr( "contype" ) ).value().toString().toLower() == tr( "p" ) )
          cType = PgConstraint::PrimaryKey;
        else if ( qry.record().field( tr( "contype" ) ).value().toString().toLower() == tr( "f" ) )
          cType = PgConstraint::ForeignKey;
        pgTables.value(tblName)->addConstraint(
              cName,fields.value(0),
              qry.record().field("condef").value().toString(),
              cType, tblName_f, fields_f );
        for(int idx=1;idx<fields.count();idx++)
          pgTables.value(tblName)->appendConstraintField(cName,fields.at(idx));
      }
  }
  qry.clear();

  if(!qry.exec(TRIGGER_QUERY)){
    errText=tr("Cannot retrieve table triggers: "
               "Error: ")+qry.lastError().text()+tr("\nDB: ")+
            DB.databaseName()+" ["+DB.hostName()+"]"+
            tr("\nQuery: ")+qry.lastQuery();
    emit error(errText);
    return false;
  }
  while(qry.next()){
    QString tblName=qry.record().field("relname").value().toString();
    if(pgTables.contains(tblName))
      if(pgTables.value(tblName)->tableNameSpace()==
          qry.record().field("nspname").value().toString()){
        pgTables.value(tblName)->addTrigger(
              qry.record().field("tgname").value().toString(),
              qry.record().field("triggerdef").value().toString());
      }
  }
  qry.clear();

  if(!qry.exec(SEQUENCE_QUERY)){
    errText=tr("Cannot retrieve table sequences: "
               "Error: ")+qry.lastError().text()+tr("\nDB: ")+
            DB.databaseName()+" ["+DB.hostName()+"]"+
            tr("\nQuery: ")+qry.lastQuery();
    emit error(errText);
    return false;
  }
  while(qry.next()){
    QString tblName=qry.record().value("refname").toString();
    if(tblName==""){
      foreach(PgTable *tbl,pgTables)
        foreach(QString fld,tbl->fields())
          if(tbl->fieldDefValue(fld).toString().contains(
                qry.record().value("relname").toString()))
            tbl->addSequence(qry.record().value("relname").toString());
    }else if(pgTables.contains(tblName))
      pgTables.value(tblName)->addSequence(
            qry.record().value("relname").toString());
  }

  return result;
}

PgTable::PgTable(const QString tblName,QObject *parent):
  QObject(parent){
  tableName=tblName;
  connect(this,SIGNAL(error(QString)),this,SLOT(errorOccurred(QString)));
}

void PgTable::addField(const QString fldName, const QString fldType,
                       const QVariant defVal, const bool isPrimary,
                       const bool isNotNULL){
  if(!fieldList.contains(fldName)){
    PgField fld;
    fld.defVal=defVal;
    fld.fieldType=fldType;
    fld.isNotNULL=isNotNULL;
    fld.isPrimary=isPrimary;
    m__FieldNames << fldName;
    fieldList.insert(fldName,fld);
  }
}

void PgTable::addIndex(const QString idxName, const QString fldName,
                       const QString idxDef){
  if(!indexList.contains(idxName)){
    PgIndex idx;
    idx.indexDef=idxDef;
    idx.indexFields<<fldName;
    indexList[idxName] = idx;
  }else{
    indexList[idxName].indexDef=idxDef;
    if(!indexList.value(idxName).indexFields.contains(fldName))
      indexList[idxName].indexFields<<fldName;
  }
}

void PgTable::addConstraint(const QString cName, const QString fldName,
                            const QString cDef, PgConstraint::ConstraintType type,
                            QString cTable, QStringList fldNamesF ){
  if(!cList.contains(cName)){
    PgConstraint c;
    c.cType = type;
    c.cDef=cDef;
    c.cFields<<fldName;
    c.cTable = cTable;
    c.cFieldsF = fldNamesF;
    cList[cName] = c;
  }
}

void PgTable::setConstraintDefinition(const QString cName, const QString cDef){
  errText.clear();
  if(cList.count(cName)>0)
    cList[cName].cDef=cDef;
  else
    emit error(tr("setConstraintDefinition: Constraint \"")+cName+
                  "\" not found\n");
}

void PgTable::appendConstraintField(const QString cName, const QString fldName){
  errText.clear();
  if(cList.count(cName)>0){
    if(!cList.value(cName).cFields.contains(fldName))
      cList[cName].cFields.append(fldName);
  }else
    emit error(tr("appendConstraintField: Constraint \"")+cName+
                  "\" not found\n");
}

void PgTable::appendIndexField(const QString idxName, const QString fldName){
  errText.clear();
  if(indexList.count(idxName)>0){
    if(!indexList.value(idxName).indexFields.contains(fldName))
      indexList[idxName].indexFields.append(fldName);
  }else
    emit error(tr("appendIndexField: Index \"")+idxName+"\" not found\n");
}

void PgTable::setIndexDefinition(const QString idxName, const QString idxDef){
  errText.clear();
  if(indexList.count(idxName)>0)
    indexList[idxName].indexDef=idxDef;
  else
    emit error(tr("setIndexDefinition: Index \"")+idxName+"\" not found\n");
}

QStringList PgTable::primaryKeyFields(){
  QStringList lst;
  QMapIterator< QString,PgField > mi(fieldList);
  while(mi.hasNext()){
    mi.next();
    if(mi.value().isPrimary) lst<<mi.key();
  }
  return lst;
}

PgConstraint::ConstraintType PgTable::constraintType( QString cName ) const
{
  if ( !cList.contains( cName ) ) return PgConstraint::UndefinedType;

  return cList[cName].cType;
}

QStringList PgTable::constraintFields( QString cName ) const
{
  if ( !cList.contains( cName ) ) return QStringList();

  return cList[cName].cFields;
}

QString PgTable::constraintTable( QString cName ) const
{
  if ( !cList.contains( cName ) ) return QString();

  return cList[cName].cTable;
}

QStringList PgTable::constraintFieldsF( QString cName ) const
{
  if ( !cList.contains( cName ) ) return QStringList();

  return cList[cName].cFieldsF;
}

QStringList PgTable::fieldConstraints(QString fldName){
  QStringList c=QStringList();
  QMapIterator< QString,PgConstraint > mi(cList);
  while(mi.hasNext()){
    mi.next();
    if(mi.value().cFields.contains(fldName)) c << mi.key();
  }
  return c;
}

QStringList PgTable::constraintDefs(){
  QStringList lst;
  QMapIterator< QString,PgConstraint > mi(cList);
  while(mi.hasNext()){
    mi.next();
    lst<<mi.value().cDef;
  }
  return lst;
}

QString PgTable::constraintByDef(QString cDef){
  QMapIterator< QString,PgConstraint > mi(cList);
  while(mi.hasNext()){
    mi.next();
    if(mi.value().cDef==cDef) return mi.key();
  }
  return "";
}

QStringList PgTable::fieldIndexes(QString fldName){
  QStringList idxs=QStringList();
  QMapIterator< QString,PgIndex > mi(indexList);
  while(mi.hasNext()){
    mi.next();
    if(mi.value().indexFields.contains(fldName)) idxs << mi.key();
  }
  return idxs;
}

QStringList PgTable::fieldIndexDefs(QString fldName){
  QStringList idxs=QStringList();
  QMapIterator< QString,PgIndex > mi(indexList);
  while(mi.hasNext()){
    mi.next();
    if(mi.value().indexFields.contains(fldName)) idxs << mi.value().indexDef;
  }
  return idxs;
}
