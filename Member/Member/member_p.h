#ifndef MEMBER_P_H
#define MEMBER_P_H

#include <QObject>


class Member;
class Post;
class Group;

class Member_P : public QObject
{
  Q_OBJECT
  friend class Member;


public:


signals:


public slots:


private:
  QString m__Surname;
  QString m__Firstname;
  QString m__Lastname;
  Post *m__Post;
  bool m__Active;
  bool m__Dismissed;
  Group *m__Group;

  explicit Member_P( Member *parent = 0 );
  ~Member_P();

  Member * p_dptr() const;

  void setPost( Post *post );
  void setGroup( Group *group );


private slots:
  void postDestroyed();
  void groupDestroyed();
};

#endif // MEMBER_P_H
