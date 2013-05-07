#ifndef MEMBER_H
#define MEMBER_H

#include "abstractsimpleobject.h"

#include "export/member_export_lib.h"


class Member;
class Member_P;
class MembersStorage;
class Post;
class Group;

typedef QList<Member *> MemberList;

class EXPORT_MEMBER Member : public AbstractSimpleObject
{
  Q_OBJECT
  friend class Member_P;
  friend class MembersStorage;


public:
  ~Member();

  const QString & surname() const;
  const QString & firstname() const;
  const QString & lastname() const;
  Post * post() const;
  bool active() const;
  bool dismissed() const;
  Group * group() const;


signals:
  void surnameChanged();
  void firstnameChanged();
  void lastnameChanged();
  void postChaged();
  void activeChanged();
  void dismissedChanged();
  void groupChanged();


public slots:
  void setSurname( const QString &surname );
  void setFirstname( const QString &firstname );
  void setLastname( const QString &lastname );
  void setPost( Post *post );
  void setActive( bool active );
  void setDismissed( bool dismissed );
  void setGroup( Group *group );


private:
  Member_P *p;

  explicit Member( QVariant id, QObject *parent = 0 );
};

#endif // MEMBER_H
