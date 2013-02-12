#ifndef MCALCULATIONALMODELPRIVATE_H
#define MCALCULATIONALMODELPRIVATE_H

#include <QObject>

#include <QVariant>


class MCalculationalColumn;
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
  QList<MCalculationalColumn *> m__Columns;
  QList<MCalculationalRow *> m__Rows;

  void declareValues();
};

#endif // MCALCULATIONALMODELPRIVATE_H
