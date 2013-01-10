#ifndef SUBJECT_H
#define SUBJECT_H

#include <QObject>
#include <QVariant>

#include "abbreviation.h"

class Subject : public QObject
{
  typedef struct
  {
    QVariant m__Id;
    Abbreviation *m__Abbreviation;
    QString m__Name;
  } StructSubject;

  Q_OBJECT
public:
  explicit Subject(QObject *parent = 0);

  const QVariant & id() const;
  Abbreviation * abbreviation() const;
  const QString & name() const;

signals:
  void changedAbbreviation( Abbreviation *value );
  void changedName( QString value );

public slots:
  void setId( QVariant value );
  void setAbbreviation( Abbreviation *value );
  void setName( QString value );

private:
  StructSubject m__StructSubject;
};

#endif // SUBJECT_H
