#ifndef ABSTRACTSIMPLESTORAGE_H
#define ABSTRACTSIMPLESTORAGE_H

#include "storageitemmodel.h"
#include "abstractsimpleobject.h"

typedef struct
{
  QString cId;
  QString cName;
} StructASSCols;

class AbstractSimpleStorage : public QObject
{
  Q_OBJECT
public:
  explicit AbstractSimpleStorage(QObject *parent = 0);
  ~AbstractSimpleStorage();

  bool setStorage( StorageItemModel *stor, StructASSCols cols );
  StorageItemModel * storage() const;

  const QList<AbstractSimpleObject *> & objects() const;

  QList<AbstractSimpleObject *> find(
      QList<AbstractSimpleObject *> objs, QVariant id ) const;
  QList<AbstractSimpleObject *> find(
      QList<AbstractSimpleObject *> objs, QString name,
      Qt::MatchFlag flag = Qt::MatchFixedString,
      Qt::CaseSensitivity cs = Qt::CaseSensitive ) const;

signals:

public slots:

protected:
  StructASSCols m__Cols;

private:
  StorageItemModel *m__Storage;

  QList<AbstractSimpleObject *> m__Objects;

  void reset();
  void setObjectData( AbstractSimpleObject *obj, MFCRecord *record );

private slots:
  void storageDestroyed();
  void recordAdded( MFCRecord *record, int index );
  void recordRemoved( MFCRecord *record, int index );
  void disconnectRecord( MFCRecord *record, int );
  void propertyChanged( QString column );
  void changedName( QString value );
};

#endif // ABSTRACTSIMPLESTORAGE_H
