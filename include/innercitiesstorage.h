#ifndef INNERCITIESSTORAGE_H
#define INNERCITIESSTORAGE_H

#include "storageitemmodel.h"
#include "innercity.h"

typedef struct
{
  QString cId;
  QString cAbbreviation;
  QString cName;
} StructInnerCitieCols;

class InnerCitiesStorage : public QObject
{
    Q_OBJECT
public:
  static InnerCitiesStorage * instance();

  bool setStorage( StorageItemModel *stor, StructInnerCitieCols cols );
  StorageItemModel * storage() const;

  const QList<InnerCity *> & objects() const;

  QList<InnerCity *> findById( QList<InnerCity *> objs, QVariant value ) const;

signals:

public slots:

private:
  static InnerCitiesStorage *m__Instance;

  StorageItemModel *m__Storage;

  StructInnerCitieCols m__Cols;

  QList<InnerCity *> m__InnerCities;

  explicit InnerCitiesStorage(QObject *parent = 0);
  ~InnerCitiesStorage();

  void reset();
  void setObjectData( InnerCity *obj, MFCRecord *record );

private slots:
  void storageDestroyed();
  void recordAdded( MFCRecord *record, int index );
  void recordRemoved( MFCRecord *, int index );
  void disconnectRecord( MFCRecord *record, int );
  void propertyChanged( QString column );
  void changedAbbreviation( Abbreviation *value );
  void changedName( QString value );
};

#endif // INNERCITIESSTORAGE_H
