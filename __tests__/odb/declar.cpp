#include "declar.h"

declars::declars():
  id(0)
{
}

int declars::getID() const
{
  return id;
}

void declars::setID(int id_)
{
  if(id_>0) id = id_;
}
