#ifndef CITIESSTORAGE_H
#define CITIESSTORAGE_H

#include "storageitemmodel.h"
#include "city.h"

typedef struct
{
  QString cId;
  QString cAbbreviation;
  QString cName;
} StructCityCols;

class CitiesStorage : public QObject
{
    Q_OBJECT
public:
  static CitiesStorage * instance();

  bool setStorage( StorageItemModel *stor, StructCityCols cols );
  StorageItemModel * storage() const;

  const QList<City *> & objects() const;

  QList<City *> findById( QList<City *> objs, QVariant value ) const;

signals:

public slots:

private:
  static CitiesStorage *m__Instance;

  StorageItemModel *m__Storage;

  StructCityCols m__Cols;

  QList<City *> m__Citie;

  explicit CitiesStorage(QObject *parent = 0);
  ~CitiesStorage();

  void reset();
  void setObjectData( City *obj, MFCRecord *record );

private slots:
  void storageDestroyed();
  void recordAdded( MFCRecord *record, int index );
  void recordRemoved( MFCRecord *, int index );
  void disconnectRecord( MFCRecord *record, int );
  void propertyChanged( QString column );
  void changedAbbreviation( Abbreviation *value );
  void changedName( QString value );
};

#endif // CITIESSTORAGE_H
