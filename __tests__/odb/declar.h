#ifndef DECLAR_H
#define DECLAR_H

#include <QtCore/QDateTime>
#include <odb/core.hxx>

#pragma db object
class declars
{
public:
  explicit declars();
#pragma db get(getID)
  int getID() const;
#pragma db set(setID)
  void setID(int id_);

public:
  friend class odb::access;
#pragma db id
  int id;
  int srvid;
#pragma db not_null default(0)
  int declarnum;
#pragma db not_null default("now()")
  QDateTime datein;
#pragma db not_null
  QDateTime ctrldate;
  QString addr;
  int clid;
  QDateTime enddate;
#pragma db default(-1)
  int responsible;
#pragma db default(false)
  bool archived;
#pragma db default(false)
  bool vupravlenie;
  int upravlenieid;
#pragma db default(false)
  bool deleted;
#pragma db default(-1)
  int decowner;
  QDateTime created_date;
  int modifier;
  QDateTime modify_date;
  bool isnew;
  int trusteesid;
  int resultsid;
  QDate respite_date;
  int assessment_type_id;
  int assessment_id;
  QString addr1;
  int result_ways_id;
};

#endif // DECLAR_H
