#ifndef SubaddressESSTORAGE_H
#define SubaddressESSTORAGE_H

#include "storageitemmodel.h"
#include "subaddress.h"

typedef struct
{
  QString cId;
  QString cPostcode;
  QString cHouseNumber;
  QString cBuildNumber;
  QString cStructNumber;
  QString cStructureStatus;
} StructSubaddressCols;

class SubaddressesStorage : public QObject
{
    Q_OBJECT
public:
  static SubaddressesStorage * instance();

  bool setStorage(StorageItemModel *stor, StructSubaddressCols cols );
  StorageItemModel * storage() const;

  const QList<Subaddress *> & objects() const;

  QList<Subaddress *> findById( QList<Subaddress *> objs, QVariant value ) const;

signals:

public slots:

private:
  static SubaddressesStorage *m__Instance;

  StorageItemModel *m__Storage;

  StructSubaddressCols m__Cols;

  QList<Subaddress *> m__Subaddresses;

  explicit SubaddressesStorage(QObject *parent = 0);
  ~SubaddressesStorage();

  void reset();
  void setObjectData( Subaddress *obj, MFCRecord *record );

private slots:
  void storageDestroyed();
  void recordAdded( MFCRecord *record, int index );
  void recordRemoved( MFCRecord *, int index );
  void disconnectRecord( MFCRecord *record, int );
  void propertyChanged( QString column );
};

#endif // SubaddressESSTORAGE_H
