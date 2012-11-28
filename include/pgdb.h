#ifndef PGDB_H
#define PGDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QMap>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlField>
#include <QStringList>
#include <QDebug>

class PgTable;

class PgDB:public QObject{
  Q_OBJECT
public:
  explicit PgDB(QSqlDatabase db,QObject *parent=0):QObject(parent){
    DB=db;
    connect(this,SIGNAL(error(QString)),this,SLOT(errorOccurred(QString)));
  }
  ~PgDB();
  QString databaseName() {return DB.databaseName();}
  QString hostName() {return DB.hostName();}
  /** Текст ошибки*/
  QString errorText() {return errText;}
  /** Коллекция таблиц базы*/
  QStringList tables();
  /** Экземпляр таблицы @param tblName*/
  PgTable* table(const QString tblName);
  /** Коллекция представлений*/
  QStringList views();
  /** Определение представления @param viewName*/
  QString viewDef(QString viewName) {
    if(viewsLst.isEmpty()) views();
    return viewsLst.value(viewName);
  }
  /** Обновление информации о таблицах с сервера БД*/
  bool refresh();

private:
  QSqlDatabase DB;
  QString errText;
  QMap< QString,PgTable* > pgTables;
  QMap< QString,QString > viewsLst;
  /** Получение информации о таблицах с сервера БД*/
  bool collect();

signals:
  void error(QString);

private slots:
  void errorOccurred(QString err) {errText=err;}
};

/** Структура поля*/
typedef struct{
  QString fieldType;
  QVariant defVal;
  bool isPrimary;
  bool isNotNULL;
} PgField;

/** Структура индекса*/
typedef struct{
  QString indexDef;
  QStringList indexFields;
} PgIndex;

/** Структура ограничения*/
typedef struct{
  enum ConstraintType { UndefinedType = 0, PrimaryKey, ForeignKey};
  ConstraintType cType;
  QString cDef;
  QStringList cFields;
  QString cTable;
  QStringList cFieldsF;
} PgConstraint;

class PgTable : public QObject
{
  Q_OBJECT
public:
  explicit PgTable(const QString tblName,QObject *parent = 0);
  /** Текст ошибки*/
  QString errorText() {return errText;}
  /** Установить имя схемы таблицы*/
  void setNamespace(QString nspName) {nameSpace=nspName;}
  /** Добавить поле*/
  void addField(const QString fldName,const QString fldType,
                const QVariant defVal=QVariant(),const bool isPrimary=false,
                const bool isNotNULL=false);
  /** Добавить ограничение*/
  void addConstraint(const QString cName,const QString fldName,
                     const QString cDef, PgConstraint::ConstraintType type,
                     const QString cTable, const QStringList fldNamesF );
  /** Установить определение ограничения*/
  void setConstraintDefinition(const QString cName,const QString cDef);
  /** Добавить поле, на которое накладывается данное ограничение*/
  void appendConstraintField(const QString cName,const QString fldName);
  /** Добавить индекс*/
  void addIndex(const QString idxName,const QString fldName,
                const QString idxDef="");
  /** Добавить индексируемое поле*/
  void appendIndexField(const QString idxName,const QString fldName);
  /** Установить SQL определение индекса*/
  void setIndexDefinition(const QString idxName,const QString idxDef);
  /** Добавить тригер*/
  void addTrigger(QString tgName,QString tgDef) {
    if(!tgList.contains(tgName)) tgList.insert(tgName,tgDef);
  }
  /** Список полей таблицы*/
  QStringList fields() {return m__FieldNames;}
  /** Список полей в составе первичного ключа*/
  QStringList primaryKeyFields();
  /** Тип поля*/
  QString fieldType(QString fldName){
    return fieldList.value(fldName).fieldType;
  }
  /** Значение поля по умолчанию*/
  QVariant fieldDefValue(QString fldName){
    return fieldList.value(fldName).defVal;
  }
  /** Допускается ли пустое значение*/
  bool fieldIsNotNULL(QString fldName){
    return fieldList.value(fldName).isNotNULL;
  }
  /** Список имён ограничений*/
  QStringList constraints() {return cList.keys();}
  /** Тип ограничения*/
  PgConstraint::ConstraintType constraintType( QString cName ) const;
  /** Список полей ограничения*/
  QStringList constraintFields( QString cName ) const;
  /** Имя таблицы, на которое ссылается ограничение*/
  QString constraintTable( QString cName ) const;
  /** Список полей, на которое ссылается ограничение*/
  QStringList constraintFieldsF( QString cName ) const;
  /** Ограничение, накладываемое на поле*/
  QStringList fieldConstraints(QString fldName);
  /** SQL определение ограничения*/
  QString constraintDef(QString cName) {return cList.value(cName).cDef;}
  /** SQL определения всех ограничений*/
  QStringList constraintDefs();
  /** Ограничение по его определению*/
  QString constraintByDef(QString cDef);
  /** Список имён индексов*/
  QStringList indexes() {return indexList.keys();}
  /** SQL определение индекса*/
  QString indexDef(QString idxName) {return indexList.value(idxName).indexDef;}
  /** Индексы, в состав которых входит поле*/
  QStringList fieldIndexes(QString fldName);
  /** SQL определение индекса в состав которого входит поле*/
  QStringList fieldIndexDefs(QString fldName);
  /** Список таблиц, от которых зависит данная*/
  QStringList dependsOn();
  /** Имя схемы*/
  QString tableNameSpace() {return nameSpace;}
  /** Список тригеров*/
  QStringList triggers() {return tgList.keys();}
  /** Определение тригера*/
  QString triggerDef(QString tgName) { return tgList.value(tgName);}
  /** Список последовательностей*/
  QStringList sequences() {return seqList;}
  /** Добавить последовательность*/
  void addSequence(QString seq) {seqList<<seq;}

private:
  QString tableName;
  QString nameSpace;
  QStringList m__FieldNames;
  QMap< QString,PgField > fieldList;
  QMap< QString,PgIndex > indexList;
  QMap< QString,PgConstraint > cList;
  QMap< QString,QString > tgList;
  QStringList seqList;
  QString errText;

signals:
  void error(QString);

public slots:

private slots:
  void errorOccurred(QString err) {errText=err;}
};

#define STRUCT_QUERY \
  "SELECT n.nspname,"\
  "  c.relname,"\
  "  a.attname,"\
  "  t.typname,"\
  "  a.attnum,"\
  "  a.attnotnull,"\
  "  (SELECT ad.adsrc "\
  "    FROM pg_attrdef ad "\
  "    WHERE ad.adrelid=a.attrelid AND a.attnum=ad.adnum) "\
  "  AS adsrc,"\
  "  array_to_string(array((SELECT pc.contype "\
  "    FROM pg_constraint pc"\
  "    WHERE c.oid = pc.conrelid AND "\
  "      (a.attnum = ANY (pc.conkey)))),';') "\
  "  AS contype, "\
  "  (SELECT pc.relname"\
  "    FROM pg_constraint co, pg_class pc"\
  "    WHERE pc.oid = co.confrelid AND"\
  "      c.oid = co.conrelid AND"\
  "      (a.attnum = ANY (co.conkey))) "\
  "  AS confrelid,"\
  "  array_to_string(array( SELECT"\
  "    array_to_string(co.confkey, ';'::text)"\
  "      AS array_to_string"\
  "    FROM pg_constraint co"\
  "    WHERE c.oid = co.conrelid AND"\
  "      (a.attnum = ANY (co.conkey))),';') "\
  "  AS confkey,"\
  "  (SELECT n.nspname"\
  "    FROM pg_constraint co, pg_class pc, pg_namespace n"\
  "    WHERE pc.oid = co.confrelid AND"\
  "      pc.relnamespace=n.oid AND"\
  "      c.oid = co.conrelid AND"\
  "      (a.attnum = ANY (co.conkey))) "\
  "  AS nspfname,"\
  "  array_to_string(array( (SELECT i.relname"\
  "    FROM pg_index x"\
  "    JOIN pg_class i ON i.oid = x.indexrelid"\
  "    WHERE c.oid = x.indrelid AND"\
  "      i.relkind = 'i'::\"char\" AND"\
  "      a.attnum=ANY(x.indkey))),';') "\
  "  AS indexnames,"\
  "  array_to_string(array(SELECT pg_get_indexdef(i.oid)"\
  "    FROM pg_index x"\
  "    JOIN pg_class i ON i.oid = x.indexrelid"\
  "    WHERE c.oid = x.indrelid AND"\
  "      i.relkind = 'i'::\"char\" AND"\
  "      a.attnum=ANY(x.indkey)),';')"\
  "  AS indexdefs "\
  "FROM pg_class c, pg_namespace n, pg_attribute a, pg_type t "\
  "WHERE"\
  "  c.relnamespace = n.oid AND"\
  "  c.oid = a.attrelid AND"\
  "  t.oid = a.atttypid AND"\
  "  a.attnum > 0 AND a.attisdropped = false AND"\
  "  c.relkind = 'r'::\"char\" AND"\
  "  n.nspname<>'pg_catalog' AND"\
  "  n.nspname<>'information_schema'"\
  "ORDER BY n.nspname,c.relname,a.attnum"

#define CONSTRAINT_QUERY \
  "SELECT n.nspname,"\
  "  c.relname,"\
  "  (SELECT c2.relname FROM pg_class c2 WHERE co.confrelid=c2.oid) AS relname_f,"\
  "  co.conname,"\
  "  co.contype,"\
  "  array_to_string(array(SELECT a.attname"\
  "    FROM pg_attribute a"\
  "    WHERE c.oid = a.attrelid AND a.attnum=ANY(co.conkey)),';')"\
  "  AS fields,"\
  "  array_to_string(array(SELECT a.attname"\
  "    FROM pg_attribute a"\
  "    WHERE c.oid = a.attrelid AND a.attnum=ANY(co.confkey)),';')"\
  "  AS fields_f,"\
  "  pg_get_constraintdef(co.oid) AS condef "\
  "FROM pg_constraint co "\
  "JOIN pg_class c ON co.conrelid=c.oid "\
  "JOIN pg_namespace n ON c.relnamespace = n.oid "\
  "ORDER BY c.relname"

#define TRIGGER_QUERY \
  "SELECT n.nspname,c.relname,t.tgname,pg_get_triggerdef(t.oid) as triggerdef "\
  "FROM pg_class c,pg_trigger t,pg_namespace n "\
  "WHERE t.tgrelid=c.oid AND c.relnamespace=n.oid "\
  "ORDER BY relname"

#define SEQUENCE_QUERY \
  "SELECT c.relname,"\
  "  array_to_string(array(SELECT pc.relname"\
  "    FROM pg_class pc, pg_depend d"\
  "    WHERE c.oid=d.objid and pc.oid=d.refobjid),';')"\
  "  AS refname "\
  "FROM pg_class c "\
  "WHERE c.relkind='S' "\
  "ORDER BY c.relname"

#endif // PGDB_H
