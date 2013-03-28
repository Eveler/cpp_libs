#ifndef DEPARTMENT_P_H
#define DEPARTMENT_P_H

#include <QObject>


class Department;

class Department_P : public QObject
{
  Q_OBJECT
  friend class Department;


public:


signals:


public slots:


private:
  QString m__Name;

  explicit Department_P( Department *parent = 0 );

  Department * p_dptr() const;
};

#endif // DEPARTMENT_P_H
