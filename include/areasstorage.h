#ifndef AREASSTORAGE_H
#define AREASSTORAGE_H

#include "storageitemmodel.h"
#include "area.h"

typedef struct
{
  QString cId;
  QString cAbbreviation;
  QString cName;
} StructAreaCols;

class AreasStorage : public QObject
{
    Q_OBJECT
public:
  static AreasStorage * instance();

  bool setStorage( StorageItemModel *stor, StructAreaCols cols );
  StorageItemModel * storage() const;

  const QList<Area *> & objects() const;

  QList<Area *> findById( QList<Area *> objs, QVariant value ) const;

signals:

public slots:

private:
  static AreasStorage *m__Instance;

  StorageItemModel *m__Storage;

  StructAreaCols m__Cols;

  QList<Area *> m__Areas;

  explicit AreasStorage(QObject *parent = 0);
  ~AreasStorage();

  void reset();
  void setObjectData( Area *obj, MFCRecord *record );

private slots:
  void storageDestroyed();
  void recordAdded( MFCRecord *record, int index );
  void recordRemoved( MFCRecord *, int index );
  void disconnectRecord( MFCRecord *record, int );
  void propertyChanged( QString column );
  void changedAbbreviation( Abbreviation *value );
  void changedName( QString value );
};

#endif // AREASSTORAGE_H
