#ifndef STRUCTURESTATUS_H
#define STRUCTURESTATUS_H

#include <QObject>
#include <QVariant>

class StructureStatus : public QObject
{
  typedef struct
  {
    QVariant m__Id;
    QString m__ShortName;
    QString m__FullName;
  } StructStructureStatus;

  Q_OBJECT
public:
  explicit StructureStatus(QObject *parent = 0);

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
  StructStructureStatus m__StructStructureStatus;
};

#endif // STRUCTURESTATUS_H
