#ifndef MEMBERSSTORAGE_H
#define MEMBERSSTORAGE_H

#include "abstractsimplestorage.h"

#include "export/member_export_lib.h"
#include "member.h"


class Post;
class Group;
class Member;

class EXPORT_MEMBER MembersStorage : public AbstractSimpleStorage
{
  Q_OBJECT


public:
  static MembersStorage * instance();

  const MemberList & members() const;

  AbstractSimpleObjectList findBySurname(
      const AbstractSimpleObjectList &objects, const QString &surname ) const;
  AbstractSimpleObjectList findByFirstname(
      const AbstractSimpleObjectList &objects, const QString &firstname ) const;
  AbstractSimpleObjectList findByLastname(
      const AbstractSimpleObjectList &objects, const QString &lastname ) const;
  AbstractSimpleObjectList findByPost(
      const AbstractSimpleObjectList &objects, Post *post ) const;
  AbstractSimpleObjectList findByActive(
      const AbstractSimpleObjectList &objects, bool active ) const;
  AbstractSimpleObjectList findByDismissed(
      const AbstractSimpleObjectList &objects, bool dismissed ) const;
  AbstractSimpleObjectList findByGroup(
      const AbstractSimpleObjectList &objects, Group *group ) const;


signals:


public slots:


protected:
  AbstractSimpleObject * createObject( QVariant id );


private:
  static MembersStorage *m__Instance;

  explicit MembersStorage(QObject *parent = 0);
};

#endif // MEMBERSSTORAGE_H
