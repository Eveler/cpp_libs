#ifndef ABBREVIATION_H
#define ABBREVIATION_H

#include <QObject>
#include <QVariant>

class Abbreviation : public QObject
{
  typedef struct
  {
    QVariant m__Id;
    QString m__ShortName;
    QString m__FullName;
  } StructAbbreviation;

  Q_OBJECT
public:
  explicit Abbreviation(QObject *parent = 0);

  const QVariant & id() const;
  const QString & shortName() const;
  const QString & fullName() const;

signals:
  void changedShortName( QString value );
  void changedFullName( QString value );

public slots:
  void setId( QVariant value );
  void setShortName( QString value );
  void setFullName( QString value );

private:
  StructAbbreviation m__StructAbbreviation;
};

#endif // ABBREVIATION_H
