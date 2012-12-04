#ifndef USER_H
#define USER_H

#include <QObject>

#include "mfccore.h"
#include "abstractsimpleobject.h"

class User : public QObject
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
public:
  explicit User(QObject *parent = 0);
  ~User();

  const QVariant & id() const;
  const StructName & name() const;
  const AbstractSimpleObject * post() const;
  const AbstractSimpleObject * department() const;
  const bool active() const;
  const bool dismissed() const;
  const AbstractSimpleObject * office() const;

signals:

public slots:
  void clear();

  void setId( QVariant value );
  void setName( StructName value );
  void setPost( AbstractSimpleObject *value );
  void setDepartment( AbstractSimpleObject *value );
  void setActive( bool value );
  void setDismissed( bool value );
  void setOffice( AbstractSimpleObject *value );

private:
  StructUser m__Value;
};

#endif // USER_H
