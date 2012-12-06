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
  /** ����� ������*/
  QString errorText() {return errText;}
  /** ��������� ������ ����*/
  QStringList tables();
  /** ��������� ������� @param tblName*/
  PgTable* table(const QString tblName);
  /** ��������� �������������*/
  QStringList views();
  /** ����������� ������������� @param viewName*/
  QString viewDef(QString viewName) {
    if(viewsLst.isEmpty()) views();
    return viewsLst.value(viewName);
  }
  /** ���������� ���������� � �������� � ������� ��*/
  bool refresh();

private:
  QSqlDatabase DB;
  QString errText;
  QMap< QString,PgTable* > pgTables;
  QMap< QString,QString > viewsLst;
  /** ��������� ���������� � �������� � ������� ��*/
  bool collect();

signals:
  void error(QString);

private slots:
  void errorOccurred(QString err) {errText=err;}
};

/** ��������� ����*/
typedef struct{
  QString fieldType;
  QVariant defVal;
  bool isPrimary;
  bool isNotNULL;
} PgField;

/** ��������� �������*/
typedef struct{
  QString indexDef;
  QStringList indexFields;
} PgIndex;

/** ��������� �����������*/
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
  /** ����� ������*/
  QString errorText() {return errText;}
  /** ���������� ��� ����� �������*/
  void setNamespace(QString nspName) {nameSpace=nspName;}
  /** �������� ����*/
  void addField(const QString fldName,const QString fldType,
                const QVariant defVal=QVariant(),const bool isPrimary=false,
                const bool isNotNULL=false);
  /** �������� �����������*/
  void addConstraint(const QString cName,const QString fldName,
                     const QString cDef, PgConstraint::ConstraintType type,
                     const QString cTable, const QStringList fldNamesF );
  /** ���������� ����������� �����������*/
  void setConstraintDefinition(const QString cName,const QString cDef);
  /** �������� ����, �� ������� ������������� ������ �����������*/
  void appendConstraintField(const QString cName,const QString fldName);
  /** �������� ������*/
  void addIndex(const QString idxName,const QString fldName,
                const QString idxDef="");
  /** �������� ������������� ����*/
  void appendIndexField(const QString idxName,const QString fldName);
  /** ���������� SQL ����������� �������*/
  void setIndexDefinition(const QString idxName,const QString idxDef);
  /** �������� ������*/
  void addTrigger(QString tgName,QString tgDef) {
    if(!tgList.contains(tgName)) tgList.insert(tgName,tgDef);
  }
  /** ������ ����� �������*/
  QStringList fields() {return m__FieldNames;}
  /** ������ ����� � ������� ���������� �����*/
  QStringList primaryKeyFields();
  /** ��� ����*/
  QString fieldType(QString fldName){
    return fieldList.value(fldName).fieldType;
  }
  /** �������� ���� �� ���������*/
  QVariant fieldDefValue(QString fldName){
    return fieldList.value(fldName).defVal;
  }
  /** ����������� �� ������ ��������*/
  bool fieldIsNotNULL(QString fldName){
    return fieldList.value(fldName).isNotNULL;
  }
  /** ������ ��� �����������*/
  QStringList constraints() {return cList.keys();}
  /** ��� �����������*/
  PgConstraint::ConstraintType constraintType( QString cName ) const;
  /** ������ ����� �����������*/
  QStringList constraintFields( QString cName ) const;
  /** ��� �������, �� ������� ��������� �����������*/
  QString constraintTable( QString cName ) const;
  /** ������ �����, �� ������� ��������� �����������*/
  QStringList constraintFieldsF( QString cName ) const;
  /** �����������, ������������� �� ����*/
  QStringList fieldConstraints(QString fldName);
  /** SQL ����������� �����������*/
  QString constraintDef(QString cName) {return cList.value(cName).cDef;}
  /** SQL ����������� ���� �����������*/
  QStringList constraintDefs();
  /** ����������� �� ��� �����������*/
  QString constraintByDef(QString cDef);
  /** ������ ��� ��������*/
  QStringList indexes() {return indexList.keys();}
  /** SQL ����������� �������*/
  QString indexDef(QString idxName) {return indexList.value(idxName).indexDef;}
  /** �������, � ������ ������� ������ ����*/
  QStringList fieldIndexes(QString fldName);
  /** SQL ����������� ������� � ������ �������� ������ ����*/
  QStringList fieldIndexDefs(QString fldName);
  /** ������ ������, �� ������� ������� ������*/
  QStringList dependsOn();
  /** ��� �����*/
  QString tableNameSpace() {return nameSpace;}
  /** ������ ��������*/
  QStringList triggers() {return tgList.keys();}
  /** ����������� �������*/
  QString triggerDef(QString tgName) { return tgList.value(tgName);}
  /** ������ �������������������*/
  QStringList sequences() {return seqList;}
  /** �������� ������������������*/
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
