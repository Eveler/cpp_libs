#ifndef OFFICE_P_H
#define OFFICE_P_H

#include <QObject>


class Office;

class Office_P : public QObject
{
  Q_OBJECT
  friend class Office;


public:


signals:


public slots:


private:
  QString m__Name;

  explicit Office_P( Office *parent = 0 );

  Office * p_dptr() const;
};

#endif // OFFICE_P_H
