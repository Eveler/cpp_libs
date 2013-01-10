#ifndef TOWNSHIPSSTORAGE_H
#define TOWNSHIPSSTORAGE_H

#include "storageitemmodel.h"
#include "township.h"

typedef struct
{
  QString cId;
  QString cAbbreviation;
  QString cName;
} StructTownshipCols;

class TownshipsStorage : public QObject
{
    Q_OBJECT
public:
  static TownshipsStorage * instance();

  bool setStorage( StorageItemModel *stor, StructTownshipCols cols );
  StorageItemModel * storage() const;

  const QList<Township *> & objects() const;

  QList<Township *> findById( QList<Township *> objs, QVariant value ) const;

signals:

public slots:

private:
  static TownshipsStorage *m__Instance;

  StorageItemModel *m__Storage;

  StructTownshipCols m__Cols;

  QList<Township *> m__Townships;

  explicit TownshipsStorage(QObject *parent = 0);
  ~TownshipsStorage();

  void reset();
  void setObjectData( Township *obj, MFCRecord *record );

private slots:
  void storageDestroyed();
  void recordAdded( MFCRecord *record, int index );
  void recordRemoved( MFCRecord *, int index );
  void disconnectRecord( MFCRecord *record, int );
  void propertyChanged( QString column );
  void changedAbbreviation( Abbreviation *value );
  void changedName( QString value );
};

#endif // TOWNSHIPSSTORAGE_H
