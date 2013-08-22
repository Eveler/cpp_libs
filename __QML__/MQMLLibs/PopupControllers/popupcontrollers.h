#ifndef POPUPCONTROLLERS_H
#define POPUPCONTROLLERS_H

#include <QObject>


class PopupController;

class PopupControllers: public QObject
{
    Q_OBJECT


public:
    static PopupControllers * instance();
    void addController( PopupController *controller );
    void removeController( PopupController *controller );


private:
    static PopupControllers *p__Instance;
    QList<PopupController *> p__Controllers;
    PopupController *m__Poppedup;

    PopupControllers();
    ~PopupControllers();


private slots:
    void poppedupChanged();
    void controllerDestroyed( QObject *obj );
};

#endif // POPUPCONTROLLERS_H
