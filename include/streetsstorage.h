#ifndef STREETSSTORAGE_H
#define STREETSSTORAGE_H

#include "storageitemmodel.h"
#include "street.h"

typedef struct
{
  QString cId;
  QString cAbbreviation;
  QString cName;
} StructStreetCols;

class StreetsStorage : public QObject
{
    Q_OBJECT
public:
  static StreetsStorage * instance();

  bool setStorage( StorageItemModel *stor, StructStreetCols cols );
  StorageItemModel * storage() const;

  const QList<Street *> & objects() const;

  QList<Street *> findById( QList<Street *> objs, QVariant value ) const;

signals:

public slots:

private:
  static StreetsStorage *m__Instance;

  StorageItemModel *m__Storage;

  StructStreetCols m__Cols;

  QList<Street *> m__Streets;

  explicit StreetsStorage(QObject *parent = 0);
  ~StreetsStorage();

  void reset();
  void setObjectData( Street *obj, MFCRecord *record );

private slots:
  void storageDestroyed();
  void recordAdded( MFCRecord *record, int index );
  void recordRemoved( MFCRecord *, int index );
  void disconnectRecord( MFCRecord *record, int );
  void propertyChanged( QString column );
  void changedAbbreviation( Abbreviation *value );
  void changedName( QString value );
};

#endif // STREETSSTORAGE_H
