#ifndef ADDRESESSTORAGE_H
#define ADDRESESSTORAGE_H

#include "storageitemmodel.h"
#include "address.h"

typedef struct
{
  QString cId;
  QString cCountry;
  QString cSubject;
  QString cRegion;
  QString cArea;
  QString cCity;
  QString cInnerCity;
  QString cTownship;
  QString cStreet;
  QString cSubaddress;
  QString cSlaveAddress;
  QString cPostcode;
} StructAddressCols;

class AddressesStorage : public QObject
{
    Q_OBJECT
public:
  static AddressesStorage * instance();

  bool setStorage( StorageItemModel *stor, StructAddressCols cols );
  StorageItemModel * storage() const;

  const QList<Address *> & objects() const;

signals:

public slots:

private:
  static AddressesStorage *m__Instance;

  StorageItemModel *m__Storage;

  StructAddressCols m__Cols;

  QList<Address *> m__Addresses;

  explicit AddressesStorage(QObject *parent = 0);
  ~AddressesStorage();

  void reset();
  void setObjectData( Address *obj, MFCRecord *record );

private slots:
  void storageDestroyed();
  void recordAdded( MFCRecord *record, int index );
  void recordRemoved( MFCRecord *, int index );
  void disconnectRecord( MFCRecord *record, int );
  void propertyChanged( QString column );
};

#endif // ADDRESESSTORAGE_H
