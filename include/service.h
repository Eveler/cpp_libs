#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include <QVariant>

class Service : public QObject
{
  typedef struct
  {
    QVariant m__Id;
    QString m__Name;
    int m__Deadline;
    bool m__Active;
  } StructService;

  Q_OBJECT
public:
  explicit Service(QObject *parent = 0);

  const QVariant & id() const;
  const QString & name() const;
  const int & deadline() const;
  bool active() const;

signals:

public slots:
  void setId( QVariant value );
  void setName( QString value );
  void setDeadline( int value );
  void setActive( bool value );

private:
  StructService m__StructService;
};

#endif // SERVICE_H
