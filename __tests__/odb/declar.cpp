#include "declar.h"

Declar::Declar():
  id(0)
{
}

int Declar::getID() const
{
  return id;
}

void Declar::setID(int id_)
{
  if(id_>0) id = id_;
}
