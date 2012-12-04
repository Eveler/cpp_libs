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

  const QList<AbstractSimpleObject *> & objects() const;

  QList<AbstractSimpleObject *> find( QVariant id ) const;
  QList<AbstractSimpleObject *> find(
      QString name, Qt::MatchFlag flag = Qt::MatchFixedString,
      Qt::CaseSensitivity cs = Qt::CaseSensitive ) const;
  QList<AbstractSimpleObject *> find(
      QVariant id, QString name, Qt::MatchFlag flag = Qt::MatchFixedString,
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

  QList<AbstractSimpleObject *> pFind(
      QVariant id, QList<AbstractSimpleObject *> objs ) const;
  QList<AbstractSimpleObject *> pFind(
      QString name, Qt::MatchFlag flag, Qt::CaseSensitivity cs, QList<AbstractSimpleObject *> objs ) const;

private slots:
  void storageDestroyed();
  void recordAdded( MFCRecord *record, int index );
  void recordRemoved( MFCRecord *record, int index );
  void disconnectRecord( MFCRecord *record, int );
  void propertyChanged( QString column );
};

#endif // ABSTRACTSIMPLESTORAGE_H
