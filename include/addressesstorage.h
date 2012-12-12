#ifndef SERVICESSTORAGE_H
#define SERVICESSTORAGE_H

#include "storageitemmodel.h"
#include "service.h"

typedef struct
{
  QString Id;
  QString Name;
  QString Deadline;
  QString Active;
} StructServiceCols;

class ServicesStorage : public QObject
{
    Q_OBJECT
public:
  static ServicesStorage * instance();

  bool setStorage( StorageItemModel *stor, StructServiceCols cols );
  StorageItemModel * storage() const;

  const QList<Service *> & objects() const;

signals:

public slots:

private:
  static ServicesStorage *m__Instance;

  StorageItemModel *m__Storage;

  StructServiceCols m__Cols;

  QList<Service *> m__Services;

  explicit ServicesStorage(QObject *parent = 0);
  ~ServicesStorage();

  void reset();
  void setObjectData( Service *obj, MFCRecord *record );

private slots:
  void storageDestroyed();
  void recordAdded( MFCRecord *record, int index );
  void recordRemoved( MFCRecord *, int index );
  void disconnectRecord( MFCRecord *record, int );
  void propertyChanged( QString column );
};

#endif // SERVICESSTORAGE_H
