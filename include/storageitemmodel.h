#ifndef STORAGEITEMMODEL_H
#define STORAGEITEMMODEL_H

#include <QStandardItemModel>
#include "mfcrecord.h"
#include <QThread>

//using namespace MFCPropertiesView;
//namespace MFCPropertiesView
//{
//  class StorageItemModel;
//}

class ParamFilters: public QObject
{
public:
  ParamFilters();
  ~ParamFilters();

  void clear();

  bool setParam( PropertiesView *pv, const QString &p_Name, QVariant p_Value,
                 Qt::MatchFlag p_Flag = Qt::MatchExactly );
  bool removeParam( PropertiesView *pv );
  bool removeParam( PropertiesView *pv, const QString &p_Name );

  const QList<PropertiesView *> & propertiesViews() const;
  const QStringList & paramNames( PropertiesView *pv ) const;
  QVariant paramValue( PropertiesView *pv, const QString &p_Name ) const;
  Qt::MatchFlag paramFlag( PropertiesView *pv, const QString &p_Name ) const;

private:
  QList<PropertiesView *> m_PropertiesViews;
  QList<QPair<PropertiesView *, QStringList> > m_ParamNames;
  QHash<PropertiesView *, QHash<QString, QVariant> > m_ParamValues;
  QHash<PropertiesView *, QHash<QString, Qt::MatchFlag> > m_ParamFlags;

  QStringList m_PNsNull;

  QStringList & paramNamesStorage( PropertiesView *pv );
};

class SortParams: public QObject
{
  Q_OBJECT
public:
  explicit SortParams();
  ~SortParams();

  bool setPropertiesView( const QString &alias );

  bool isNull() const;
  bool isValid() const;

  bool setSort( PropertiesView *pv, const QString &p_Name, Qt::SortOrder sort_Flag = Qt::AscendingOrder );
  bool removeSort( PropertiesView *pv );
  bool removeSort( PropertiesView *pv, const QString &p_Name );
  void clear();

  PropertiesView * propertiesView() const;
  const QList<PropertiesView *> & propertiesViews() const;
  const QStringList & paramNames( PropertiesView *pv ) const;
  Qt::SortOrder sortFlag( PropertiesView *pv, const QString &p_Name ) const;

  bool comparison( MFCRecord *record_1, MFCRecord *record_2 ) const;

signals:
  void changed();

private:
  PropertiesView *m_PV;
  QList<PropertiesView *> m_PropertiesViews;
  QList<QPair<PropertiesView *, QStringList> > m_ParamNames;
  QHash<PropertiesView *, QHash<QString, Qt::SortOrder> > m_SortFlags;

  QStringList m_PNsNull;

  QStringList & paramNamesStorage( PropertiesView *pv );
};

class StorageItemModel : public QStandardItemModel
{
  Q_OBJECT
public:
  StorageItemModel( PropertiesView *propertiesView, QObject *parent = 0 );
  ~StorageItemModel();

  bool isNull() const;

  StorageItemModel * externalStorage_Recursively( PropertiesView *pv );
  bool addExternalStorage( StorageItemModel *storage, bool autoDelete = false );
  StorageItemModel * externalStorage( PropertiesView *pv ) const;
  StorageItemModel * externalStorage( const QString &pv_alias ) const;
  QList<StorageItemModel *> externalStorages() const;

  bool appendRecord( MFCRecord *rootRecord, bool markAsNew );
  void reindexRecord( int row );
  bool setRecordVisible( MFCRecord *rootRecord, bool visible = true );
  bool removeRecord( MFCRecord *rootRecord );
  bool removeVisibleRecord( MFCRecord *rootRecord );
  bool removeVisibleRecord( int row );
  void clear();

  const QList<MFCRecord *> & availableRecords() const;
  const QList<MFCRecord *> & visibleRecords() const;

  bool changeRecordMark( MFCRecord *rootRecord, bool isNew );
  const QList<MFCRecord *> & newRecords() const;
  QList<MFCRecord *> oldRecords() const;

  bool renameColumn( PropertiesView *childPV, QString childPName, QString newName,
                     PropertiesView *parentPV = 0, QString parentPName = QString() );

  PropertiesView * getPropertiesView() const;

  int findColumnByRealName( PropertiesView *childPV, QString childPName,
                            PropertiesView *parentPV = 0, QString parentPName = QString() ) const;
  PropertiesView * columnPropertiesView( int col ) const;
  QString realHeaderName( int col ) const;
  QList<int> linkedColumns( int col ) const;

  QList<MFCRecord *> findRecords( const ParamFilters &filter);
  QList<MFCRecord *> rootRecordFor( MFCRecord *record );
  bool setFilter(ParamFilters *filter );
  const ParamFilters *filter() const;
  void clearFilter();

  bool setSort( SortParams *sort );
  SortParams * sort() const;

  bool setChild( MFCRecord *rootRecord, QString p_Name, MFCRecord *child );

  MFCRecord * findByIndex( const QString &p_Name, QVariant val );
  void deleteContent();

signals:
  void searchStarted();
  void searchFinished();

  void availableRecords_Changed();
  void visibleRecords_Changed();
  void newRecords_Changed();
  void recordAdded( MFCRecord *rootRecord );
  void recordDisplayChanged( MFCRecord *rootRecord, int index );
  void visibleRecordRemoved( int index );
  void recordMoved( MFCRecord *rootRecord, int oldIndex );

public slots:
  bool resort();
  bool resortAll();

private:
  static const QList<QVariant::Type> indexedTypes;

  PropertiesView *m_PropertiesView;
  QString m_PropertiesViewAlias;

  QList<StorageItemModel *> m__ExternalStorages;
  QHash<PropertiesView *, StorageItemModel *> m__ExtStgs_PV;
  QHash<QString, StorageItemModel *> m__ExtStgs_Alias;
  QList<StorageItemModel *> m__DeletableStorages;

  QHash<QString, QHash<QString, MFCRecord *> > m_IndexedRecords;

  bool m_CanStartSearch;

  QList<MFCRecord *> m_AvailableRecords;
  QList<QUuid> m_RecordsUuid;
  QList<MFCRecord *> m_VisibleRecords;
  QList<MFCRecord *> m_NewRecords;

  QList<QPair<PropertiesView *, QString> > links;
  QHash<QPair<int, PropertiesView *>, QList<int> > properties_columns_1;
  QHash<QPair<PropertiesView*, QString>, QList<int> > properties_columns_2;
  QMap<int, QList<int> > linked_columns;
//  QHash<int, PropertiesView *> col_pv;
//  QHash<int, QString> col_name;

  QHash<QPair<QPair<int, PropertiesView *>, QString>,
        QPair<QPair<int, PropertiesView *>, QString> > renamedColumns;

  bool blockEdit;

  ParamFilters *m_Filter;
  SortParams *m_Sort;

  QList<MFCRecord *> m_NotSorted;

  void insertRowU( int row );
  void insertColumnU( int row );

  bool removeRowU( int row );
  bool removeRowsU( int row, int count );
  bool removeColumnU( int row );
  bool removeColumnsU( int column, int count );

  void appendRow( const QList<QStandardItem *> &items );
  void appendColumn( const QList<QStandardItem *> &items );

  void insertRow( int row, const QModelIndex &parent = QModelIndex() );
  bool insertRows( int row, int count, const QModelIndex &parent = QModelIndex() );
  void insertColumn( int column, const QModelIndex &parent = QModelIndex() );
  bool insertColumns( int column, int count, const QModelIndex &parent = QModelIndex() );

  bool removeRow( int row, const QModelIndex &parent = QModelIndex() );
  bool removeRows( int row, int count, const QModelIndex &parent = QModelIndex() );
  bool removeColumn( int column, const QModelIndex &parent = QModelIndex() );
  bool removeColumns( int column, int count, const QModelIndex &parent = QModelIndex() );

  bool setHeaderData( const int section, const Qt::Orientation orientation,
                      const QVariant &value, const int role = Qt::DisplayRole );
  bool setData( const QModelIndex &index, const QVariant &value, const int role = Qt::DisplayRole );
  bool setItemData( const QModelIndex &index, const QMap<int, QVariant> &roles );
  void setItem( int row, int column, QStandardItem *item );
  void setItemPrototype( const QStandardItem *item );

  void drawColumns();
  void drawRecord( int row, MFCRecord *parent, MFCRecord *record );
  QString getVisibleData( int row, QList<int> columns );

  void createConnect( MFCRecord *rootRecord );
  void removeConnect( MFCRecord *rootRecord );
  void removeIndex( MFCRecord *rootRecord );

  void quicksort(int l, int r);
  void smallsort();

private slots:
  void propertiesModified();
  void valueChanged( QString p_Name, QVariant old_Value, QVariant new_Value );
  void dataReversed();
  void recordDestroyed( QUuid uuid );
  void connectSingleRecord( MFCRecord *record );
  void disconnectSingleRecord( MFCRecord *record );
  void childReplaced( MFCRecord *old_record, MFCRecord *new_record );
  void filterDestroyed();
  void sortDestroyed();
  void externalStorageDestroyed( QObject *obj );
};

#endif // STORAGEITEMMODEL_H
