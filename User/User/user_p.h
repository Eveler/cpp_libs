#ifndef USER_P_H
#define USER_P_H

#include <QObject>


class User;
class Post;
class Department;
class Office;
class Group;

class User_P : public QObject
{
  Q_OBJECT
  friend class User;


public:


signals:


public slots:


private:
  QString m__Surname;
  QString m__Firstname;
  QString m__Lastname;
  Post *m__Post;
  Department *m__Department;
  bool m__Active;
  bool m__Dismissed;
  Office *m__Office;
  Group *m__Group;

  explicit User_P( User *parent = 0 );

  User * p_dptr() const;
};

#endif // USER_P_H
