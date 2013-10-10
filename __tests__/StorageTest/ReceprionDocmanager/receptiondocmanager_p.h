#ifndef RECEPTIONDOCMANAGER_P_H
#define RECEPTIONDOCMANAGER_P_H

#include <QObject>

#include "widget_receptiondocmanager.h"


class Widget_ReceptionDocmanager;

class ReceptionDocmanager_P : public QObject
{
    Q_OBJECT
    friend class Widget_ReceptionDocmanager;


  public:


  signals:


  public slots:


  private:
    Docmanager *m__Docmanager;

    explicit ReceptionDocmanager_P( Widget_ReceptionDocmanager *parent );
};

#endif // RECEPTIONDOCMANAGER_P_H
