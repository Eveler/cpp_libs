#ifndef POST_P_H
#define POST_P_H

#include <QObject>


class Post;
class Direction;

class Post_P : public QObject
{
  Q_OBJECT
  friend class Post;


public:


signals:


public slots:


private:
  QString m__Name;
  Direction *m__Direction;

  explicit Post_P( Post *parent = 0 );
  ~Post_P();

  Post * p_dptr() const;

  void setDirection( Direction *direction );

private slots:
  void directionDestroyed();
};

#endif // POST_P_H
