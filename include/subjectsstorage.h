#ifndef SUBJECTSSTORAGE_H
#define SUBJECTSSTORAGE_H

#include "storageitemmodel.h"
#include "subject.h"

typedef struct
{
  QString cId;
  QString cAbbreviation;
  QString cName;
} StructSubjectCols;

class SubjectsStorage : public QObject
{
    Q_OBJECT
public:
  static SubjectsStorage * instance();

  bool setStorage( StorageItemModel *stor, StructSubjectCols cols );
  StorageItemModel * storage() const;

  const QList<Subject *> & objects() const;

  QList<Subject *> findById( QList<Subject *> objs, QVariant value ) const;

signals:

public slots:

private:
  static SubjectsStorage *m__Instance;

  StorageItemModel *m__Storage;

  StructSubjectCols m__Cols;

  QList<Subject *> m__Subjects;

  explicit SubjectsStorage(QObject *parent = 0);
  ~SubjectsStorage();

  void reset();
  void setObjectData( Subject *obj, MFCRecord *record );

private slots:
  void storageDestroyed();
  void recordAdded( MFCRecord *record, int index );
  void recordRemoved( MFCRecord *, int index );
  void disconnectRecord( MFCRecord *record, int );
  void propertyChanged( QString column );
  void changedAbbreviation( Abbreviation *value );
  void changedName( QString value );
};

#endif // SUBJECTSSTORAGE_H
