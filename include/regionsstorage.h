#ifndef REGIONSSTORAGE_H
#define REGIONSSTORAGE_H

#include "storageitemmodel.h"
#include "Region.h"

typedef struct
{
  QString cId;
  QString cAbbreviation;
  QString cName;
} StructRegionCols;

class RegionsStorage : public QObject
{
    Q_OBJECT
public:
  static RegionsStorage * instance();

  bool setStorage( StorageItemModel *stor, StructRegionCols cols );
  StorageItemModel * storage() const;

  const QList<Region *> & objects() const;

  QList<Region *> findById( QList<Region *> objs, QVariant value ) const;

signals:

public slots:

private:
  static RegionsStorage *m__Instance;

  StorageItemModel *m__Storage;

  StructRegionCols m__Cols;

  QList<Region *> m__Regions;

  explicit RegionsStorage(QObject *parent = 0);
  ~RegionsStorage();

  void reset();
  void setObjectData( Region *obj, MFCRecord *record );

private slots:
  void storageDestroyed();
  void recordAdded( MFCRecord *record, int index );
  void recordRemoved( MFCRecord *, int index );
  void disconnectRecord( MFCRecord *record, int );
  void propertyChanged( QString column );
  void changedAbbreviation( Abbreviation *value );
  void changedName( QString value );
};

#endif // REGIONSSTORAGE_H
