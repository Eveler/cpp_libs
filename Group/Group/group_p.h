#ifndef GROUP_P_H
#define GROUP_P_H

#include <QObject>


class Group;

class Group_P : public QObject
{
  Q_OBJECT
  friend class Group;


public:


signals:


public slots:


private:
  QString m__Name;

  explicit Group_P( Group *parent = 0 );

  Group * p_dptr() const;
};

#endif // GROUP_P_H
