#ifndef ABSTRACTSIMPLESTORAGE_H
#define ABSTRACTSIMPLESTORAGE_H

#include "storageitemmodel.h"
#include "abstractsimpleobject.h"

class AbstractSimpleStorage : public QObject
{
  Q_OBJECT
public:
  explicit AbstractSimpleStorage(QObject *parent = 0);
  ~AbstractSimpleStorage();

  bool setStorage( StorageItemModel *stor = NULL,
                   QString colName_Id = QString(),
                   QString colName_Name = QString() );
  StorageItemModel * storage();

  virtual const QList<AbstractSimpleObject *> & objects() const = 0;

signals:

public slots:

protected:
  QString m__ColName_Id;
  QString m__ColName_Name;

private:
  StorageItemModel *m__Storage;

  virtual void setObjectData( AbstractSimpleObject *obj, MFCRecord *record ) = 0;

private slots:
  void storageDestroyed();
  virtual void recordAdded( MFCRecord *record, int index ) = 0;
  virtual void recordRemoved( MFCRecord *record, int index ) = 0;
  void disconnectRecord( MFCRecord *record, int );
  void propertyChanged( QString column );
};

#endif // ABSTRACTSIMPLESTORAGE_H
