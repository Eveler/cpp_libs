#ifndef USER_H
#define USER_H

#include <QObject>

#include "mfccore.h"
#include "abstractsimpleobject.h"


class UsersStorage;

class EXPORT User : public QObject
{
  typedef struct
  {
    QVariant m__Id;
    StructName m__Name;
    AbstractSimpleObject *m__Post;
    AbstractSimpleObject *m__Department;
    bool m__Active;
    bool m__Dismissed;
    AbstractSimpleObject *m__Office;
  } StructUser;
  Q_OBJECT
  friend class UsersStorage;


public:
  ~User();

  const QVariant & id() const;
  const StructName & name() const;
  const AbstractSimpleObject * post() const;
  const AbstractSimpleObject * department() const;
  bool active() const;
  bool dismissed() const;
  const AbstractSimpleObject * office() const;


signals:


public slots:
  void setName( StructName value );
  void setPost( AbstractSimpleObject *value );
  void setDepartment( AbstractSimpleObject *value );
  void setActive( bool value );
  void setDismissed( bool value );
  void setOffice( AbstractSimpleObject *value );


private:
  StructUser m__Value;

  explicit User( QVariant id, QObject *parent = 0 );

  void clear();

  void setId( QVariant value );
};

#endif // USER_H
