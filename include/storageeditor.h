#ifndef STORAGEEDITOR_H
#define STORAGEEDITOR_H

#include <QObject>
#include <QSqlDatabase>
#include "storageitemmodel.h"
#include "propertiessqlworker.h"

class StorageEditor : public QObject
{
  Q_OBJECT
public:
  static StorageEditor * instance(
      const QString &alias, const QString &connectionName,
      const QString &propertiesView, QString filter = QString(), SortParams *sort = 0 );
  static StorageEditor * getStorage( const QString &alias );
  static bool releaseAll();
  static bool release( StorageEditor *editor );
  static QStringList notAvailableStorages( QStringList aliases );

  bool isNull() const;

  const QString & alias() const;

  StorageItemModel * storage() const;

  void showLoadLog( bool show );

  void setSqlFilter( QString text );

  void load();

  bool setUnique( QStringList p_Names );

  void beginChanges();
  QList<MFCRecord *> changedRecords();
  QList<MFCRecord *> endChanges();

  void setAutosaveOnAdd( bool enable );
  bool addRecord( MFCRecord *rootRecord );
  bool addRecord( MFCRecord *rootRecord, PropertiesSqlWorker *psw, bool autoSave = true );

  bool setKeyField( QString keyField );

  bool save();
  bool save( PropertiesSqlWorker *sqlWorker );

signals:
  void destroyed( QString alias );
  void address( QString text );
  void progress( int value );

public slots:

private:
  static StorageEditor *nullEditor;
  static QHash<QString, StorageEditor *> m_Editors;

  QString *m_Alias;
  QSqlDatabase m_DB;
  PropertiesSqlWorker *m_PSW;
  StorageItemModel *m_Storage;

  QString m_Filter;

  bool checkChanges;
  QList<MFCRecord *> m_ChangedRecords;
  QHash<MFCRecord *, QStringList> m_ChangedProperies;
  QHash<QPair<MFCRecord *, QString>, QPair<QVariant, QVariant> > m_ChangedValues;
  MFCRecord *revert;

  bool m_Autosave;

  QString error;

  QStringList m_Address;

//  QHash<Properties *, QList<MFCRecord *> > m_Records;
  QHash<PropertiesView *, QList<MFCRecord *> > m_Records;
  QStringList m_UniqueProperties;

  bool m_ShowLoadLog;

  QString m_KeyField;

  explicit StorageEditor();
  explicit StorageEditor( const QString &alias, QSqlDatabase &db,
                          PropertiesView *propertiesView, QString filter, SortParams *sort );
  ~StorageEditor();

  QString releaseError();
//  bool loadRecords( Properties *ps, QString filter );
//  bool loadRecords( PropertiesView *pv, QString filter );
  bool unloadRecords( QStringList &recordKeys, const QString &keyField );
  bool updateRecords( const QString &filter, const QString &keyField );
  bool loadRecords( StorageItemModel *currentStorage, QString filter );
  bool nextVal( MFCRecord *rootRecord, PropertiesSqlWorker *psw );

private slots:
  void storageDestroyed();
  void recordAdded( MFCRecord *rootRecord );
  void propertyChanged( QString p_Name, QVariant oldValue, QVariant newValue );
};


#endif // STORAGEEDITOR_H
