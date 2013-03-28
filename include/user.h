#ifndef USER_H
#define USER_H

#include "abstractsimpleobject.h"


class User_P;
class UsersStorage;
class Post;
class Department;
class Office;
class Group;

class EXPORT User : public AbstractSimpleObject
{
  Q_OBJECT
  friend class User_P;
  friend class UsersStorage;
  Q_PROPERTY(QString surname READ surname WRITE setSurname NOTIFY surnameChanged)
  Q_PROPERTY(QString firstname READ firstname WRITE setFirstname NOTIFY firstnameChanged)
  Q_PROPERTY(QString lastname READ lastname WRITE setLastname NOTIFY lastnameChanged)
  Q_PROPERTY(Post * post READ post WRITE setPost NOTIFY postChaged)
//  Q_PROPERTY(QString surname READ surname WRITE setSurname NOTIFY surnameChanged)
//  Q_PROPERTY(QString surname READ surname WRITE setSurname NOTIFY surnameChanged)
//  Q_PROPERTY(QString surname READ surname WRITE setSurname NOTIFY surnameChanged)
//  Q_PROPERTY(QString surname READ surname WRITE setSurname NOTIFY surnameChanged)
//  Q_PROPERTY(QString surname READ surname WRITE setSurname NOTIFY surnameChanged)


public:
  ~User();

  const QString & surname() const;
  const QString & firstname() const;
  const QString & lastname() const;
  Post * post() const;
  Department * department() const;
  bool active() const;
  bool dismissed() const;
  Office * office() const;
  Group * group() const;


signals:
  void surnameChanged();
  void firstnameChanged();
  void lastnameChanged();
  void postChaged();
  void departmentChanged();
  void activeChanged();
  void dismissedChanged();
  void officeChanged();
  void groupChanged();


public slots:
  void setSurname( const QString &surname );
  void setFirstname( const QString &firstname );
  void setLastname( const QString &lastname );
  void setPost( Post *post );
  void setDepartment( Department *department );
  void setActive( bool active );
  void setDismissed( bool dismissed );
  void setOffice( Office *office );
  void setGroup( Group *group );


private:
  User_P *p;

  explicit User( QVariant id, QObject *parent = 0 );
};

#endif // USER_H
