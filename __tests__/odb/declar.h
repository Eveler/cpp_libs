#ifndef DECLAR_H
#define DECLAR_H

#pragma db object
class Declar
{
public:
  explicit Declar();
#pragma db get(getID)
  int getID()const;
#pragma db set(setID)
  void setID(int id_);

private:
#pragma db id auto
  int id;
};

#endif // DECLAR_H
