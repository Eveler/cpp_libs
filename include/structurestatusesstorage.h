#ifndef STRUCTURESTATUSESSTORAGE_H
#define STRUCTURESTATUSESSTORAGE_H

#include "storageitemmodel.h"
#include "structurestatus.h"

typedef struct
{
  QString cId;
  QString cShortName;
  QString cFullName;
} StructStructureStatusCols;

class StructureStatusesStorage : public QObject
{
    Q_OBJECT
public:
  static StructureStatusesStorage * instance();

  bool setStorage( StorageItemModel *stor, StructStructureStatusCols cols );
  StorageItemModel * storage() const;

  const QList<StructureStatus *> & objects() const;

  QList<StructureStatus *> findById( QList<StructureStatus *> objs, QVariant value ) const;

signals:

public slots:

private:
  static StructureStatusesStorage *m__Instance;

  StorageItemModel *m__Storage;

  StructStructureStatusCols m__Cols;

  QList<StructureStatus *> m__StructureStatuses;

  explicit StructureStatusesStorage(QObject *parent = 0);
  ~StructureStatusesStorage();

  void reset();
  void setObjectData( StructureStatus *obj, MFCRecord *record );

private slots:
  void storageDestroyed();
  void recordAdded( MFCRecord *record, int index );
  void recordRemoved( MFCRecord *, int index );
  void disconnectRecord( MFCRecord *record, int );
  void propertyChanged( QString column );
  void changedShortName( QString value );
  void changedFullName( QString value );
};

#endif // STRUCTURESTATUSESSTORAGE_H
