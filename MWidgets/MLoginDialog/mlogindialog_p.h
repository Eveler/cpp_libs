#ifndef MLOGINDIALOG_P_H
#define MLOGINDIALOG_P_H

#include <QObject>

#include "mlogindialog.h"


class MLoginDialog_P : public QObject
{
  Q_OBJECT
  friend class MLoginDialog;


public:


signals:


public slots:


private:
  QStringList m__Names;

  explicit MLoginDialog_P( MLoginDialog *parent );

  MLoginDialog * p_dptr() const;
};

#endif // MLOGINDIALOG_P_H
