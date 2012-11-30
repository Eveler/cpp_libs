#ifndef ABSTRACTSIMPLESTORAGE_H
#define ABSTRACTSIMPLESTORAGE_H

#include "storageitemmodel.h"
#include "abstractsimpleobject.h"

typedef struct
{
  QString Id;
  QString Name;
} StructASSCols;

class AbstractSimpleStorage : public QObject
{
  Q_OBJECT
public:
  explicit AbstractSimpleStorage(QObject *parent = 0);
  ~AbstractSimpleStorage();

  bool setStorage( StorageItemModel *stor, StructASSCols cols );
  StorageItemModel * storage() const;

  virtual const QList<AbstractSimpleObject *> & objects() const = 0;

signals:

public slots:

protected:
  StructASSCols m__Cols;

private:
  StorageItemModel *m__Storage;

  void reset();
  virtual void setObjectData( AbstractSimpleObject *obj, MFCRecord *record ) = 0;

private slots:
  void storageDestroyed();
  virtual void recordAdded( MFCRecord *record, int index ) = 0;
  virtual void recordRemoved( MFCRecord *record, int index ) = 0;
  void disconnectRecord( MFCRecord *record, int );
  void propertyChanged( QString column );
};

#endif // ABSTRACTSIMPLESTORAGE_H
