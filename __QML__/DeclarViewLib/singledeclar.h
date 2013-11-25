#ifndef SINGLEDECLAR_H
#define SINGLEDECLAR_H

#include <QQuickItem>

class SingleDeclar : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(SingleDeclar)

  public:
    SingleDeclar(QQuickItem *parent = 0);
    ~SingleDeclar();
};

#endif // SINGLEDECLAR_H

