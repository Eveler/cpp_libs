#ifndef ABBREVIATIONSSTORAGE_H
#define ABBREVIATIONSSTORAGE_H

#include "storageitemmodel.h"
#include "abbreviation.h"

typedef struct
{
  QString Id;
  QString cShortName;
  QString cFullName;
} StructAbbreviationCols;

class AbbreviationsStorage : public QObject
{
    Q_OBJECT
public:
  static AbbreviationsStorage * instance();

  bool setStorage( StorageItemModel *stor, StructAbbreviationCols cols );
  StorageItemModel * storage() const;

  const QList<Abbreviation *> & objects() const;

  QList<Abbreviation *> findById( QList<Abbreviation *> objs, QVariant value ) const;

signals:

public slots:

private:
  static AbbreviationsStorage *m__Instance;

  StorageItemModel *m__Storage;

  StructAbbreviationCols m__Cols;

  QList<Abbreviation *> m__Abbreviations;

  explicit AbbreviationsStorage(QObject *parent = 0);
  ~AbbreviationsStorage();

  void reset();
  void setObjectData( Abbreviation *obj, MFCRecord *record );

private slots:
  void storageDestroyed();
  void recordAdded( MFCRecord *record, int index );
  void recordRemoved( MFCRecord *, int index );
  void disconnectRecord( MFCRecord *record, int );
  void propertyChanged( QString column );
  void changedShortName( QString value );
  void changedFullName( QString value );
};

#endif // ABBREVIATIONSSTORAGE_H
