#ifndef POST_P_H
#define POST_P_H

#include <QObject>


class Post;

class Post_P : public QObject
{
  Q_OBJECT
  friend class Post;


public:


signals:


public slots:


private:
  QString m__Name;

  explicit Post_P( Post *parent = 0 );

  Post * p_dptr() const;
};

#endif // POST_P_H
