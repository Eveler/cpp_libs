#ifndef MCALCULATIONALMODELPRIVATE_H
#define MCALCULATIONALMODELPRIVATE_H

#include <QObject>

#include <QVariant>


class MCalculationalRow;
class MCalculationalModel;

class MCalculationalModelPrivate : public QObject
{
  friend class MCalculationalModel;
  Q_OBJECT
public:
  explicit MCalculationalModelPrivate(QObject *parent = 0);


signals:


public slots:


private:
  QList<QVariant> m__Header;
  QList<MCalculationalRow *> m__Rows;

  void declareValues();
};

#endif // MCALCULATIONALMODELPRIVATE_H
