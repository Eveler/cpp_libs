#ifndef SERVICESSTORAGE_H
#define SERVICESSTORAGE_H

#include <QObject>

class ServicesStorage : public QObject
{
    Q_OBJECT
public:
  static ServicesStorage * instance();

signals:

public slots:

private:
  static ServicesStorage *m__Instance;

  explicit ServicesStorage(QObject *parent = 0);
};

#endif // SERVICESSTORAGE_H
