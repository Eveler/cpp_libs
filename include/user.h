#ifndef USER_H
#define USER_H

#include <QObject>

#include "mfccore.h"
#include "post.h"
#include "department.h"
#include "office.h"

class User : public QObject
{
  typedef struct
  {
    QVariant m__Id;
    StructName m__Name;
    Post *m__Post;
    Department *m__Department;
    bool m__Active;
    bool m__Dismissed;
    Office *m__Office;
  } StructUser;
  Q_OBJECT
public:
  explicit User(QObject *parent = 0);
  ~User();

  const QVariant & id() const;
  const StructName & name() const;
  const Post * post() const;
  const Department * department() const;
  const bool active() const;
  const bool dismissed() const;
  const Office * office() const;

signals:

public slots:
  void clear();

  void setId( QVariant value );
  void setName( StructName value );
  void setPost( Post *value );
  void setDepartment( Department *value );
  void setActive( bool value );
  void setDismissed( bool value );
  void setOffice( Office *value );

private:
  StructUser m__User;
};

#endif // USER_H
