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
  QString cSlaveaddress;
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
  void changedCountry( AbstractSimpleObject *value );
  void changedSubject( Subject *value );
  void changedRegion( Region *value );
  void changedArea( Area *value );
  void changedCity( City *value );
  void changedInnerCity( InnerCity *value );
  void changedTownship( Township *value );
  void changedStreet( Street *value );
  void changedSubaddress( Subaddress *value );
  void changedSlaveaddress( AbstractSimpleObject *value );
  void changedPostcode( AbstractSimpleObject *value );
};

#endif // ADDRESESSTORAGE_H
